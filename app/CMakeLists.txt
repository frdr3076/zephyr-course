cmake_minimum_required(VERSION 3.20.0)


list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# set(DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/boards/app.overlay")

# IMPORTANT: Use this line if you have many .overlay files.
# If not only your board overlay will be build.
list(APPEND EXTRA_DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/boards/app.overlay")


find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)


# Added by Franco: If option"Enable LED debugging" is active in Kconfig:
if(CONFIG_LED_DEBUG)
    message(STATUS "Option LED_DEBUG active: Adding target for automatic debug")
    
    add_custom_target(run_debug ALL
        COMMAND west debug
        COMMENT "Executing automatic west debug by CONFIG_LED_DEBUG=y"
        USES_TERMINAL
    )
    
    # Forces debug sesion after compilation
    add_dependencies(run_debug zephyr_final)
endif()