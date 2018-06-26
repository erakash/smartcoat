void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  float sensorVoltage; 
  float sensorValue;
  int uvindex;
  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue/1024*3.3;
  uvindex = sensorVoltage/0.1;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print("UV Index = ");
  Serial.print(uvindex);
  delay(1000);
}