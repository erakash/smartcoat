#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

//*************Declare Pins******************//

//*************Declare Variables**************//
String COMMAND;
int UpperThreshold = 518;
int LowerThreshold = 490;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;
int reading = 0;

//*********Declare Sensor Variables*************//
float BPM = 0.0;
float temp;
int co2;
int tvoc;


void setup() {
  Serial.begin(38400);
  Serial.println("System Started");
    if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
    while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

void loop() {
  RefreshHeartRate();
  RefreshAirqualityRate();
  RefreshHeartRate();
    if (Serial.available() > 0) {
    COMMAND = Serial.readStringUntil('\n');
    if(COMMAND.equals("READ")){
      Serial.println("BPM:"+String(BPM) + "TMP:"+temp+"ECO2:"+co2+"TVOC:"+tvoc );
    }
    else{
      
      }
  }

}


void RefreshHeartRate(){
  reading = analogRead(0); 

      // Heart beat leading edge detected.
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }

      // Heart beat trailing edge detected.
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  

      BPM = (1.0/PulseInterval) * 60.0 * 1000;
  }


  void RefreshAirqualityRate() {
  if(ccs.available()){
    if(!ccs.readData()){
    temp = ccs.calculateTemperature();
      co2 = ccs.geteCO2();
      tvoc = ccs.getTVOC();
    }
  }
}