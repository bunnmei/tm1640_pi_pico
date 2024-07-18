#include "TM1640.h"
#include "pico/stdlib.h"
#include <stdio.h>

void TM1640_init(TM1640 *stru, uint8_t din, uint8_t scl) {
  stru->DIN = din;
  stru->SCL = scl;
  gpio_init(stru->SCL);
  gpio_init(stru->DIN);
  gpio_set_dir(stru->SCL, GPIO_OUT);
  gpio_set_dir(stru->DIN, GPIO_OUT);
  gpio_put(stru->SCL, 1);
  gpio_put(stru->DIN, 1);
}

void TM1640_start(TM1640 *stru) {
  gpio_put(stru->DIN, 0);
  sleep_ms(1);
}

void TM1640_end(TM1640 *stru) {
  sleep_ms(1);
  gpio_put(stru->SCL, 0);
  gpio_put(stru->DIN, 0);
  gpio_put(stru->SCL, 1);
  gpio_put(stru->DIN, 1);
}

void send_data(TM1640 *stru, uint8_t data) {
  for (int i = 0; i < 8; i++){
    gpio_put(stru->SCL, 0);
    sleep_ms(1);
    gpio_put(stru->DIN, (data>>i)&0x01);
    gpio_put(stru->SCL, 1);
  }
};

void slice_num(TM1640 *stru, uint16_t num) {

  if(num > 1000) {
    stru->slice_num[0] = 9;
    stru->slice_num[1] = 9;
    stru->slice_num[2] = 9;
    return;
  }
  
  stru->slice_num[0] = (int8_t)(num / 100);
  stru->slice_num[1] = (int8_t)((num % 100) / 10);
  stru->slice_num[2] = (int8_t)(num % 10);

};
void set_num_stru(TM1640 *stru) {
  stru->send_num[0] = font_7seg[stru->slice_num[0]];
  stru->send_num[1] = font_7seg[stru->slice_num[1]];
  stru->send_num[2] = font_7seg[stru->slice_num[2]];
}

void TM1640_send_auto(TM1640 *stru, uint16_t num) {

  slice_num(stru, num);
  set_num_stru(stru);

  printf("ff- %d-%d-%d\n", stru->slice_num[0], stru->slice_num[1], stru->slice_num[2]);
  sleep_ms(1);
  TM1640_start(stru);
  send_data(stru, 0x40); //mode 0x40 or 0x44
  TM1640_end(stru);

  sleep_ms(1);
  TM1640_start(stru);
  send_data(stru, 0b11000000); //addr
  send_data(stru, stru->send_num[0]);
  send_data(stru, stru->send_num[1]);
  send_data(stru, stru->send_num[2]);
  TM1640_end(stru);

  sleep_ms(1);
  TM1640_start(stru);
  send_data(stru, 0b10001100); //brightness
  TM1640_end(stru);
  sleep_ms(1);
};