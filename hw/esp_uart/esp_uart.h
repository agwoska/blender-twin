/**
 * @file esp_uart.h
 * @author Andrew Woska ( andrew@woska.org )
 * @brief defines useful parts for UART communications for project
 * @version 0.1
 * @date 2022-11-29
 */

#pragma once

#ifndef ESP_UART_H
#define ESP_UART_H

/* constants */

// comment if no debug messages wanted
#define DEBUG

// motor commands
#define MOTOR_QUERY     ( 0x00 )
#define MOTOR_SPEED1    ( 0x01 )
#define MOTOR_SPEED2    ( 0x02 )
#define MOTOR_SPEED3    ( 0x04 )
#define MOTOR_OFF       ( 0x08 )

/* prototypes */

void uart_read();
void uart_write();

#endif // ESP_UART_H