/**
 * @file ard_uart.ino
 * @author Andrew Woska ( andrew@woska.org )
 * @author Arelson Rapisura
 * @author U Shin
 * @brief Arduino UART design for communicating with ESP32
 * @version 0.1
 * @date 2022-12-06
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

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

int on_btn = 0;
int dir_btn = 11;
int speed2_btn = 12;
int speed3_btn = 13;

int on_btn_state = 0;
int dir_btn_state = 11;
int speed2_btn_state = 12;
int speed3_btn_state = 13;

bool on=false;


void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

  // Set buttons to input
  pinMode(on_btn, INPUT_PULLUP);
  pinMode(dir_btn, INPUT_PULLUP);
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


//------------ Turn ON/OFF ------------------------
void loop() {
  on_btn_state = digitalRead(on_btn);
  dir_btn_state = digitalRead(dir_btn); 
  speed2_btn_state = digitalRead(speed2_btn);
  speed3_btn_state = digitalRead(speed3_btn);

  Serial.println(on_btn_state); //pin 0
  if(on_btn_state==0 && on==false){
    setOn();
    on=true;
  }else if(on_btn_state==0 && on==true){
    setOff();
    on=false;
  }
  delay(100);

  //------- Changing the direction ------

  Serial.println(dir_btn_state); //pin 11
  if(dir_btn_state==0 && on==false){
    directionControl();
    on=true;
  }else if(dir_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);

  //------------ Speed: slow ---------------
  Serial.println(speed3_btn_state); //pin 13
  if(speed3_btn_state==0 && on==false){
    speedSlowControl();
    on=true;
  }else if(speed3_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);

  //------------ Speed: fast ---------------
  Serial.println(speed2_btn_state); //pin 11
  if(speed2_btn_state==0 && on==false){
    speedFastControl();
    on=true;
  }else if(speed2_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);
  //end
}


//This function lets you turn on the motor
void setOn(){
  Serial.println("motor on");
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

//This function lets you stop the motor
void setOff(){
  Serial.println("motor off");
	analogWrite(enA, 255);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}


// This function lets you control spinning direction of motors
void directionControl() {
	// Now change motor directions
  Serial.println("direction control: change direction");
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	delay(2000);
}


// This function lets you control speed of the motors
void speedFastControl() {
  Serial.println("Speed Control: Accelerating");
	for (int i = 0; i < 256; i++) {
		analogWrite(in1, i);
	}
}

// This function lets you control speed of the motors
void speedSlowControl() {
  Serial.println("Speed Control: Decelerating");
	for (int i = 255; i >= 0; --i) {
		analogWrite(in1, i);
		delay(20);
	}
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