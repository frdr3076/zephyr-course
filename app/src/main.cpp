
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "our_driver.h" // Task 2
/*Commands:
    Build: west build -b frdm_mcxa156 app -p
    Flash: west flash
    menuconfig: west build -t menuconfig
    zephyr.dts is found here: .\zephyr-course\build\zephyr\zephyr.dts
*/

/* The devicetree node identifier for the "led0" alias. */

//#define LED_NODE DT_ALIAS(warning_led)
//#define LED_NODE DT_ALIAS(led2)

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


static const struct device *const our_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));


LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

// Added for driver lecture:
/*
namespace {
    void test(){
        const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        int ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP,&val);
        LOG_INF("Channel ret %d",ret);
    }
}
*/

int main(void)
{
    if(!device_is_ready(our_dev)){

        LOG_ERR("our_driver0 is not ready");
        return 0;

    }

    struct sensor_value val;
    uint32_t count;

    while(1){
        sensor_sample_fetch(our_dev);                               // LED ON
        k_msleep(500);                                           
        sensor_channel_get(our_dev, SENSOR_CHAN_AMBIENT_TEMP, &val); // LED OFF
        our_driver_increment_counter(our_dev, &count);
        LOG_INF("main: blink #%u", count);
        k_msleep(500);
    
    } //end while



    /* // Previous exercises of Device Drivers
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
    */
} //end main
