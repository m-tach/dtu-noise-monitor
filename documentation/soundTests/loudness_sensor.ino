int loudness;

void setup()
{
    SerialUSB.begin(9600);
}

void loop()
{
    loudness = analogRead(0);    
    SerialUSB.println("Loudness = "+String(loudness));
    delay(200);
}
