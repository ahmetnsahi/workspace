/*
 * main.h
 *
 *  Created on: 8 Eki 2024
 *      Author: ahmet
 */

#ifndef MAIN_MAIN_H_
#define MAIN_MAIN_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"




void start_all_task();
bool stop_all_task();
void start_uart_task();
void stop_uart_task();
// Görev tanıtıcısı
void force_terminate_task(TaskHandle_t taskHandle) ;




#endif /* MAIN_MAIN_H_ */
