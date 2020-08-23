/*
    mController.h - Library for controlling a vehicle with joysticks
    Created by CJ Panici, Neechsoft, Inc. August 22, 2020
    Released to Ashley Webb and licensed for lifetime use
*/
#ifndef mController_h
#define mController_h

#include "Arduino.h"

class JoyStick{
    const int id;
    const int x_pin;
    const int y_pin;
    int x;
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
            }
        void setup(){
            // nothing really to set up with this
        }
        int, int loop(){

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

            return x, y;
        }
        void print_info(){
            Serial.print("JOYSTICK-");
            Serial.print(id);
            Serial.print(" X:");
            Serial.print(x);
            Serial.print(" Y:");
            Serial.print(y);
            Serial.println();
        }
    // end public region  
}

class Motor{
    const int id;
    const int pwm_pin;
    const int fwd_pin;
    const int rev_pin;
    const int r_min;
    const int r_max;
    const int s_min;
    const int s_max;
    float r_speed;
    int pwm;
    bool fwd;
    bool rev;
    public:
        Motor(int id, int pwm_pin, int fwd_pin, int rev_pin, int r_min, int r_max, int s_min, int s_max):
            id(id),
            pwm_pin(pwm_pin),
            fwd_pin(fwd_pin),
            rev_pin(rev_pin),
            r_min(r_min),
            r_max(r_max),
            s_min(s_min),
            s_max(s_max)
            {
                fwd = true;
                rev = false;
                pwm = 0;
            }
        void update_dir_pins(){
            // makes sure the pins both can't be on
            if(fwd && !rev){
                digitalWrite(fwd_pin, HIGH);
                digitalWrite(rev_pin, LOW);
            }
            else if(rev && !fwd){
                digitalWrite(fwd_pin, LOW);
                digitalWrite(rev_pin, HIGH);
            }
            else{
                // default is forward
                digitalWrite(fwd_pin, HIGH);
                digitalWrite(rev_pin, LOW);
            }
        }
        void update_pwm_pin(){
            
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

            // set it out the pwm pin
            analogWrite(pwm_pin, pwm)

        }
        bool is_forward(){
            return fwd;
        }
        bool is_reverse(){
            return rev;
        }
        void move_forward(){
            fwd = true;
            rev = false;
        }
        void move_reverse(){
            fwd = false;
            rev = true;
        }
        void set_speed(int raw_input){
            // sets the raw speed input.
            r_speed = raw_input;
        }
        int get_pwm(){
            return pwm;
        }
        void setup(){
            pinMode(fwd_pin, OUTPUT);
            pinMode(rev_pin, OUTPUT);
        }
        void loop(){

            // update the direction pins
            update_dir_pins();

            // updates the pwm pin
            update_pwm_pin();
        }
        void print_info(){
            Serial.print("MOTOR-");
            Serial.print(id);
            Serial.print(" FWD:");
            Serial.print(fwd);
            Serial.print(" REV:");
            Serial.print(rev);
            Serial.print(" PWM:");
            Serial.print(pwm);
            Serial.println();
        }
}