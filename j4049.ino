#include "mController.h"
// /*
//     J4049 - Arduino Controlled GoKart. Version 2.0
//     Changes: Classes to control devices
//              Controls operate in different manner than
//              originally designed.
// */

// directional constants
int DIRECTION_STOPPED = 0;
int DIRECTION_FORWARD = 1;
int DIRECTION_REVERSE = 2;

// ----------------------------
// JS705 - LEFT JOYSTICK
// This now only controls the throttle
// ----------------------------
int JS705_X_PIN = A0;
int JS705_Y_PIN = A1;
JoyStick js705(705, JS705_X_PIN, JS705_Y_PIN, 0, 1023, -100, 100);

// ----------------------------
// JS711 - RIGHT JOYSTICK
// This now only controls the left/right
// ----------------------------
int JS711_X_PIN = A2;
int JS711_Y_PIN = A3;
JoyStick js711(711, JS711_X_PIN, JS711_Y_PIN, 0, 1023, -100, 100);

// ----------------------------
// M208 DRIVER/FRONT LEFT PINS
//-----------------------------
int M208_L_EN = 22;
int M208_R_EN = 23;
int M208_L_I = 33;
int M208_R_I = 32;
int M208_L_PWM = 2;
int M208_R_PWM = 3;
Motor m208(208, M208_L_I, M208_R_I, M208_L_EN, M208_R_EN, M208_L_PWM, M208_R_PWM, 0, 100, 0, 255);


// ----------------------------
// M308 REAR LEFT PINS
//-----------------------------
int M308_L_EN = 24;
int M308_R_EN = 25;
int M308_L_I = 31;
int M308_R_I = 30;
int M308_L_PWM = 4;
int M308_R_PWM = 5;
Motor m308(308, M308_L_I, M308_R_I, M308_L_EN, M308_R_EN, M308_L_PWM, M308_R_PWM, 0, 100, 0, 255);

// ----------------------------
// M408 FRONT RIGHT PINS
//-----------------------------
int M408_L_EN = 26;
int M408_R_EN = 27;
int M408_L_I = 35;
int M408_R_I = 34;
int M408_L_PWM = 6;
int M408_R_PWM = 7;
Motor m408(408, M408_L_I, M408_R_I, M408_L_EN, M408_R_EN, M408_L_PWM, M408_R_PWM, 0, 100, 0, 255);

// ----------------------------
// M508 REAR RIGHT PINS
//-----------------------------
int M508_L_EN = 28;
int M508_R_EN = 29;
int M508_L_I = 37;
int M508_R_I = 36;
int M508_L_PWM = 8;
int M508_R_PWM = 9;
Motor m508(508, M508_L_I, M508_R_I, M508_L_EN, M508_R_EN, M508_L_PWM, M508_R_PWM, 0, 100, 0, 255);

// local position variables.
jspos jsl_pos;
jspos jsr_pos;

// speed parameters.
int base_speed = 0;
float fract_speed = 0.0;
float right_speed = 0;
float left_speed = 0;

// deadband values for turning
// thresholds
int turn_db_max = 25;
int turn_db_min = -25;

void setup(){

  // launch the serial port
  Serial.begin(9600);
  
  js705.setup();
  js711.setup();
  
  m208.setup();
  m308.setup();
  m408.setup();
  m508.setup();
}

void loop(){

  // gets the position of the 
  // two joysticks
  jsl_pos = js705.loop();
  jsr_pos = js711.loop();

  // call the motor loop routines.
  m208.loop();
  m308.loop();
  m408.loop();
  m508.loop();

  // forward or reverse logic for the 
  // motors
  if (jsl_pos.y > 1){
    
    m208.set_direction(DIRECTION_FORWARD);
    m308.set_direction(DIRECTION_FORWARD);
    m408.set_direction(DIRECTION_FORWARD);
    m508.set_direction(DIRECTION_FORWARD);
  
  } else if(jsl_pos.y < -1){
    
    m208.set_direction(DIRECTION_REVERSE);
    m308.set_direction(DIRECTION_REVERSE);
    m408.set_direction(DIRECTION_REVERSE);
    m508.set_direction(DIRECTION_REVERSE);
  
  } else{
    
    m208.set_direction(DIRECTION_STOPPED);
    m308.set_direction(DIRECTION_STOPPED);
    m408.set_direction(DIRECTION_STOPPED);
    m508.set_direction(DIRECTION_STOPPED);
  
  }

  // calculates the base speed.
  // this is a percentage 0-100%
  base_speed = abs(jsl_pos.y);

  // this is the fraction speed
  fract_speed = jsr_pos.x * 0.01;

  // if the right joystick is turning
  // left (negative)
  if(jsr_pos.x <= turn_db_min){
    left_speed = base_speed - (base_speed * abs(fract_speed));
  }else{
    left_speed = base_speed;
  }
  
  // if the right joystick is turning
  // right (positive)
  if(jsr_pos.x >= turn_db_max){
    right_speed = base_speed - (base_speed * abs(fract_speed));
  }else{
    right_speed = base_speed;
  }  

  // sends the speeds to the motors. If there is no
  // turning then all of the speeds should equal the
  // base speed.
  m208.set_speed(left_speed);
  m308.set_speed(right_speed);
  m408.set_speed(left_speed);
  m508.set_speed(right_speed);

  //Serial.print("base_speed = ");
  //Serial.print(base_speed);
  //Serial.print("  fract_speed = ");
  //Serial.print(fract_speed);
  //Serial.print("  left_speed =");
  //Serial.print(left_speed);
  //Serial.print("  right_speed = ");
  //Serial.println(right_speed);
  
  //jsl.print_info();
  //jsr.print_info();

  m208.print_info();
  m308.print_info();
  m408.print_info();
  m508.print_info();
  
}
