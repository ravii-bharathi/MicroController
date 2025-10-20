#ifndef CLCD_H
#define CLCD_H

#include <inttypes.h>

#define DISP_ON_AND_CURSOR_OFF 0x0C
#define TWO_LINE_5x7_MATRIX_4_BIT 0x28
#define CLEAR_DISP_SCREEN 0x01
#define CURSOR_HOME 0x02

#define LINE1(x) ((0x80) + (x))
#define LINE2(x) ((0xc0) + (x))

#define HI 1
#define LO 0

class CLCD {
public:
  /* Default constructor */
  CLCD(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t rs, uint8_t en);

  /* Methods */
  void begin(void);  // configure the clcd
  void print(const char *s, uint8_t addr); // print a string on clcd
  void putch(int8_t data, uint8_t addr); // print a char on clcd

  void command(uint8_t addr, uint16_t exec_time_us); // write instruction on clcd

private:
  /* Datatypes */
  uint8_t clcd_rs_pin;
  uint8_t clcd_en_pin;
  uint8_t clcd_data_pin[4];


  /* Methods */
  void write(uint8_t data, bool rs_bit_val, uint16_t exec_time_us); // write data on the clcd
};

#endif
