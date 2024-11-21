/*
 * bluetooth.c
 *
 *  Created on: 16 Eki 2024
 *      Author: ahmet
 */
#include "bluetooth.h"
#include "Bootloader.h"
#include "command.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"
#include "string.h"

#include <sys/_intsup.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Bluetooth tanımlamaları
#define SPP_SERVER_NAME "SPP_SERVER"
#define DEVICE_NAME "AET_RTLS_ANCHOR"
static const char *BT_TAG = "BT_SPP";

esp_spp_cfg_t spp_config = {
    .mode = ESP_SPP_MODE_CB,  // ya da uygun olan modu seçin
    // diğer yapılandırma ayarlarını da buraya ekleyebilirsiniz
};

static bool bt_initialized = false;
static uint32_t spp_client = 0;  // SPP bağlantı handle'ı

// Bluetooth SPP etkinlik işlemcisi
void spp_event_handler(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
    case ESP_SPP_INIT_EVT:
        ESP_LOGI(BT_TAG, "ESP_SPP_INIT_EVT");
        esp_bt_dev_set_device_name(DEVICE_NAME);
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        esp_spp_start_srv(ESP_SPP_SEC_ENCRYPT, ESP_SPP_ROLE_SLAVE, 0, SPP_SERVER_NAME);
        break;

    case ESP_SPP_SRV_OPEN_EVT:  // Bu olayı ekliyoruz
        ESP_LOGI(BT_TAG, "ESP_SPP_SRV_OPEN_EVT");
        spp_client = param->srv_open.handle;  // Bağlantı handle'ını kaydet
        ESP_LOGI(BT_TAG, "Sunucu bağlantısı açıldı. Handle: %" PRIu32, spp_client);
        break;

    case ESP_SPP_DATA_IND_EVT:
        ESP_LOGI(BT_TAG, "ESP_SPP_DATA_IND_EVT");
        ESP_LOGI(BT_TAG, "Alinan veri: %.*s", param->data_ind.len, param->data_ind.data);
        process_command((char *)param->data_ind.data, param->data_ind.len);
        break;

    case ESP_SPP_CLOSE_EVT:  // Bağlantı kesildiğinde
        ESP_LOGI(BT_TAG, "ESP_SPP_CLOSE_EVT: Baglanti kesildi");
        spp_client = 0;  // Bağlantı handle'ını sıfırla
        break;

    default:
        ESP_LOGI(BT_TAG, "Bilinmeyen SPP olayi: %d", event);
        break;
    }
}


void bt_init() {
    if (bt_initialized) {
        return;
    }
    ESP_LOGI(BT_TAG, "Bluetooth baslatiliyor...");
    esp_err_t ret;

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        ESP_LOGE(BT_TAG, "Bluetooth controller initialization failed: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    if (ret) {
        ESP_LOGE(BT_TAG, "Bluetooth controller enable failed: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(BT_TAG, "Bluedroid stack initialization failed: %s", esp_err_to_name(ret));
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(BT_TAG, "Bluedroid stack enable failed: %s", esp_err_to_name(ret));
        return;
    }

    esp_bt_gap_register_callback(bt_gap_cb);

    ret = esp_spp_register_callback(spp_event_handler);
    if (ret != ESP_OK) {
        ESP_LOGE(BT_TAG, "SPP callback registration failed: %s", esp_err_to_name(ret));
        return;
    }

    ret =esp_spp_enhanced_init(&spp_config);
    if (ret != ESP_OK) {
        ESP_LOGE(BT_TAG, "SPP initialization failed: %s", esp_err_to_name(ret));
        return;
    }
    bt_initialized = true;
    ESP_LOGI(BT_TAG, "Bluetooth baslatildi ve baglanti hazir.");
}

void bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT:
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_TAG, "Authentication Success: %s", param->auth_cmpl.device_name);
        } else {
            ESP_LOGE(BT_TAG, "Authentication Failed, status: %d", param->auth_cmpl.stat);
        }
        break;
    default:
        ESP_LOGI(BT_TAG, "Unknown GAP event: %d", event);
        if (param != NULL) {
            ESP_LOGI(BT_TAG, "GAP event details: status: %d", param->auth_cmpl.stat);
        }
        break;
    }
}

// Bluetooth devre dışı bırakma fonksiyonu
void bt_deinit() {
    if (!bt_initialized) {
        return;
    }
    esp_spp_deinit();
    esp_bluedroid_disable();
    esp_bluedroid_deinit();
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
    bt_initialized = false;
    ESP_LOGI(BT_TAG, "Bluetooth devre disi.");
}

// Bluetooth üzerinden veri gönderme fonksiyonu
void bt_send_data(const char *data) {
    if (bluetooth_is_enabled() && spp_client != 0) {
        esp_err_t err = esp_spp_write(spp_client, strlen(data), (uint8_t *)data);
        if (err == ESP_OK) {
            ESP_LOGI(BT_TAG, "Veri gonderildi: %s", data);
        } else {
            ESP_LOGE(BT_TAG, "Veri gonderme hatasi: %s", esp_err_to_name(err));
        }
    } else {
        ESP_LOGE(BT_TAG, "Bagli bir cihaz yok veya spp_client handle'ı tanımlanmamış, veri gönderilemedi.");
    }
}
// Bluetooth üzerinden veri gönderme fonksiyonu
void bt_send_char(char* data,int len ) {
    if (bluetooth_is_enabled() && spp_client != 0) {
        esp_err_t err = esp_spp_write(spp_client,len, (uint8_t *)data);
        if (err == ESP_OK) {
            ESP_LOGI(BT_TAG, "Veri gonderildi: %s", data);
        } else {
            ESP_LOGE(BT_TAG, "Veri gonderme hatasi: %s", esp_err_to_name(err));
        }
    } else {
        ESP_LOGE(BT_TAG, "Bagli bir cihaz yok veya spp_client handle'ı tanımlanmamış, veri gönderilemedi.");
    }
}
void bt_send(const char* format, ...) {
	
   static char send_data[128];  // Göndermek istediğiniz veriyi tutacak buffer
   static  va_list args;
        
        va_start(args, format);
        vsnprintf(send_data, sizeof(send_data), format, args);  // Formatlı string oluşturuluyor
        va_end(args);
    
    // tcp üzerinden gönderiliyor
    bt_send_data(send_data);
}

bool bluetooth_is_enabled() {
    return esp_bluedroid_get_status() == ESP_BLUEDROID_STATUS_ENABLED;
}

void process_command_ble(char* command, uint16_t size) {

}
