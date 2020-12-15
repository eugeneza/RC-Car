#include <Servo.h>
Servo steer_servo;

// RC Car setup

#define chan1 A0
#define chan3 A1
#define chan6 A2

//Pins for dual motor and LED

int PWM1 = 5;
int PWM2 = 6;
int led = 7;
int arm;

//Declaring some global variables
int channel1;
int channel3;
int channel6; 
int s_val; // Servo value


void initialize(){                                // Initializes all pins used
  steer_servo.attach(10);                         // Attaches servo to pin 10
  pinMode(chan1, INPUT);
  pinMode(chan3, INPUT);
  pinMode(chan6, INPUT);
  pinMode(led, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
}

void full_stop(){                               // Puts car to a complete stop
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}

void go_forward(int pwm){                       // Drives forward based on PWM
  analogWrite(PWM1, pwm);
  analogWrite(PWM2, 0);
}

void go_back(int pwm){                          // Drives back based on PWM
  analogWrite(PWM1, 0);
  analogWrite(PWM2, pwm);
}

void find_chan1(){                             // Reads channel 1 value to steer servo motor
  channel1 = pulseIn(chan1, HIGH, 100000);
  s_val = map(channel1, 1000, 2000, 45, 135);
  if ((s_val >= 45) && (s_val <=135)){
  steer_servo.write(s_val);                    // Writes servo value to move in a direction
  }
  
  else{
  steer_servo.write(90);      
  }
}

void find_chan3(){                              // Reads channel 3 value to determine pwm and direction of motors
  int pwm;
  channel3 = pulseIn(chan3, HIGH, 100000);
  if(channel3 > 1549){
    pwm = map(channel3, 1550, 2000, 0, 130);
    go_forward(pwm);
  }
  else if(channel3 < 1451){
    pwm = map(channel3, 1000, 1450, 130, 0);
    go_back(pwm);
  }
  else{
    full_stop();
  }
}


int find_chan6(){
  channel6 = pulseIn(chan6, HIGH, 100000);
  return channel6;
}

void arm_status(){                             // Reads channel 6 value to determine if RC car gets armed          
  while((channel6 < 1500) || ((channel3 < 1451) ||(channel3 > 1549))){ // Car will stay disarmed as long as left stick is not in neutral position
    full_stop();
    digitalWrite(led, LOW);
    channel6 = find_chan6();
    channel3 = pulseIn(chan3, HIGH, 100000);  
    }
  digitalWrite(led, HIGH);
}
