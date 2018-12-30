
// joystick pins
// ----------------------------
// JS705 - LEFT JOYSTICKS
// ----------------------------
int JS705_X_PIN = A0;
int JS705_Y_PIN = A1;
// joystick current value
int JS705_X = 0;
int JS705_Y = 0;

// ----------------------------
// JS711 - RIGHT JOYSTICKS
// ----------------------------
int JS711_X_PIN = A2;
int JS711_Y_PIN = A3;
// joystick current value
int JS711_X = 0;
int JS711_Y = 0;

// -----------------------------
// Joy stick thresholds
// -----------------------------
int JS_FWD = 520; // beyond this value will enable forward motion
int JS_REV = 480; // less then this value will enable reverse motion
int JS_STRAFE_LOW = 20;
int JS_STRAFE_HIGH = 1000;

// ----------------------------
// M208 FRONT LEFT PINS
//-----------------------------
int M208_L_EN = 22;
int M208_R_EN = 23;
int M208_L_I = 33;
int M208_R_I = 32;
int M208_L_PWM = 2;
int M208_R_PWM = 3;

// ----------------------------
// M308 REAR LEFT PINS
//-----------------------------
int M308_L_EN = 24;
int M308_R_EN = 25;
int M308_L_I = 31;
int M308_R_I = 30;
int M308_L_PWM = 4;
int M308_R_PWM = 5;

// ----------------------------
// M408 FRONT RIGHT PINS
//-----------------------------
int M408_L_EN = 26;
int M408_R_EN = 27;
int M408_L_I = 35;
int M408_R_I = 34;
int M408_L_PWM = 6;
int M408_R_PWM = 7;

// ----------------------------
// M508 REAR RIGHT PINS
//-----------------------------
int M508_L_EN = 28;
int M508_R_EN = 29;
int M508_L_I = 37;
int M508_R_I = 36;
int M508_L_PWM = 8;
int M508_R_PWM = 9;

// MOTOR SPEEDS
int M208_SPEED = 0;
int M308_SPEED = 0;
int M408_SPEED = 0;
int M508_SPEED = 0;

// motor enable values
bool M208_L_EN_VAL = false;
bool M208_R_EN_VAL = false;
bool M308_L_EN_VAL = false;
bool M308_R_EN_VAL = false;
bool M408_L_EN_VAL = false;
bool M408_R_EN_VAL = false;
bool M508_L_EN_VAL = false;
bool M508_R_EN_VAL = false;


// strafe booleans
bool strafe_left = false;
bool strafe_right = false;
int strafe_speed = 128;

