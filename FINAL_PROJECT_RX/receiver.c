
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

#include "ssd1306.h"
#include "receiver.h"

#define MOTOR GPIO_NUM_23

extern SSD1306_t dev;

void short_vibration(void)
{
    gpio_set_level(MOTOR, 1);
    vTaskDelay(pdMS_TO_TICKS(300));
    gpio_set_level(MOTOR, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void long_vibration(void)
{
    gpio_set_level(MOTOR, 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_set_level(MOTOR, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void play_pattern(char *msg)
{
    for(int i = 0; i < strlen(msg); i++)
    {
        if(msg[i] == 'S')
        {
            short_vibration();
        }
        else if(msg[i] == 'L')
        {
            long_vibration();
        }
    }
}

static void recv_cb(const uint8_t *mac_addr,
                    const uint8_t *data,
                    int len)
{
    char msg[20];

    memset(msg, 0, sizeof(msg));
    memcpy(msg, data, len);

    printf("Received: %s\n", msg);

    ssd1306_clear_screen(&dev, false);

    if(strcmp(msg, "S") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:S", 9, false);
        ssd1306_display_text(&dev, 2, "YES", 3, false);
        play_pattern(msg);
    }
    else if(strcmp(msg, "L") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:L", 9, false);
        ssd1306_display_text(&dev, 2, "NO", 2, false);
        play_pattern(msg);
    }
    else if(strcmp(msg, "SLS") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:SLS", 11, false);
        ssd1306_display_text(&dev, 2, "NEED HELP", 9, false);
        play_pattern(msg);
    }
    else if(strcmp(msg, "LSS") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:LSS", 11, false);
        ssd1306_display_text(&dev, 2, "NEED WATER", 10, false);
        play_pattern(msg);
    }
    else if(strcmp(msg, "SLL") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:SLL", 11, false);
        ssd1306_display_text(&dev, 2, "PAIN", 4, false);
        play_pattern(msg);
    }
    else if(strcmp(msg, "LSL") == 0)
    {
        ssd1306_display_text(&dev, 0, "PATTERN:LSL", 11, false);
        ssd1306_display_text(&dev, 2, "EMERGENCY", 9, false);
        play_pattern(msg);
    }
    else
    {
        ssd1306_display_text(&dev, 0, "INVALID", 7, false);
        ssd1306_display_text(&dev, 2, "PATTERN", 7, false);

        printf("Invalid Pattern\n");

        gpio_set_level(MOTOR, 1);
        vTaskDelay(pdMS_TO_TICKS(300));
        gpio_set_level(MOTOR, 0);
    }
}

void receiver_init(void)
{
    esp_err_t ret = nvs_flash_init();

    if(ret == ESP_ERR_NVS_NO_FREE_PAGES ||
       ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    gpio_reset_pin(MOTOR);
    gpio_set_direction(MOTOR, GPIO_MODE_OUTPUT);
    gpio_set_level(MOTOR, 0);

    esp_netif_init();
    esp_event_loop_create_default();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    esp_wifi_start();

    esp_now_init();

    esp_now_register_recv_cb(recv_cb);

    ssd1306_clear_screen(&dev, false);

    ssd1306_display_text(&dev, 0, "RECEIVER", 8, false);
    ssd1306_display_text(&dev, 2, "WAITING", 7, false);

    printf("Receiver Ready\n");
}

