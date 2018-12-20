
// motor profiles
// ----------------------------
// PROFILE CONSTANTS
#define int LINEAR = 1;
#define int PARABOLIC_RAMP = 2;

//----------------------------------------
// IF YOU WANT PARABOLIC, SWITCH THIS
// VARUABLE.
//---------------------------------------
int SELECTED_MOTOR_PROFILE = LINEAR;

int LINEAR_SLOPE = 1;
int LINEAR_OFFSET = 0;

// joystick pins
// ----------------------------
// JS705 - LEFT JOYSTICKS
// ----------------------------
JS705_X_PIN = A0;
JS705_Y_PIN = A1;

// ----------------------------
// JS711 - RIGHT JOYSTICKS
// ----------------------------
JS711_X_PIN = A2;
JS711_Y_PIN = A3;

// ----------------------------
// M208 FRONT LEFT PINS
//-----------------------------
M208_L_EN = 22;
M208_R_EN = 23;
//M208_L_I = XX;
//M208_R_I = XX;
M208_L_PWM = 2;
M208_R_PWM = 3;

// ----------------------------
// M308 REAR LEFT PINS
//-----------------------------
M308_L_EN = 24;
M308_R_EN = 25;
//M308_L_I = XX;
//M308_R_I = XX;
M308_L_PWM = 4;
M308_R_PWM = 5;

// ----------------------------
// M408 FRONT RIGHT PINS
//-----------------------------
M408_L_EN = 26;
M408_R_EN = 27;
//M408_L_I = XX;
//M408_R_I = XX;
M408_L_PWM = 6;
M408_R_PWM = 7;

// ----------------------------
// M508 REAR RIGHT PINS
//-----------------------------
M508_L_EN = 28;
M508_R_EN = 29;
//M508_L_I = XX;
//M508_R_I = XX;
M508_L_PWM = 8;
M508_R_PWM = 9;

// 

void setup() {
  // put your setup code here, to run once:
  
  // set the motor enable pin modes
  pinMode(M208_L_EN, OUTPUT);
  pinMode(M208_R_EN, OUTPUT);
  pinMode(M308_L_EN, OUTPUT);
  pinMode(M308_R_EN, OUTPUT);
  pinMode(M408_L_EN, OUTPUT);
  pinMode(M408_R_EN, OUTPUT);
  pinMode(M508_L_EN, OUTPUT);
  pinMode(M508_R_EN, OUTPUT);

  // put the enable bits low initially
  digitalWrite(M208_L_EN, LOW);
  digitalWrite(M208_R_EN, LOW);
  digitalWrite(M308_L_EN, LOW);
  digitalWrite(M308_R_EN, LOW);
  digitalWrite(M408_L_EN, LOW);
  digitalWrite(M408_R_EN, LOW);
  digitalWrite(M508_L_EN, LOW);
  digitalWrite(M508_R_EN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