void setup() {
  // put your setup code here, to run once:

  // initiate serial comms on baud 9600
  Serial.begin(9600);
  
  // set the motor enable pin modes
  pinMode(M208_L_EN, OUTPUT);
  pinMode(M208_R_EN, OUTPUT);
  pinMode(M308_L_EN, OUTPUT);
  pinMode(M308_R_EN, OUTPUT);
  pinMode(M408_L_EN, OUTPUT);
  pinMode(M408_R_EN, OUTPUT);
  pinMode(M508_L_EN, OUTPUT);
  pinMode(M508_R_EN, OUTPUT);
  pinMode(M208_L_I, INPUT);
  pinMode(M208_R_I, INPUT);
  pinMode(M308_L_I, INPUT);
  pinMode(M308_R_I, INPUT);
  pinMode(M408_L_I, INPUT);
  pinMode(M408_R_I, INPUT);
  pinMode(M508_L_I, INPUT);
  pinMode(M508_R_I, INPUT);

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

float scp(int input, int rmin, int rmax, int smin, int smax){
  // this routine takes in a raw input value
  // plus parameters and will return the scaled 
  // output
  float slope;
  float slope_numerator;
  float slope_denominator;
  float inter;
  float output;

  // slope is rise over run
  slope_numerator = smax - smin;
  slope_denominator = rmax - rmin;
  slope = slope_numerator / slope_denominator;

  // intercept calculation
  inter = smax - slope*rmax;

  output = input*slope+inter;

  // return value (line formula)
  return output;
}

void enable_motor(int motor_number){
  if(motor_number == 208){
    digitalWrite(M208_L_EN, HIGH);
    digitalWrite(M208_R_EN, HIGH);
    M208_L_EN_VAL = true;
    M208_R_EN_VAL = true;
  }
  if(motor_number == 308){
    digitalWrite(M308_L_EN, HIGH);
    digitalWrite(M308_R_EN, HIGH);
    M308_L_EN_VAL = true;
    M308_R_EN_VAL = true;    
  }
  if(motor_number == 408){
    digitalWrite(M408_L_EN, HIGH);
    digitalWrite(M408_R_EN, HIGH);
    M408_L_EN_VAL = true;
    M408_R_EN_VAL = true;    
  }
  if(motor_number == 508){
    digitalWrite(M508_L_EN, HIGH);
    digitalWrite(M508_R_EN, HIGH);
    M508_L_EN_VAL = true;
    M508_R_EN_VAL = true;    
  }
}
void disable_motor(int motor_number){
  if(motor_number == 208){
    digitalWrite(M208_L_EN, LOW);
    digitalWrite(M208_R_EN, LOW);
    M208_L_EN_VAL = false;
    M208_R_EN_VAL = false;
  }
  if(motor_number == 308){
    digitalWrite(M308_L_EN, LOW);
    digitalWrite(M308_R_EN, LOW);
    M308_L_EN_VAL = false;
    M308_R_EN_VAL = false;
  }
  if(motor_number == 408){
    digitalWrite(M408_L_EN, LOW);
    digitalWrite(M408_R_EN, LOW);
    M408_L_EN_VAL = false;
    M408_R_EN_VAL = false;
  }
  if(motor_number == 508){
    digitalWrite(M508_L_EN, LOW);
    digitalWrite(M508_R_EN, LOW);
    M508_L_EN_VAL = false;
    M508_R_EN_VAL = false;
  }
}

void send_motor_speed(int motor_number, bool reverse, int motor_speed_int){
  if(motor_number == 208){
    if(reverse){
      analogWrite(M208_R_PWM, 0);
      analogWrite(M208_L_PWM, motor_speed_int);
    }
    else{
      analogWrite(M208_L_PWM, 0);
      analogWrite(M208_R_PWM, motor_speed_int);
    }
  }
  if(motor_number == 308){
    if(reverse){
      analogWrite(M308_R_PWM, 0);
      analogWrite(M308_L_PWM, motor_speed_int);
    }
    else{
      analogWrite(M308_L_PWM, 0);
      analogWrite(M308_R_PWM, motor_speed_int);
    }
  }
  if(motor_number == 408){
    if(reverse){
      analogWrite(M408_R_PWM, 0);
      analogWrite(M408_L_PWM, motor_speed_int);
    }
    else{
      analogWrite(M408_L_PWM, 0);
      analogWrite(M408_R_PWM, motor_speed_int);
    }
  }
  if(motor_number == 508){
    if(reverse){
      analogWrite(M508_R_PWM, 0);
      analogWrite(M508_L_PWM, motor_speed_int);
    }
    else{
      analogWrite(M508_L_PWM, 0);
      analogWrite(M508_R_PWM, motor_speed_int);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the joystick positions
  JS705_X = analogRead(JS705_X_PIN);
  JS705_Y = analogRead(JS705_Y_PIN);
  JS711_X = analogRead(JS711_X_PIN);
  JS711_Y = analogRead(JS711_Y_PIN);

  //Serial.print("JS705_X=");
  //Serial.print(JS705_X);
  //Serial.print("    JS705_Y=");
  //Serial.print(JS705_Y);
  //Serial.print("    JS711_X=");
  //Serial.print(JS711_X);
  //Serial.print("    JS711_Y=");
  //Serial.println(JS711_Y);

  // STRAFE MODE LOGIC
  if((JS705_Y >= JS_STRAFE_HIGH) and (JS711_Y >= JS_STRAFE_HIGH)){
    strafe_left = true;
  }
  else{
    strafe_left = false;
  }
  if((JS705_Y <= JS_STRAFE_LOW) and (JS711_Y <= JS_STRAFE_LOW)){
    strafe_right = true;
  }
  else{
    strafe_right = false;
  }

  if(strafe_right or strafe_left){

    // enable the motors
    enable_motor(208);
    enable_motor(308);
    enable_motor(408);
    enable_motor(508);

    // set the speed values
    M208_SPEED = strafe_speed;
    M308_SPEED = strafe_speed;
    M408_SPEED = strafe_speed;
    M508_SPEED = strafe_speed;
   
    if(strafe_left){
      // send the motor speeds and directions
      send_motor_speed(208, false, M208_SPEED);
      send_motor_speed(308, true, M308_SPEED);
      send_motor_speed(408, true, M408_SPEED);
      send_motor_speed(508, false, M508_SPEED);
    }
    if(strafe_right){
      // send the motor speeds and directions
      send_motor_speed(208, true, M208_SPEED);
      send_motor_speed(308, false, M308_SPEED);
      send_motor_speed(408, false, M408_SPEED);
      send_motor_speed(508, true, M508_SPEED);
    }
    
  }
  else{
    
    if((JS705_X > JS_FWD) or (JS705_X < JS_REV)){
  
      // enable the motors
      enable_motor(208);
      enable_motor(308);
      if(JS705_X > JS_FWD){
  
        M208_SPEED = scp(JS705_X, 500, 1023, 0, 255);
        send_motor_speed(208, false, M208_SPEED);
   
        M308_SPEED = scp(JS705_X, 500, 1023, 0, 255);
        send_motor_speed(308, false, M308_SPEED);
      
      }
      if(JS705_X < JS_REV){

        M208_SPEED = scp(JS705_X, 500, 0, 0, 255);
        send_motor_speed(208, true, M208_SPEED);
  
        M308_SPEED = scp(JS705_X, 500, 0, 0, 255);
        send_motor_speed(308, true, M308_SPEED);
      
      }
    
    }
    else{
      disable_motor(208);
      disable_motor(308);
      M208_SPEED = 0;
      M308_SPEED = 0;
      send_motor_speed(208, false, M208_SPEED);
      send_motor_speed(308, false, M308_SPEED);
    }
    
    if((JS711_X > JS_FWD) or (JS711_X < JS_REV)){
  
      // enable the motors
      enable_motor(408);
      enable_motor(508);
      if(JS711_X > JS_FWD){
  
        M408_SPEED = scp(JS711_X, 500, 1023, 0, 255);
        analogWrite(M408_L_PWM, M408_SPEED);
   
        M508_SPEED = scp(JS711_X, 500, 1023, 0, 255);
        analogWrite(M508_L_PWM, M508_SPEED);
      
      }
      if(JS711_X < JS_REV){
  
        M408_SPEED = scp(JS711_X, 500, 0, 0, 255);
        analogWrite(M408_R_PWM, M408_SPEED);

        M508_SPEED = scp(JS711_X, 500, 0, 0, 255);
        analogWrite(M508_R_PWM, M508_SPEED);
        
      }
      
    }
    else{
      disable_motor(408);
      disable_motor(508);
      M408_SPEED = 0;
      M508_SPEED = 0;
      send_motor_speed(408, false, M408_SPEED);
      send_motor_speed(508, false, M508_SPEED);
    } 
  }

  // print the motor enables
  //Serial.print("M208_L_EN_VAL=");
  //Serial.print(M208_L_EN_VAL);
  //Serial.print("    M208_R_EN_VAL=");
  //Serial.print(M208_R_EN_VAL);
  //Serial.print("    M308_L_EN_VAL=");
  //Serial.print(M308_L_EN_VAL);
  //Serial.print("    M308_R_EN_VAL=");
  //Serial.print(M308_R_EN_VAL);
  //Serial.print("    M408_L_RN_VAL=");
  //Serial.print(M408_L_EN_VAL);
  //Serial.print("    M408_R_EN_VAL=");
  //Serial.print(M408_R_EN_VAL);
  //Serial.print("    M508_L_EN_VAL=");
  //Serial.print(M508_L_EN_VAL);
  //Serial.print("    M508_R_EN_VAL=");
  //Serial.println(M508_R_EN_VAL);

  // print motor speeds
  Serial.print("M208_SPEED=");
  Serial.print(M208_SPEED);
  Serial.print("     M308_SPEED=");
  Serial.print(M308_SPEED);
  Serial.print("     M408_SPEED=");
  Serial.print(M408_SPEED);
  Serial.print("     M508_SPEED=");
  Serial.println(M508_SPEED);

  // print joystick values
  Serial.print("JS705_X=");
  Serial.print(JS705_X);
  Serial.print("      JS705_Y=");
  Serial.print(JS705_Y);
  Serial.print("      JS711_X=");
  Serial.print(JS711_X);
  Serial.print("      JS711_Y=");
  Serial.println(JS711_Y);

  // print strafe modes
  //Serial.print("strafe_left = ");
  //Serial.print(strafe_left);
  //Serial.print("       strafe_right=");
  //Serial.println(strafe_right);
}
