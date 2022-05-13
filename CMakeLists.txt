cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PEQ_Pico C CXX ASM)

set(CNAKE_C_STANDARD 11)
set(CNAKE_CXX_STANDARD 17)
SET(GCC_COVERAGE_COMPILE_FLAGS "-O0")
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
pico_sdk_init()

add_subdirectory(libs)

add_executable(${PROJECT_NAME}
    main.cpp
    Uart/my_uart.cpp
    GPS/Converter.cpp
    Chrono/PicoChrono.cpp
)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_uart
    hardware_gpio
    pico_unique_id
)

target_include_directories(
     ${PROJECT_NAME} PRIVATE ${SOURCE_DIR}
)

message(${PROJECT_NAME})
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)