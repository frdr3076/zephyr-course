#define DT_DRV_COMPAT our_driver    // Links C to every DT. Enables instance macros like DT_INST_FOREACH_STATUS_OKAY(...)
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>          // DEVICE_DT_INST_DEFINE
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>    // gpio_dt_spec, gpio_pin_set_dt


// ----------------------- Task 2 ------------------------------------------------------------------
#include "our_driver.h"

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF); // necesary to use LOG.


struct our_driver_config {
    struct gpio_dt_spec led;    // from devicetree hardware [inmutable]
};

struct our_driver_data{
    int32_t led_state;          // modified at runtime [mutable]
    uint32_t counter;           // For Task2: Parameter that modifies function
};

// Private Helpers
/* sensor_sample_fetch() --> Turns ON LED */
static int our_sample_fetch(const struct device *dev, enum sensor_channel chan) // dev instance 0 or 1
{
    const struct our_driver_config *cfg = dev->config; // instance of config
    struct our_driver_data *data = dev->data;          // instance of data

    int ret = gpio_pin_set_dt(&cfg->led,1);
    if(ret == 0){ // ok
        data->led_state = 1;
        LOG_INF("%s: fetch -> LED ON", dev->name); // instance name
    }
    return ret;

};

/* sensor_channel_get() -> Turns OFF LED*/
static int our_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    const struct our_driver_config *cfg = dev->config;
    struct our_driver_data *data = dev->data;

    int ret = gpio_pin_set_dt(&cfg->led, 0);
    if(ret == 0){
        data->led_state = 0;
        val->val1 = data->led_state;  // int
        val->val2 = 0;                // fracc
        LOG_INF("%s: channel_get -> LED OFF",dev->name);
    }
    return ret;
};

// Implement Extended Function Driver

int our_driver_increment_counter(const struct device *dev, uint32_t *count)
{   /*
       Not static because main wouldn't find it
       main calls this function directly
    */
    struct our_driver_data *data = dev->data;
    data->counter++;
    if( count != NULL ){
        *count = data->counter;
    }
    LOG_INF("%s: counter = %u",dev->name, data->counter);
    return 0;
}



// Register Sensor API
// Connects functions get & fetch with code 
static DEVICE_API(sensor, our_driver_api) = { 
    .sample_fetch = our_sample_fetch,
    .channel_get = our_channel_get,
};


// Init Flow
static int our_driver_init(const struct device *dev)
{
    const struct our_driver_config *cfg = dev->config;

    if(!gpio_is_ready_dt(&cfg->led)){ //gpio3 is ready
        LOG_ERR("GPIO not ready");
        return -ENODEV;
    }
    return gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE); //gpio as output and off

}

// Instantiation Macro
#define OUR_DRIVER_DEFINE(inst)  \
    static struct our_driver_data data_##inst; \
    static const struct our_driver_config cfg_##inst ={ .led = GPIO_DT_SPEC_INST_GET(inst, led_gpios),}; \
    DEVICE_DT_INST_DEFINE(inst, our_driver_init, NULL, &data_##inst, &cfg_##inst, POST_KERNEL, \
         CONFIG_SENSOR_INIT_PRIORITY,&our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)



// static struct our_driver_data data_##inst; = Creates data_0, data_1
// static const struct our_driver_config cfg_##inst = Creates cfg_0, cfg_1
//GPIO_DT_SPEC_INST_GET(inst, led_gpios) = Devicetree, led-gpios and build gpio_dt_spec.
// DEVICE_DT_INST_DEFINE uses instances of data and cfg.
// CONFIG_SENSOR_INIT_PRIORITY = Sets priority.





/* ----------------------------- From Device Drivers Lecture ------------------------------------------------------*/

/*

static int channel_get_my_impl(const struct device *dev,
				               enum sensor_channel chan,
				               struct sensor_value *val){

    LOG_INF("Hello from channel get, channel %d",chan);                        
    return 0;
                               }


static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_impl,
};


// Init fn
static int init(const struct device* dev){
    LOG_INF("Device initialized!");
    return 0;
}

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST)

*/


/*
static const __attribute__((__aligned__(__alignof(
    struct sensor_driver_api)))) struct sensor_driver_api api_iomico_lecture
     __attribute__((section("."
                            "_sensor_driver_api"
                            "." "static"
                            "."
                            "api_iomico_lecture_")))
     __attribute__((__used__))  = {};
*/