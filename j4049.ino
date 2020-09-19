#include "mController.h"
// /*
//     J4049 - Arduino Controlled GoKart. Version 2.0
//     Changes: Classes to control devices
//              Controls operate in different manner than
//              originally designed.
// */

// left joystick. This controls the forward, reverse
// action of the vehicle.
JoyStick jsl(1, A0, A1, 0, 1023, -100, 100);

// right joystick
JoyStick jsr(2, A2, A3, 0, 1023, -100, 100);

// motor drivers side front
Motor mdsf(1, 3, 4, 2, 0, 100, 0, 255);

// motor passenger side front
Motor mpsf(2, 5, 4, 7, 0, 100, 0, 255);

// motor drivers side rear
Motor mdsr(3, 9, 8, 12, 0, 100, 0, 255);

// motor passenger side rear
Motor mpsr(4, 10, 11, 13, 0, 100, 0, 255);

// local position
jspos jsl_pos;
jspos jsr_pos;

// speed parameters.
int base_speed = 0;
float fract_speed = 0.0;
int turn_db_max = 25;
int turn_db_min = -25;
float right_speed = 0;
float left_speed = 0;

float scp(float raw_input, float rmin, float rmax, float smin, float smax){

  float sn;
  float sd;
  float s;
  float i;
  float out;
    
  // some pre-calculations (for linear)
  sn = smax - smin;
  sd = rmax - rmin;
  s = sn / sd;
  i = smax - (s * rmax);

  // caluclate the output
  out = raw_input * s + i;

  return out;    
}

void setup(){

  // launch the serial port
  Serial.begin(9600);
  
  jsl.setup();
  jsr.setup();
  
  mdsf.setup();
  mpsf.setup();
  mdsr.setup();
  mpsr.setup();
}

void loop(){

  // gets the position of the 
  // two joysticks
  jsl_pos = jsl.loop();
  jsr_pos = jsr.loop();

  // call the motor loop routines.
  mdsf.loop();
  mpsf.loop();
  mdsr.loop();
  mpsr.loop();

  // forward or reverse logic for the 
  // motors
  if (jsl_pos.y >= 0){
    mdsf.move_forward();
    mpsf.move_forward();
    mdsr.move_forward();
    mpsr.move_forward();
  }
  else{
    mdsf.move_reverse();
    mpsf.move_reverse();
    mdsr.move_reverse();
    mpsr.move_reverse();
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

  // sends the speeds to the motors
  mdsf.set_speed(left_speed);
  mpsf.set_speed(right_speed);
  mdsr.set_speed(left_speed);
  mpsr.set_speed(right_speed);

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

  mdsf.print_info();
  mpsf.print_info();
  mdsr.print_info();
  mpsr.print_info();
}
