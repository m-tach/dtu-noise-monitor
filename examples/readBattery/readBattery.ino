#define ADC_AREF 3.3f
#define BATVOLT_R1 4.7f
#define BATVOLT_R2 10.0f
#define BATVOLT_PIN BAT_VOLT

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(57600);

  while(!SerialUSB){
    //wait for Serial Monitor to be opened
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialUSB.println(getBatteryVoltage());

  delay(1000);
}

uint16_t getBatteryVoltage()
{
    uint16_t voltage = (uint16_t)((ADC_AREF / 1.023) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * (float)analogRead(BATVOLT_PIN));

    return voltage;
}
