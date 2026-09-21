#include <zephyr/init.h>
#include <zephyr/kernel.h>

// This code executes before main().

static int l5_task2_board_init(void)
{
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(l5_task2_board_init, APPLICATION, 0);