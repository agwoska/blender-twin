/**
 * @file esp_uart.ino
 * @author Andrew Woska ( andrew@woska.org )
 * @brief ESP32 UART design for communicating with ESP32
 *      currently set up for testing
 * @version 0.1
 * @date 2022-11-29
 * 
 * last updated: 2022-11-30
 */

#include "esp_uart.h"

#define DELAY   ( 10000 )
int i;

void setup() {
  pinMode(2, OUTPUT); // enable blue LED
  Serial.begin(9600); // enable UART
  delay(100);         // ensure UART availability for startup
  i = 0;
}

/**
 * @brief UART command message loop for Arduino
 * 
 */
void looper() {
  if ( i == 0 ) {
    Serial.write(MOTOR_QUERY);
    delay(DELAY);
  }
  else if ( i == 1 ) {
    Serial1.write(MOTOR_SPEED1);
    delay(DELAY);
  }
  else if ( i == 2 ) {
    Serial.write(MOTOR_SPEED2);
    delay(DELAY);
  }
  else {
    Serial.write(MOTOR_SPEED3);
    delay(DELAY);
    i = -1;
  }
  ++i;
}

void loop() {
  if (Serial.available()) { // UART RX available
    char in = Serial.read();// reads 1-byte
//    Serial.println(in, HEX);
    digitalWrite(2, HIGH);  // turn on LED
    delay(DELAY/2); // 5s
    digitalWrite(2, LOW);   // turn off LED
  }
  else {                    // UART TX; go to next command
    looper();
  }
}
