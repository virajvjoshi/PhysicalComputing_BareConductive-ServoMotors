/* Industrial Design and Physical Computing by:
 * Viraj Joshi  (http://virajvjoshi.com)
 * Matteo Bandi (http://matteobandidesign.com)
 * August 2018
 */
 
// compiler error handling
#include "Compiler_Errors.h"
#include "Servo.h"

//Naming Servos
Servo ServoA1;
Servo ServoA2;
Servo ServoB1;
Servo ServoB2;

//Ensure all Servos are back to home position when starting
int Lpos = 0;

// touch includes
#include <MPR121.h>
#include <Wire.h>
#include <Servo.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// touch behaviour definitions
#define firstPin 0
#define lastPin 11

void setup(){  
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);

  ServoA1.attach(9);
  ServoA2.attach(8);
  ServoB1.attach(7);
  ServoB2.attach(6);
}

void loop(){
  readTouchInputs();
}


void readTouchInputs(){
  if(MPR121.touchStatusChanged()){
    
    MPR121.updateTouchData();
    if(MPR121.getNumTouches()<=1){
      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        
        if(MPR121.isNewTouch(i)){
for (Lpos = 0; Lpos < 45; Lpos++){
    ServoA1.write(Lpos);
    ServoA2.write(Lpos);
    ServoB2.write(Lpos);
    ServoB1.write(Lpos);
    delay(150);
 }     
    for (Lpos = 45; Lpos >= 0; Lpos -= 1) {
    ServoA1.write(Lpos);
    ServoA2.write(Lpos);
    ServoB2.write(Lpos);
    ServoB1.write(Lpos);
    delay(150);
  }
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" was just touched");
            digitalWrite(LED_BUILTIN, HIGH);
            
            }     
        }
        }
      }
    }
