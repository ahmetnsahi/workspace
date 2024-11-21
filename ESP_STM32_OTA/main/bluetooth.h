
/*
 * bluetooth.h
 *
 *  Created on: 16 Eki 2024
 *      Author: ahmet
 */

#ifndef MAIN_BLUETOOTH_H_
#define MAIN_BLUETOOTH_H_

#include "wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"


void bt_init(void);
void bt_deinit(void);
void bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);
void bt_send_data(const char *data);
void bt_send_char(char *data,int len );
bool bluetooth_is_enabled();
void bt_send(const char* format, ...) ;


#endif /* MAIN_BLUETOOTH_H_ */
