#include <SoftwareSerial.h>

SoftwareSerial EBlue(10,11);

    /*
    == MASTER DEVICE - Joystick ==B
    */
    int xAxis, yAxis;
    void setup() {
      Serial.begin(9600);
      EBlue.begin(9600);; // Default communication rate of the Bluetooth module
    }
    void loop() {
      xAxis = analogRead(A0); // Read Joysticks X-axis
      yAxis = analogRead(A1); // Read Joysticks Y-axis
      
      // Send the values via the serial port to the slave HC-05 Bluetooth device
        
    if (EBlue.available()){
    EBlue.write(xAxis/4);// Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
    delay(10);
    EBlue.write(yAxis/4);
    }
      //Serial.println(xAxis/4);
      //Serial.println();
      Serial.print(EBlue.write("a"));
      delay(20);
    } 
