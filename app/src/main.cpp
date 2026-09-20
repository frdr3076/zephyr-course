#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/*Commands:
    Build: west build -b frdm_mcxa156 app -p
    Flash: west flash
    menuconfig: west build -t menuconfig
    zephyr.dts is found here: .\zephyr-course\build\zephyr\zephyr.dts
*/

/* The devicetree node identifier for the "led0" alias. */

//#define LED_NODE DT_ALIAS(warning_led)
#define LED_NODE DT_ALIAS(led2)

//#define LED_NODE DT_ALIAS(app_led)
    /* Method 1: using nodelabel
    //#define LED_NODE DT_NODELABEL(red_led)
    */

    /* Method 2: ussing path
    //#define LED_NODE DT_PATH(leds,led_1)
    */

    /* Method 3: using other overlays
    //west build -- -DEXTRA_DTC_OVERLAY_FILE="boards/green.overlay"
    */

//Not used: //#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");


        //k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);    // Use for Module 01 to 03
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS); // Use for Module 04

    }
    return 0;
}
