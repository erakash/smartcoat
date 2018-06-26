

const int temperaturePin = A0;


void setup()
{


  Serial.begin(9600);
}


void loop()
{

  float voltage, degreesC, degreesF;


  voltage = getVoltage(temperaturePin);


  degreesC = (voltage - 0.5) * 100.0;

  // While we're at it, let's convert degrees Celsius to Fahrenheit.
  // This is the classic C to F conversion formula:

  degreesF = degreesC * (9.0/5.0) + 32.0;

  // Now we'll use the serial port to print these values
  // to the serial monitor!



  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.println(degreesF);


  delay(1000); // repeat once per second (change as you wish!)
}


float getVoltage(int pin)
{


  return (analogRead(pin) * 0.00292969);


}


