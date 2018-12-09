
#include <Wire.h>

// joystick pins
//
//PIN A0 - JS1 Y-AXIS
//PIN A1 - JS2 X-AXIS
//PIN A2 - JS2 Y-AXIS
//PIN A3 - JS1 X-AXIS
// THESE WERE TESTED BUT THEY 
// SHOULD BE TESTED AGAIN
int JS1_Y_PIN = A0;
int JS1_X_PIN = A3;
int JS2_Y_PIN = A2;
int JS2_X_PIN = A1;
int JS1_Y;
int JS1_X;
int JS2_Y;
int JS2_X;

// speed output pins
// not sure of the outputs yet,
// so we will just put in place
// holders
int SP1 = 8;
int SP2 = 9;
int SP3 = 10;
int SP4 = 11;

// reverse pins
// not too sure of these outputs
// yet so we will just put in 
// some placeholders
int REV1 = 22;
int REV2 = 24;
int REV3 = 26;
int REV4 = 28;

// strife speed in percentage
int STRIFE_SPEED = 50;

// variable to detect if the 
// kart is in strife mode.
bool STRIFE_LEFT = 0;
bool STRIFE_RIGHT = 0;

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
  JS1_Y = analogRead(JS1_Y_PIN);
  JS1_X = analogRead(JS1_X_PIN);
  JS2_Y = analogRead(JS2_Y_PIN);
  JS2_X = analogRead(JS2_X_PIN);

  // the joysticks at center center are at 500, 500
  // roughly. Less than 500 is backwards
  // so, lets control the high control output first. we 
  // need a little "slop" in the  
  // first we need to check the mode

  // determine if we are in strife mode
  // when both joysticks x-values are certain
  // critirea
  if(JS1_X < 100 and JS2_X < 100){
    STRIFE_LEFT = 1;

    // put the correct motor in
    // reverse
  }
  else{
    STRIFE_LEFT = 0;
    
    // put the correct motor in
    // forward
  }
  if(JS1_X > 850 and JS2_X > 850){
    STRIFE_RIGHT = 1;
    
    // put the correct motor in
    // reverse
  }
  else{
    STRIFE_RIGHT = 0;
    
    // put the correct motor in
    // forward
  }

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
}
