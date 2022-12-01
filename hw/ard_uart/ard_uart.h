/**
 * @file ard_uart.h
 * @author Andrew Woska ( andrew@woska.org )
 * @brief defines useful parts for UART communications for project
 * @version 0.1
 * @date 2022-11-29
 * 
 * last updated 2022-11-30
 */

#pragma once

#ifndef ARD_UART_H
#define ARD_UART_H

/* constants */

// comment if no debug messages wanted
#define DEBUG

// motor commands
#define MOTOR_QUERY     ( 0x00 )
#define MOTOR_SPEED1    ( 0x01 )
#define MOTOR_SPEED2    ( 0x02 )
#define MOTOR_SPEED3    ( 0x04 )
#define MOTOR_OFF       ( 0x08 )

/* function prototypes */

/**
 * @brief UART RX for receiving commands
 * reads 1-byte of data from ESP32
 */
void uart_read();

/**
 * @brief UART TX for sending commands if queried
 * sends 1-byte of data to ESP32
 * commands located above as _motor commands_
 */
void uart_write();

#endif // ARD_UART_H