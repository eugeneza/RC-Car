// Code for RC Car
// Eugene Zaverukha

#include "setup.h"



void setup() {
  //Serial.begin(9600);
  initialize();               // Initializes all pins and stops the motors
  full_stop();
  
  digitalWrite(led, HIGH);    // Initialize sequence with an LED toggle to indicate car is ready to operate
  delay(250);            
  digitalWrite(led, LOW);

}

void loop() {
  
  arm = find_chan6();
  if (arm < 1500){
    arm_status();           // Checks if car is armed
  }
  find_chan3();           // Determine pwm and direction of movement with left stick (up/ down)
  find_chan1();           // Steer car using right stick (left/ right)         

}
