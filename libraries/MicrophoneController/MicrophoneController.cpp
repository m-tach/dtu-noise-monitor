#include <MicrophoneController.h>

#define NS 20000


float SOS_A[3][6] = {
{1.000000e+00, 2.000000e+00, 1.000000e+00, 1.000000e+00, -1.405361e-01, 4.937598e-03},
{1.000000e+00, -2.000000e+00, 1.000000e+00, 1.000000e+00, -1.884901e+00, 8.864215e-01},
{1.000000e+00, -2.000000e+00, 1.000000e+00, 1.000000e+00, -1.994139e+00, 9.941475e-01},
};

float SV_A[4] = {2.557411e-01, 1.000000e+00, 1.000000e+00, 1.000000e+00};


static __inline__ void syncADC() __attribute__((always_inline, unused));

static void syncADC() 
{
    while (ADC->STATUS.bit.SYNCBUSY == 1);
}

/**
   Powers down all devices and puts the system to deep sleep.
*/
void systemSleep()
{

  __WFI(); // SAMD sleep

}

void initADC() 
{
  SYSCTRL->OSC8M.bit.PRESC = 0;                          // no prescaler (is 8 on reset)
  SYSCTRL->OSC8M.reg |= 1 << SYSCTRL_OSC8M_ENABLE_Pos;   // enable source

  REG_PORT_DIRCLR1 = PORT_PA11;
  PORT->Group[0].PINCFG[11].bit.PMUXEN = 1;
  PORT->Group[0].PMUX[5].reg = PORT_PMUX_PMUXO_B;

  GCLK->GENDIV.bit.ID = 0x03;
  GCLK->GENDIV.bit.DIV = 9;
  GCLK->GENCTRL.reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_ID(3); // GCLK_GENCTRL_DIVSEL don't need this, it makes divide based on power of two
  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ) {}

  PM->APBCSEL.bit.APBCDIV = 0;                           // no prescaler
  REG_PM_APBCMASK |= PM_APBCMASK_ADC;

  GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(3) | GCLK_CLKCTRL_ID(30);
  while (GCLK->STATUS.bit.SYNCBUSY == 1);

  REG_ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC0; //set vref for ADC to VCC
  syncADC();
  // Sampling time, no extra sampling half clock-cycles
  REG_ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(0);
  //
  // Input control and input scan
  REG_ADC_INPUTCTRL |= ADC_INPUTCTRL_GAIN_1X |
                       ADC_INPUTCTRL_MUXNEG_GND |
                       ADC_INPUTCTRL_MUXPOS_PIN19;

  ADC->CTRLB.bit.RESSEL = 0;
  syncADC();
  ADC->CTRLB.bit.PRESCALER = 0x0; //DIV4
  syncADC();
  ADC->CTRLA.bit.ENABLE = 0x01;
  syncADC();
  ADC->CTRLA.bit.ENABLE = 0;
  syncADC();
}
  
// Set the sleep mode
void initSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

void readADC(char *a, size_t asize)
{
    int i = 0;

    float input;

    float y1 = 0;
    float y2 = 0;
    float y3 = 0;
    float buf11 = 0.0;
    float buf21 = 0.0;
    float buf12 = 0.0;
    float buf22 = 0.0;
    float buf13 = 0.0;
    float buf23 = 0.0;

    float squarer;
    
    float pr2 = 20e-6 * 20e-6;

    float Leq;

    float sum = 0;

    float lat;
    float lon;

    //char a[13];
    //String value;


    sodaq_wdt_reset();                  // restting the watchdog
    sodaq_wdt_disable();

    for (i = 0; i < NS; i++) {
        ADC->CTRLA.bit.ENABLE = 0x01;
        syncADC();
        ADC->SWTRIG.bit.START = 1;
        while (ADC->INTFLAG.bit.RESRDY == 0);
        syncADC();
        ADC->CTRLA.bit.ENABLE = 0;
        syncADC();

        input = (float)(ADC->RESULT.reg) / 4095;

        y1 = SV_A[0] * SOS_A[0][0] * input + buf11;
        buf11 = SV_A[0] * SOS_A[0][1] * input - SOS_A[0][4] * y1 + buf21;
        buf21 = SV_A[0] * SOS_A[0][2] * input - SOS_A[0][5] * y1;

        y2 = SOS_A[1][0] * y1 + buf12;
        buf12 = SOS_A[1][1] * y1 - SOS_A[1][4] * y2 + buf22;
        buf22 = SOS_A[1][2] * y1 - SOS_A[1][5] * y2;

        y3 = SOS_A[2][0] * y2 + buf13;
        buf13 = SOS_A[2][1] * y2 - SOS_A[2][4] * y3 + buf23;
        buf23 = SOS_A[2][2] * y2 - SOS_A[2][5] * y3;

        squarer = y3 * y3;

        sum += squarer;
    }

    Leq = 10 * log10((sum / NS) / pr2);
    //SerialUSB.println(Leq);

    memcpy(&a[0], &Leq, sizeof(Leq));  
    memcpy(&a[4], &lat, sizeof(lat));
    memcpy(&a[8], &lon, sizeof(lon));
    a[12] = 0;
    //value = String(a);

    //return a;


    y1 = 0.0;
    y2 = 0.0;
    y3 = 0.0;

    buf11 = 0.0;
    buf21 = 0.0;
    buf12 = 0.0;
    buf22 = 0.0;
    buf13 = 0.0;
    buf23 = 0.0;

    sum = 0;

    sodaq_wdt_enable(WDT_PERIOD_8X);    // watchdog expires in ~8 seconds
    systemSleep();
}