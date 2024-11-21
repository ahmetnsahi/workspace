/*
 * uartread.h
 *
 *  Created on: 4 Eki 2024
 *      Author: ahmet
 */

#ifndef MAIN_UARTREAD_H_
#define MAIN_UARTREAD_H_

#include <stdbool.h>

#include <stdint.h>
void uart_event_task(void *pvParameters);
extern volatile bool uartmaincontrol; 
extern volatile bool uartoutflag;   
extern volatile bool infoflag; 
void init_uart();


#endif /* MAIN_UARTREAD_H_ */
