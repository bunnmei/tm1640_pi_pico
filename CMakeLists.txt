cmake_minimum_required(VERSION 3.19.8)
# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(movad  C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
	main.c
        TM1640.c
)

#target_sources(AWG_1.pio PRIVATE AWG_1.c)
# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

