#include "mController.h"
// /*
//     J4049 - Arduino Controlled GoKart. Version 2.0
//     Changes: Classes to control devices
//              Controls operate in different manner than
//              originally designed.
// */

// left joystick
JoyStick jsl(1, A0, A1, 0, 255, -100, 100);

// right joystick
JoyStick jsr(2, A2, A3, 0, 255, -100, 100);

// motor drivers side front
Motor mdsf(1, 3, 4, 2, -100, 100, 0, 255);

// motor passenger side front
Motor mpsf(2, 5, 4, 7, -100, 100, 0, 255);

// motor drivers side rear
Motor mdsr(3, 9, 8, 12, -100, 100, 0, 255);

// motor passenger side rear
Motor mpsr(4, 10, 11, 13, -100, 100, 0, 255);

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

  jsl.print_info();
  jsr.print_info();

}