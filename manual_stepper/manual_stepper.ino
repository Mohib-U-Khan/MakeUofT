/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-stepper-motor-28byj-48-uln2003/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  Based on Stepper Motor Control - one revolution by Tom Igoe
*/

#include <Stepper.h>
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins A
#define IN1A 19
#define IN2A 18
#define IN3A 5
#define IN4A 17

// ULN2003 Motor Driver Pins B
#define IN1B 32
#define IN2B 33
#define IN3B 25
#define IN4B 26



// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1A, IN3A, IN2A, IN4A);
Stepper myStepperB(stepsPerRevolution, IN1B, IN3B, IN2B, IN4B);

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(10);
  myStepperB.setSpeed(10);
  // initialize the serial port
  Serial.setTimeout(1);
  Serial.begin(115200);
}

int ds = 30;
int xp = 0;
int yp = 0;
bool manual = 0;


bool started = 0;
bool rdX = 0;
bool reading_num = 0;

String buff = "";
uint16_t xarr[1024] = { 0 };
uint16_t yarr[1024] = { 0 };
int xctr = 0, yctr = 0;
int arrctr = 0;



void loop() {
  while (Serial.available() > 0) {

    char inch = Serial.read();
    switch (inch) {
      case 'w':  // up
        myStepperB.step(ds);
        yp += ds;
        break;
      case 'a':
        myStepper.step(-ds);
        xp -= ds;
        break;
      case 's':
        myStepperB.step(-ds);
        yp -= ds;
        break;
      case 'd':
        myStepper.step(ds);
        xp += ds;
        break;
      case 'o':
        xp = 0;
        yp = 0;
        break;
      case 'm':
        manual = !manual;
        Serial.println(manual ? "manual" : "automatic (q)");
        break;
      case 'q':
        if (manual) break;
        myStepperB.step(-1024);
        myStepper.step(-1024);
        myStepperB.step(1024);
        myStepper.step(1024);
        break;
    }
  }
  //endwhile
  // buff += c;
  // char c = Serial.read();
  // if(c == '#'){
  //   started=1;
  //   rdX = 1;
  // } // start
  // if(c == '!') started=0; //end
  // if(c == 'U') continue; //servo up
  // if(c == 'D') continue; //servo dwn

  // if(started){
  //   if(isdigit(c)&&!reading_num){
  //     char d = Serial.read()-'0';
  //     // draw from current to (c,d)

  //   }
  // }

  // char inch = Serial.read();
  // switch(inch){
  //   case 'w':  // up
  //     myStepperB.step(ds);
  //     yp+=ds;
  //     break;
  //   case 'a':
  //     myStepper.step(-ds);
  //     xp-=ds;
  //     break;
  //   case 's':
  //     myStepperB.step(-ds);
  //     yp-=ds;
  //     break;
  //   case 'd':
  //     myStepper.step(ds);
  //     xp+=ds;
  //     break;
  //   case 'o':
  //     xp = 0;
  //     yp=0;
  //     break;
  //   case 'm':
  //   manual = !manual;
  //   Serial.println(manual?"manual":"automatic (q)");
  //   break;
  //   case 'q':
  //   if(manual) break;
  //     myStepperB.step(-1024);
  //     myStepper.step(-1024);
  //     myStepperB.step(1024);
  //     myStepper.step(1024);
  //     break;
  // }

  // Serial.print("x: ");
  // Serial.print(xp);
  // Serial.print(" y: ");
  // Serial.print(yp);
  // Serial.println();

  // if(buff!="")Serial.print(buff);

  // if(buff.length()>0){

  //   int coordCtr = 0;
  //   const char s[2] = " ";
  //   char *token;

  //   int str_len = buff.length() + 1;

  // // Prepare the character array (the buffer)
  //   char char_array[str_len];

  // // Copy it over
  //   buff.toCharArray(char_array, str_len);

  //   /* get the first token */
  //   token = strtok(char_array, " ");

  //   /* walk through other tokens */
  //   while( token != NULL ) {
  //     Serial.print("token --> ");
  //     Serial.println(token);
  //     if(isdigit(token[0])){
  //       if(coordCtr%2==0){
  //         xarr[xctr] = atoi(token);
  //         Serial.print("add x ");
  //         Serial.println(xarr[xctr]);
  //         xctr++;
  //       }else{
  //         yarr[yctr] = atoi(token);
  //         Serial.print("add y ");
  //         Serial.println(yarr[yctr]);
  //         yctr++;
  //       }
  //       coordCtr++;
  //     }
  //     else{
  //       if(token[0] == 'U'){
  //         xarr[xctr++] = -1;
  //         yarr[yctr++] = -1;
  //         Serial.println("up");
  //       }
  //       if(token[0] == 'D'){
  //         xarr[xctr++] = -2;
  //         yarr[yctr++] = -2;
  //         Serial.println("down");
  //       }
  //     }
  //     token = strtok(NULL, s);
  //  }
  // }

  buff = "";
  // // step one revolution in one direction:
  // Serial.println("clockwise");
  // myStepper.step(stepsPerRevolution);
  // myStepperB.step(stepsPerRevolution);

  // delay(1000);

  // // step one revolution in the other direction:
  // Serial.println("counterclockwise");
  // myStepper.step(-stepsPerRevolution);
  // myStepperB.step(-stepsPerRevolution);
  // delay(1000);
}