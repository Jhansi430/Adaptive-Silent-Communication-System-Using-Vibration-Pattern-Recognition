#include "ssd1306.h"
#include "receiver.h"

SSD1306_t dev;

void app_main(void)
{
    i2c_master_init(
        &dev,
        CONFIG_SDA_GPIO,
        CONFIG_SCL_GPIO,
        CONFIG_RESET_GPIO);

    ssd1306_init(&dev, 128, 64);

    ssd1306_clear_screen(&dev, false);

    receiver_init();
}