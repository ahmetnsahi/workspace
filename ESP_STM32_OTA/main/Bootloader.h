/*
 * Bootloader.h
 *
 *  Created on: 14 Ağu 2024
 *      Author: ahmet
 */

#ifndef MAIN_BOOTLOADER_H_
#define MAIN_BOOTLOADER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LED_PIN GPIO_NUM_2  // LED'in bağlı olduğu pin numarası (GPIO2)
#define RESET_PIN GPIO_NUM_22  // Reset baglı pin
#define BOOT_PIN GPIO_NUM_23  //  Boot pini
#define POWER_PIN GPIO_NUM_21 //  Power pini normalde 0 yeni kartta 4
// UART ayarları
#define UART_PORT_NUM      UART_NUM_2
#define UART_BAUD_RATE     115200

#define UART_TX_PIN        GPIO_NUM_17
#define UART_RX_PIN        GPIO_NUM_16
#define UART_BUFFER_SIZE   1*1024
#define UART_DATA_BUFFER_SIZE   4*1024
 
#define  ack 0x79
#define nack 0x1f

// Yapı tanımı okuma için
typedef struct {
    uint8_t *data;  // Okunan veriyi tutacak dizi
    size_t length;  // Okunan veri miktarı
    int status;     // Okuma durumu (0: başarılı, negatif: hata)
} ReadResult;

//init func 
void init_bootloader();
void init_uartbootloader();

void init_gpiobootlader();
void deinit_uartbootloader();
//gpio func
void powerOn();
void powerOf();
void power_reset();

void set_boot0_high();
void set_boot0_low();
void reset_stm32() ;

void enter_bootloader_mode();
void exit_bootloader_mode();
void delay_ms(uint32_t time);


//bootlader func
uint8_t calculate_checksum(uint8_t N, uint8_t *data, uint32_t length);
void convert_endian(const uint8_t* data, uint16_t length, bool to_big_endian, uint8_t* output_buffer);
bool ack_control();
bool connectted_boot();
bool erase_full();
ReadResult read_data(uint32_t addres, uint16_t length);
bool write_block(uint32_t addres, uint8_t* data, uint16_t length); 
bool go_app(uint32_t addres);
bool RDP_Lock(void);
bool RDP_UnLock(void);
uint32_t get_crc(uint32_t addres,uint32_t sizeof_mem,uint32_t polynomial,uint32_t initial_value);
#endif /* MAIN_BOOTLOADER_H_ */
