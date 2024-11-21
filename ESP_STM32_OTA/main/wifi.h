/*
 * wifi.h
 *
 *  Created on: 25 Tem 2024
 *      Author: ahmet
 */

#ifndef MAIN_WIFI_H_
#define MAIN_WIFI_H_


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void wifi_init_sta(void);

void wifi_deinit_sta(void);
void wifi_restart();
extern volatile bool stop_events; 
#endif /* MAIN_WIFI_H_ */
