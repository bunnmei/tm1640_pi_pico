#ifndef _TM1640_H
#define _TM1640_H
// #include "common.h"
#include <stdint.h>
#include <string.h>


typedef struct
{
  uint8_t DIN;
  uint8_t SCL;
  uint8_t slice_num[3];
  uint8_t send_num[3];
  uint8_t font_7seg[16];
} TM1640;

static const int font_7seg[10] = {
      0b00111111, // 0
      0b00000110, // 1
      0b01011011, // 2
      0b01001111, // 3
      0b01100110, // 4
      0b01101101, // 5
      0b01111101, // 6
      0b00100111, // 7
      0b01111111, // 8
      0b01101111, // 9
  };

void TM1640_init(TM1640 *stru, uint8_t din, uint8_t scl);
void TM1640_start(TM1640 *stru);
void TM1640_end(TM1640 *stru);
void send_data(TM1640 *stru, uint8_t data);
void TM1640_send_auto(TM1640 *stru, uint16_t num);
void slice_num(TM1640 *stru, uint16_t num);
void set_num_stru(TM1640 *stru);

#endif
