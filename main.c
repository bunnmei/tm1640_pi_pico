#include "pico/stdlib.h"
#include <stdio.h>
#include "TM1640.h"

const uint8_t DIN  = 21;
const uint8_t SCL = 20;

int main() {
    stdio_init_all();
    TM1640 tm1640;
    TM1640_init(&tm1640, DIN, SCL);
    sleep_ms(10);

    uint16_t i = 1;
    while (1)
    {
      TM1640_send_auto(&tm1640, i);
      i++;
      sleep_ms(1000);
    }
}