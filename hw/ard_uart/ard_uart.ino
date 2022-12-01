/**
 * @file ard_uart.ino
 * @author Andrew Woska ( andrew@woska.org )
 * @brief Arduino UART design for communicating with ESP32
 * @version 0.1
 * @date 2022-11-29
 * @warning not intended to run while ESP32 is being flashed
 * 
 * last updated 2022-11-30
 */

#include "ard_uart.h"

/* macros */

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

/* global variables */

bool query; // is query command send
int state;  // current motor state

/* implementation */

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);   // serial monitor
  #endif // DEBUG
  Serial1.begin(9600);  // UART to ESP
  pinMode(13, OUTPUT);  // on-board LED
  query = false;
  state = MOTOR_OFF;
}

void loop() {
  uart_read();
  uart_write();
  delay(100);
}


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
