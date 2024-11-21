/*
 * command.h
 *
 *  Created on: 30 Eki 2024
 *      Author: ahmet
 */

#ifndef MAIN_COMMAND_H_
#define MAIN_COMMAND_H_


#include "stdio.h"

void process_command(char* command,uint16_t Size);
void log_cmd(int log_types, const char *format, ...);

#define TAG "CMD_LOG"

#define  RST    "rst"      //Sistem(STM32) resetleme
#define  RSTE    "erst"      //Sistem(ESP32) resetleme
#define  RSTS    "srst"      //Sistem(ESP32) resetleme

#define  ESP    "esp"      //Sistem(STM32) resetleme
#define  STM    "stm"      //Sistem(STM32) resetleme
#define  DELETE "del"       //Program silme
#define  APP    "app"        //Programa geç
#define  BOT    "bot"        //Programa geç
#define  START  "goo"        //Program almayı başlat

#define  CHECK "check"       //CRC ALMA
#define  CRCX "crc="       //CRC ALMA
#define  LENGHT "len="    //Program boyutunu alma
#define  CRCQ "crc"    //Program hafızayı kilitle

#define  OFF "off"    //Program hafızayı kilitle
#define  ON "onn"    //Program hafızayı kilitle

#define  PRE "pre"      //Sistem resetleme
#define  PRD "prd"      //Sistem resetleme


#define  LEN "len="      //gelen binary boyutunu ögrenme



////////////////////////////////////    dwm1000

#define  ANC    "anc="      //Wifi conf alm
#define  SYNC   "sync="      //Wifi conf alma
#define  RATIO  "err="      //Wifi conf alma
#define  TAG    "tag="      //Wifi conf alma
#define  DWM    "dw"      //Wifi conf alma

////////////////////////////////////  modem

#define  CONF    "conf="      //Wifi conf alma
#define  PORT    "port="      //Wifi conf alma
#define  IP    "ip="      //Wifi conf alma

#define  INF    "info"        //Programa geç

// Gönderim türlerini bit alanları olarak tanımlıyoruz
#define LOG_BT       (1 << 0)
#define LOG_TCP      (1 << 1)
#define LOG_ESP_INFO (1 << 2)
#define LOG_ESP_ERROR (1 << 3)

#endif /* MAIN_COMMAND_H_ */
