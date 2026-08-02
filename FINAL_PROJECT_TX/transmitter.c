#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"

#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"

#include "transmitter.h"

#define BUTTON_S GPIO_NUM_18
#define BUTTON_L GPIO_NUM_19

static uint8_t receiver_mac[] =
{
0x30, 0x76, 0xF5, 0xF4, 0x29, 0x44
};

void send_cb(const uint8_t *mac_addr,
esp_now_send_status_t status)
{
printf("Send Status: %s\n",
status == ESP_NOW_SEND_SUCCESS ?
"SUCCESS" : "FAIL");
}

void transmitter_init(void)
{
esp_err_t ret = nvs_flash_init();


if(ret == ESP_ERR_NVS_NO_FREE_PAGES ||
   ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
{
    nvs_flash_erase();
    nvs_flash_init();
}

gpio_set_direction(BUTTON_S, GPIO_MODE_INPUT);
gpio_set_pull_mode(BUTTON_S, GPIO_PULLUP_ONLY);

gpio_set_direction(BUTTON_L, GPIO_MODE_INPUT);
gpio_set_pull_mode(BUTTON_L, GPIO_PULLUP_ONLY);

esp_netif_init();
esp_event_loop_create_default();

wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

ESP_ERROR_CHECK(esp_wifi_init(&cfg));
esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
esp_wifi_start();

ESP_ERROR_CHECK(esp_now_init());

esp_now_register_send_cb(send_cb);

esp_now_peer_info_t peer = {0};

memcpy(peer.peer_addr, receiver_mac, 6);
peer.channel = 1;
peer.encrypt = false;

ESP_ERROR_CHECK(esp_now_add_peer(&peer));

printf("TRANSMITTER READY\n");

char pattern[10] = "";
int index = 0;
TickType_t last_press_time = 0;

while(1)
{
    if(gpio_get_level(BUTTON_S) == 0)
    {
        if(index < 9)
        {
            pattern[index++] = 'S';
            pattern[index] = '\0';
        }

        printf("Pattern: %s\n", pattern);

        last_press_time = xTaskGetTickCount();

        while(gpio_get_level(BUTTON_S) == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }

    if(gpio_get_level(BUTTON_L) == 0)
    {
        if(index < 9)
        {
            pattern[index++] = 'L';
            pattern[index] = '\0';
        }

        printf("Pattern: %s\n", pattern);

        last_press_time = xTaskGetTickCount();

        while(gpio_get_level(BUTTON_L) == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }

    if(index > 0)
    {
        TickType_t now = xTaskGetTickCount();

        if((now - last_press_time) > pdMS_TO_TICKS(1000))
        {
            esp_now_send(receiver_mac,
                         (uint8_t *)pattern,
                         strlen(pattern));

            printf("Sent Pattern: %s\n", pattern);

            memset(pattern, 0, sizeof(pattern));
            index = 0;
        }
    }

    vTaskDelay(pdMS_TO_TICKS(50));
}


}
