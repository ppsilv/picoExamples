
#include "pico/stdlib.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

#define LED01   0
#define LED02   LED01 + 1
#define LED03   LED01 + 2

int gpio_led_init(void) {
    gpio_init(LED01);
    gpio_init(LED02);
    gpio_init(LED03);
    gpio_set_dir(LED01, GPIO_OUT);
    gpio_set_dir(LED02, GPIO_OUT);
    gpio_set_dir(LED03, GPIO_OUT);

    return 0;
}


int main() {
    int rc = gpio_led_init();
    hard_assert(rc == PICO_OK);
    while (true) {
        gpio_put(LED01, true);
        gpio_put(LED02, false);
        gpio_put(LED03, true);
        sleep_ms(LED_DELAY_MS);
        gpio_put(LED01, false);
        gpio_put(LED02, true);
        gpio_put(LED03, false);
        sleep_ms(LED_DELAY_MS);
    }
}
