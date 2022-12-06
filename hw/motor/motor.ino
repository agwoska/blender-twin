/**
 * @file ard_uart.ino
 * @author Andrew Woska ( andrew@woska.org )
 * @author Arelson Rapisura
 * @author U Shin
 * @brief Arduino UART design for communicating with ESP32
 * @version 0.1
 * @date 2022-12-05
 * @warning not intended to run while ESP32 is being flashed
 * 
 * last updated 2022-12-06
 */

#include "ard_uart.h"

/* Macros */

// print safe
#ifdef DEBUG
#define prints(s) ( Serial.println(s) )
#else
#define prints() ()
#endif //DEBUG

// print safe hexidecimal
#ifdef DEBUG
#define printsh(s) ( Serial.println(s, HEX) )
#else
#define printsh() ()
#endif //DEBUG

/* implementation */

// Motor connections
int enA = 9;
int in1 = 8;
int in2 = 7;
int on_btn = 2;
int speed1_btn = 11;
int speed2_btn = 12;
int speed3_btn = 13;

//declaring initial button states
int  on_btn_state = 0;
int  speed1_btn_state = 0;
int  speed2_btn_state = 0;
int  speed3_btn_state = 0;

int  state = MOTOR_OFF;

//declaring if blender is on or off
bool on=false;

// if query command sent
bool query = false;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

  // Set buttons to input
  pinMode(on_btn, INPUT_PULLUP);
  pinMode(speed1_btn, INPUT_PULLUP);
  pinMode(speed2_btn, INPUT_PULLUP);
  pinMode(speed3_btn, INPUT_PULLUP);

	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

  // Serial.begin(9600);
  #ifdef DEBUG
  Serial.begin(9600);   // serial monitor
  #endif // DEBUG
  Serial1.begin(9600);  // UART to ESP
}

void loop() {
  //read button states
  on_btn_state = digitalRead(on_btn);
  speed1_btn_state = digitalRead(speed1_btn);
  speed2_btn_state = digitalRead(speed2_btn);
  speed3_btn_state = digitalRead(speed3_btn);

  // chech UART
  uart_read();
  uart_write();
  
  //Active low; if buttons are pressed
  if(on_btn_state==0 && on==false){
    setOn();
    on=true;
  }else if(on_btn_state==0 && on==true){
    setOff();
    on=false;
  }else if(speed1_btn_state==0 && on==true){
    setSpeed1();
  }else if(speed2_btn_state==0 && on==true){
    setSpeed2();
  }else if(speed3_btn_state==0 && on==true){
    setSpeed3();
  }
  delay(300);
}
 
//turn the blender on
void setOn(){
  state = MOTOR_SPEED1;
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  analogWrite(enA, 85);
}

//turn the blender off
void setOff(){
  state = MOTOR_OFF;
	analogWrite(enA, 85);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}

//set speed setting 1
void setSpeed1(){
  state = MOTOR_SPEED1;
	analogWrite(enA, 85);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

//set speed setting 2
void setSpeed2(){
  state = MOTOR_SPEED2;
	analogWrite(enA, 170);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

//set speed setting 3
void setSpeed3(){
  state = MOTOR_SPEED3;
	analogWrite(enA, 255);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}


/* function implementations */

void uart_read() {
  if (Serial1.available()) {  // check if command sent
    char in = Serial1.read(); // reads 1-byte
    printsh(in);              // prints debug statement
    if ( in == MOTOR_QUERY ) {
      prints("QUERY");
      query = true;
    }
    else if ( in == MOTOR_SPEED1 ) {
      prints("CHANGE to speed 1");
      state = MOTOR_SPEED1;
    }
    else if ( in == MOTOR_SPEED2 ) {
      prints("CHANGE to speed 2");
      state = MOTOR_SPEED2;
    }
    else if ( in == MOTOR_SPEED3 ) {
      prints("CHANGE to speed 3");
      state = MOTOR_SPEED3;
    }
    else {  // error; may be triggered by ESP32 flash
      prints("OTHER");
    }
  }
}

void uart_write() {
  if ( !query ) return;
  delay(100); // ensure availablility of UART
  Serial1.write(state);
  query = false;
}