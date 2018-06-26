

void setup()
   { Serial.begin(38400);
     Serial.println("Enter AT commands:");
   }


void loop()
   {  if (Serial.available())
          Serial.write(Serial.read());  

      if (Serial.available())
         { Serial.write(Serial.read()); 
         }
   }
   //https://www.prometec.net/bluetooth-le/#