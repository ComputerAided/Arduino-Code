/*-------------------------------------------
  Analog_Joystick_Simple
  By: Kenny H.
  Last Updated: 4-17-2016
  Compiled with Arduino 1.6.8

  Released under an MIT License:

  The MIT License (MIT)
  Copyright (c) 2016 Kenny H.

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
  -------------------------------------------*/

//Pins used for I/O
#define HPin 1
#define VPin 0
#define SelPin 2
#define UpLED    13
#define DownLED  11
#define LeftLED  10
#define RightLED 12

//Joystick Minimum Values
#define H_Min 2
#define V_Min 0
//Joystick Mid Values
#define H_Mid 500
#define V_Mid 522
//Joystick Max Values
#define H_Max 1018
#define V_Max 1028
//Threshold values for triggering
#define threshold 256
#define nthreshold -256
//change to 1 to use serial port
#define Serial_Enable 0
#if Serial_Enable
#define DebounceTime 50
#endif


void setup() {
  pinMode(UpLED, OUTPUT);
  pinMode(DownLED, OUTPUT);
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);

  #if Serial_Enable
  //Uses SEL pin on Sparkfun analog Joystick as input
  pinMode(SelPin, INPUT_PULLUP);
  //Opens up Serial port for Output
  Serial.begin(9600);
  #endif
  
}

void loop() {
  //Works only if Serial_Enable is set to 1. Used for reporting values over Serial.
  #if Serial_Enable
  //receives char from Serial port and assigns it to rchar
  char rchar;
  if (Serial.available() > 0) {
    rchar = Serial.read();
    Serial.flush();
  }
  
  //if SEL button pressed or the arduino recieves 'r' from the serial port,it will display information.
  if (digitalRead(SelPin) == false) {
    delay(DebounceTime);                                            //Software button debouncing
    if (digitalRead(SelPin) == false){
      uint16_t hval = analogRead(HPin);
      uint16_t vval = analogRead(VPin);
      
      Serial.print("The Horizontal Value is:");
      Serial.print(hval);
      Serial.print("The Vertical Value is:");
      Serial.print(vval);
      Serial.println();
      rchar = 0;
      delay(750);

    }
  }

  if (rchar == 'r') {
    uint16_t hval = analogRead(HPin);
    uint16_t vval = analogRead(VPin);
    
    Serial.print("The Horizontal Value is:");
    Serial.print(hval);
    Serial.print("The Vertical Value is:");
    Serial.print(vval);
    Serial.println();
    rchar = 0;
  }
  #endif

/*-----------------------------------------------------------------------------------------------------Main Loop------------------------------------------------------------------------------------------------------------*/ 
  int16_t hval = (analogRead(HPin) - H_Mid);
  int16_t vval = (analogRead(VPin) - V_Mid);

  if (hval > threshold){
    digitalWrite(RightLED, HIGH);
    digitalWrite(LeftLED, LOW);
  } else if (hval < nthreshold) {
    digitalWrite(LeftLED, HIGH);
    digitalWrite(RightLED, LOW);
  } else {
    digitalWrite(LeftLED, LOW);
    digitalWrite(RightLED, LOW);
  }
  
  if (vval > threshold) {
    digitalWrite(DownLED, HIGH);
    digitalWrite(UpLED, LOW);
  } else if (vval < nthreshold) {
    digitalWrite(UpLED, HIGH);
    digitalWrite(DownLED, LOW);
  } else {
    digitalWrite(UpLED, LOW);
    digitalWrite(DownLED, LOW);
  }
}
