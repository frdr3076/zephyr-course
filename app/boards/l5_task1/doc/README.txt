
For this task:

1- I made a Copy of all the contents of this folder:
    "C:\Users\User\zephyr-demo\deps\zephyr\boards\nxp\frdm_mcxa156"

2- Renamed every board name "frdm_mcxa156" with "board_l5_task1"
    a - board.yml
    b - Kconfig & Kconfig.l5_task1
    c - l5_task1.dts model & compatible

Commands used in Powershell:

--> BUILD: (execute from zephyr-demo)
    west build -b l5_task1 deps/zephyr/samples/hello_world -d build_l5_task1 -p always -- "-DBOARD_ROOT=C:/Users/User/zephyr-demo/zephyr-course/app"

--> FLASH:
    west flash -d build_l5_task1

--> SERIAL PORT MESSAGE VERIFICATION: (check port number with Manage Devices in Windows...)
    python -m serial.tools.miniterm COM<N> 115200


----------------- Star topology ----------------------------
zephyr-demo/              ← topdir (here is .west)
├── deps/
│   └── zephyr/            ← Zephyr
└── zephyr-course/         ← My repo (.git)
-------------------------------------------------------------

