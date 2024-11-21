/*
 * uartread.c
 *
 *  Created on: 4 Eki 2024
 *      Author: ahmet
 */

#include <stdint.h>
#include  <stdio.h> 
#include <stdbool.h>
#include "arch/sys_arch.h"
#include <driver/gpio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "Bootloader.h"
#include "esp_private/esp_task_wdt.h"
#include "hal/uart_types.h"
#include "lwip/sockets.h"
#include "uartread.h"
#include "esp_timer.h"
#include "socket.h"



#define BAUD_RATE          4000000

volatile bool uartmaincontrol=false;
volatile bool uartoutflag=true;
volatile bool infoflag=true;
#define BUFFER_SIZE   4*1024
static QueueHandle_t uart_queue;
 
bool uartTaskShouldExit = false;

static const char *TAG = "UART_ISR";
 
void uart_event_task(void *pvParameters) {
    // Sabit boyutta bir buffer tanımla
    uint8_t dtmp[UART_DATA_BUFFER_SIZE];
    
    
   while (uartmaincontrol) {
	   
	  // send(sock, "aaaaaaaaaaBaaaaaaa\n\r", 20, 0);  boş veri gönderimminden 13k kadar çıkıldı yaklaşık 3mbit
     esp_task_wdt_restart();
    int received_bytes = uart_read_bytes(UART_PORT_NUM, dtmp,UART_DATA_BUFFER_SIZE,pdMS_TO_TICKS(0)) ;
     if (received_bytes > 0 && infoflag) {
         // send(sock, dtmp, received_bytes, 0);
 
       }
          vTaskDelay(pdMS_TO_TICKS(10));
     
    }

    // Task sonlandırma işlemleri
    uart_flush(UART_PORT_NUM);
    uart_driver_delete(UART_PORT_NUM);

    ESP_LOGI(TAG, "Uart task Terminated.");
    uartoutflag = true;
    vTaskDelete(NULL);
}



void init_uart() {
    const uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk=UART_SCLK_APB
        
        
};
       // UART ayarlarını uygula
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT_NUM, UART_DATA_BUFFER_SIZE * 2, UART_DATA_BUFFER_SIZE * 2, 0, NULL, 0);

     // RX FIFO tam dolu eşiği (0-127 arası değer alabilir)
    uart_set_rx_full_threshold(UART_PORT_NUM, 30); // Örneğin 120 bayt
    // TX FIFO boş eşiği (0-127 arası değer alabilir)
    uart_set_tx_empty_threshold(UART_PORT_NUM, 1); // 
   
}

