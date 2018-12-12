#include <Wire.h>

// ---------------------MOTORS---------------
//        M208 - FRONT LEFT
//        M308 - REAR LEFT
//        M408 - FRONT RIGHT
//        M508 - REAR RIGHT
//-------------------------------------------

// joystick pins
//JS705 - LEFT
//JS711 = RIGHT
//PIN A0 - JS705 Y-AXIS
//PIN A1 - JS711 X-AXIS
//PIN A2 - JS711 Y-AXIS
//PIN A3 - JS705 X-AXIS

int JS705_Y_PIN = A0;
int JS705_X_PIN = A3;
int JS711_Y_PIN = A2;
int JS711_X_PIN = A1;
int JS705_Y;
int JS705_X;
int JS711_Y;
int JS711_X;

// SPEED REGISTERS OVER i2c
// EACH MOTOR HAS THERE OWN SPEED
// REGISTER
#define MOTOR_I2C_ADDRESS = 0x2c;
#define M208_SPEED_REGISTER = 0x00;
#define M308_SPEED_REGISTER = 0x01;
#define M408_SPEED_REGISTER = 0x02;
#define M508_SPEED_REGISTER = 0x03;

// SPEED COMMAND INTEGERS
// THESE ARE SPEEDS IN PERCENTAGES
float M208_SPEED = 0.0;
float M308_SPEED = 0.0;
float M408_SPEED = 0.0;
float M508_SPEED = 0.0;

// reverse pins. These are
// tested pins.
int M208_REV_PIN = 22;
int M308_REV_PIN = 24;
int M408_REV_PIN = 26;
int M508_REV_PIN = 28;

// strafe speed in percentage
int STRAFE_SPEED = 50;

// variable to detect if the 
// kart is in strife mode.
bool STRAFE_LEFT = 0;
bool STRAFE_RIGHT = 0;

void setup() {
  // put your setup code here, to run once:

  // initialize the serial connection
  Serial.begin(9600);
  
  // assign the speed pins to outputs  
  pinMode(SP1, OUTPUT);
  pinMode(SP2, OUTPUT);
  pinMode(SP3, OUTPUT);
  pinMode(SP4, OUTPUT);

  // sets the pin mode for the
  // reverse outputs
  pinMode(REV1, OUTPUT);
  pinMode(REV2, OUTPUT);
  pinMode(REV3, OUTPUT);
  pinMode(REV4, OUTPUT);
  
}

float scp(int input, int rmin, int rmax, int smin, int smax){
  // this routine takes in a raw input value
  // plus parameters and will return the scaled 
  // output
  float slope;
  float inter;

  // slope is rise over run
  slope = (smax - smin) / (rmax - rmin);

  // intercept calculation
  inter = smax - slope*rmax;

  // return value (line formula)
  return input*slope + inter;
}

void loop() {
  // put your main code here, to run repeatedly:

  // firstly, we will read the joystick values.
  JS705_Y = analogRead(JS705_Y_PIN);
  JS705_X = analogRead(JS705_X_PIN);
  JS711_Y = analogRead(JS711_Y_PIN);
  JS711_X = analogRead(JS711_X_PIN);

  // the joysticks at center center are at 500, 500
  // roughly. Less than 500 is backwards
  // so, lets control the high control output first. we 
  // need a little "slop" in the  
  // first we need to check the mode

  // determine if we are in strife mode
  // when both joysticks x-values are certain
  // critirea
  if(JS705_X < 100 and JS711_X < 100){
    STRAFE_LEFT = 1;

    // put the correct motor in
    // reverse
  }
  else{
    STRAFE_LEFT = 0;
    
    // put the correct motor in
    // forward
  }
  if(JS705_X > 850 and JS711_X > 850){
    STRAFE_RIGHT = 1;
    
    // put the correct motor in
    // reverse
    
  }
  else{
    STRAFE_RIGHT = 0;
    
    // put the correct motor in
    // forward
  }

  if(STRAFE_RIGHT = 0 and STRAFE_LEFT = 0){

    if(JS705_Y > 500){
      M208_SPEED = scp(JS705_Y, 500, 1024, 256, 0);
      M308_SPEED = scp(JS705_Y, 500, 1024, 256, 0);
      digitalWrite(M208_REV_PIN , LOW);
      digitalWrite(M308_REV_PIN , LOW);
    }
    else{
      M208_SPEED = scp(JS1_Y, 500, 0, 256, 0);
      M308_SPEED = scp(JS1_Y, 500, 0, 256, 0);
      digitalWrite(M208_REV_PIN , HIGH);
      digitalWrite(M308_REV_PIN , HIGH);
    }
    if(JS2_Y > 500){
      M408_SPEED = scp(JS2_Y, 500, 1024, 256, 0);
      M508_SPEED = scp(JS2_Y, 500, 1024, 256, 0);
      digitalWrite(M408_REV_PIN , LOW);
      digitalWrite(M508_REV_PIN , LOW);
    }
    else{
      M408_SPEED = scp(JS2_Y, 500, 0, 256, 0);
      M508_SPEED = scp(JS2_Y, 500, 0, 256, 0);
      digitalWrite(M408_REV_PIN , HIGH);
      digitalWrite(M508_REV_PIN , HIGH);      
    }
  }

  // write the speed commands to the i2c speed
  // controller board (digital pot)
  

  // print some debug information on the serial
  // console at the end
  // lets print them out as well
  Serial.print("JS1_Y: ");
  Serial.print(JS1_Y);
  Serial.print("  ");
  Serial.print("JS1_X: ");
  Serial.print(JS1_X);
  Serial.print("  ");
  Serial.print("JS2_Y: ");
  Serial.print(JS2_Y);
  Serial.print("  ");
  Serial.print("JS2_X: ");
  Serial.print(JS2_X);
  Serial.print("  ");
  Serial.print("SP1_CMD: ");
  Serial.print(SP1_CMD);
  Serial.print("SP2_CMD: ");
  Serial.print(SP2_CMD);
  Serial.print("SP3_CMD: ");
  Serial.print(SP3_CMD);
  Serial.print("SP4_CMD: ");
  Serial.print(SP4_CMD);

  // end of the print line
  Serial.println(" ");
}
