#include <zephyr/shell/shell.h>
// For L07 Task 1
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>


// Instance to control LED
/*
 Obtains instance of driver. Static because only this file uses it.
*/
static const struct device *const our_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0)); 

// sensor fetch -> sensor_sample_fetch() [LED ON]

static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv){

    ARG_UNUSED(argc);   // macro to eliminate warning of "parameter not used"
    ARG_UNUSED(argv);

    if (!device_is_ready(our_dev)){ // init driver finished ok

        shell_error(sh, "Device %s not ready", our_dev->name); //shell_error: prints in red
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(our_dev);
    if(ret < 0){
        shell_error(sh, "sensor_sample_fetch failed (%d)", ret);
        return ret;
    }

    shell_print(sh, "Fetch OK (LED ON)");
    return 0;

} // end fetch

// sensor read -> sensor channel_get() (LED OFF) prints value

static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv){

    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    struct sensor_value val;

    if(!device_is_ready(our_dev)){
        shell_error(sh, "Device %s not ready", our_dev->name);
        return -ENODEV;
    }

    int ret = sensor_channel_get(our_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if(ret < 0){
        shell_error(sh, "sensor_channel_get failed (%d)", ret);
        return ret;
    }

    shell_print(sh, "Value: %d.%06d (LED OFF)", val.val1, val.val2);
    return 0;

} // end cmd_sensor_read


// sensor info -> nombre y estado ready

static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Device: %s", our_dev->name);
    shell_print(sh, "Ready:  %s", device_is_ready(our_dev) ? "yes": "no");
    return 0;

} // end cmd_sensor_info

/* Creates table of subcommands SHELL_CMD_ARG(name, subcmds, help, handler, mandatory, optional)
   mandatory = 1, counts own name of subcommand always in argv[0]
   optional = 0, doesn't accept extra arguments
*/
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmds,
    SHELL_CMD_ARG(fetch, NULL, "Fetch sample (turns LED ON)",        cmd_sensor_fetch, 1, 0),
    SHELL_CMD_ARG(read, NULL, "Read channel sample (turns LED OFF)", cmd_sensor_read, 1, 0),
    SHELL_CMD_ARG(info, NULL, "Print device name and ready state",   cmd_sensor_info, 1, 0),
    SHELL_SUBCMD_SET_END // End of subcommand
);

/* Registers root command "sensor", Last NULL = NO additional subcmd*/
SHELL_CMD_REGISTER(sensor, &sensor_subcmds, "LED sensor driver commands", NULL);


// Code from Lecture of Shell Subsystem:
/*

SHELL_CMD_REGISTER(sensor, &sensor_subcmds, "LED sensor driver commands", NULL);


static int cmd_channel_get_handler(const struct shell * sh, int argc, char** argv){
    shell_info(sh, "Hello from channel get");
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    
    [0]=SHELL_CMD_ARG(channel_get, NULL,"Get channel of my driver",cmd_channel_get_handler, 1, 0),
    [1]=SHELL_SUBCMD_SET_END,
    
);

SHELL_CMD_REGISTER(our_driver, &our_driver_subcmd, "our driver set of commands",NULL);

*/

