/*
    mController.h - Library for controlling a vehicle with joysticks
    Created by CJ Panici, Neechsoft, Inc. August 22, 2020
    Released to Ashley Webb and licensed for lifetime use
*/

//
// CanSheild link https://github.com/Seeed-Studio/CAN_BUS_Shield
// This can be used to figure out the can messaging
//
#ifndef mController_h
#define mController_h

#include "Arduino.h"

struct jspos{
    int x;
    int y;
};

class JoyStick{
    const int id;
    const int x_pin;
    const int y_pin;
    int x;
    int x_last;
    int y_last;
    int y;
    int x_raw;
    int y_raw;
    int r_min;
    int r_max;
    int s_min;
    int s_max;
    public:
        JoyStick(int id, int x_pin, int y_pin, int r_min, int r_max, int s_min, int s_max):
            id(id),
            x_pin(x_pin),
            y_pin(y_pin),
            r_min(r_min),
            r_max(r_max),
            s_min(s_min),
            s_max(s_max)
            {
                x = 0;
                y = 0;
            };
        void setup(){
            // nothing really to set up with this
        }
        struct jspos loop(){

            // return structure
            struct jspos jsposition;

            // gets the raw values
            x_raw = analogRead(x_pin);
            y_raw = analogRead(y_pin);

            // scale the values
            float s;
            float sn;
            float sd;
            float i;

            // some pre-calculations (for linear)
            sn = s_max - s_min;
            sd = r_max - r_min;
            s = sn / sd;
            i = s_max - (s * r_max);

            // caluclate the x
            x = x_raw * s + i;

            // calculate the y
            y = y_raw * s + i;

            jsposition.x = x;
            jsposition.y = y;

            return jsposition;
        }
        void print_info(){
            // should only print the information,
            // if the value has changed.
            if(x != x_last || y != y_last){
              Serial.print("JOYSTICK-");
              Serial.print(id);
              Serial.print(" X:");
              Serial.print(x);
              Serial.print(" Y:");
              Serial.print(y);
              Serial.println();
            }
            x_last = x;
            y_last = y;
        }
    // end public region  
};

class Motor{
    const int id;
    const int input_pin1;
    const int input_pin2;
    const int fwd_en_pin;
    const int rev_en_pin;
    const int fwd_pwm_pin;
    const int rev_pwm_pin;
    const int r_min;
    const int r_max;
    const int s_min;
    const int s_max;
    float r_speed;
    int pwm;
    int direction;
    bool enabled;
    public:
        Motor(int id, int input_pin1, int input_pin2, int fwd_en_pin, int rev_en_pin, int fwd_pwm_pin, int rev_pwm_pin, int r_min, int r_max, int s_min, int s_max):
            id(id),
            input_pin1(input_pin1),
            input_pin2(input_pin2),
            fwd_en_pin(fwd_en_pin),
            rev_en_pin(rev_en_pin),
            fwd_pwm_pin(fwd_pwm_pin),
            rev_pwm_pin(rev_pwm_pin),
            r_min(r_min),
            r_max(r_max),
            s_min(s_min),
            s_max(s_max)
            {
                direction = 0; // 0 = stopped/disabled, 1 = forward, 2 = reverse
                pwm = 0;
                enabled = false;
            };
        void update_enable_pins(){
            // makes sure the pins both can't be on
            if(enabled){
                digitalWrite(fwd_en_pin, HIGH);
                digitalWrite(rev_en_pin, HIGH);
            }else{
                digitalWrite(fwd_en_pin, LOW);
                digitalWrite(rev_en_pin, LOW);
            }
        }
        void update_pwm_pins(){
            
            // calculate the speed
            // scale the values
            float s;
            float sn;
            float sd;
            float i;

            // some pre-calculations (for linear)
            sn = s_max - s_min;
            sd = r_max - r_min;
            s = sn / sd;
            i = s_max - (s * r_max);

            // caluclate the speed
            pwm = r_speed * s + i;

            if(direction == 1){
                // set it out the pwm pin
                analogWrite(fwd_pwm_pin, pwm);
                analogWrite(rev_pwm_pin, 0);
            }else if(direction == 2){
                // set it out the pwm pin
                analogWrite(fwd_pwm_pin, 0);
                analogWrite(rev_pwm_pin, pwm);
            }else{
                analogWrite(fwd_pwm_pin, 0);
                analogWrite(rev_pwm_pin, 0);
            }
        }
        void enable(){
            enabled = true;
        }
        void disable(){
            enabled = false;
        }
        void set_speed(int raw_input){
            // sets the raw speed input.
            r_speed = raw_input; 
        }
        int get_input(int number){
            if(number==1){
                return digitalRead(input_pin1);
            }else if(number==2){
                return digitalRead(input_pin2);
            }else{
                return 0;
            }
        }
        int set_direction(int a_direction){
            // 0 = stopped
            // 1 = forward
            // 2 = reverse

            // assigns the new direction
            direction = a_direction;

            if(direction > 0){
                enable();
            }else{
                disable();
            }
        }
        void setup(){
            pinMode(fwd_en_pin, OUTPUT);
            pinMode(rev_en_pin, OUTPUT);
            pinMode(input_pin1, INPUT);
            pinMode(input_pin2, INPUT);
        }
        void loop(){

            // update the direction pins
            update_enable_pins();

            // updates the pwm pin
            update_pwm_pins();
        }
        void print_info(){
            Serial.print("MOTOR-");
            Serial.print(id);
            Serial.print(" enabled:");
            Serial.print(enabled);
            Serial.print(" DIRECTION:");
            Serial.print(direction);
            Serial.print(" PWM:");
            Serial.println(pwm);
        }
};
#endif
