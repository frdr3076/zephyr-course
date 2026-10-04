if(CONFIG_OUR_DRIVER)
    target_sources(app PRIVATE our_driver.c)
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # Task2: Makes header visible for main, addsi nclude search path.

    if(CONFIG_SHELL) # You can create your own Kconfig.
        target_sources(app PRIVATE our_driver_shell.c)
    endif()


endif()