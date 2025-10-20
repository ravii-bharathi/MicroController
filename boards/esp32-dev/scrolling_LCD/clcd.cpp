#include "clcd.h"
#include "Arduino.h"

CLCD::CLCD(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t rs, uint8_t en) {
  clcd_rs_pin = rs;
  clcd_en_pin = en;

  clcd_data_pin[0] = d4;
  clcd_data_pin[1] = d5;
  clcd_data_pin[2] = d6;
  clcd_data_pin[3] = d7;
}

void CLCD::write(uint8_t data, bool rs_bit_val, uint16_t exec_time_us) {
  digitalWrite(clcd_rs_pin, rs_bit_val);

  // --- Send high nibble ---
  digitalWrite(clcd_data_pin[0], (data >> 4) & 0x01);
  digitalWrite(clcd_data_pin[1], (data >> 5) & 0x01);
  digitalWrite(clcd_data_pin[2], (data >> 6) & 0x01);
  digitalWrite(clcd_data_pin[3], (data >> 7) & 0x01);

  digitalWrite(clcd_en_pin, HI);
  delayMicroseconds(5); // was 1, too short
  digitalWrite(clcd_en_pin, LO);
  delayMicroseconds(100); // give LCD time

  // --- Send low nibble ---
  digitalWrite(clcd_data_pin[0], (data >> 0) & 0x01);
  digitalWrite(clcd_data_pin[1], (data >> 1) & 0x01);
  digitalWrite(clcd_data_pin[2], (data >> 2) & 0x01);
  digitalWrite(clcd_data_pin[3], (data >> 3) & 0x01);

  digitalWrite(clcd_en_pin, HI);
  delayMicroseconds(5); // was 1, too short
  digitalWrite(clcd_en_pin, LO);
  delayMicroseconds(exec_time_us);
}

void CLCD::command(uint8_t data, uint16_t exec_time_us) {
  write(data, 0, exec_time_us);
}

void CLCD::begin(void) {
  // --- FIX 1: set pin modes BEFORE using them ---
  pinMode(clcd_rs_pin, OUTPUT);
  pinMode(clcd_en_pin, OUTPUT);
  pinMode(clcd_data_pin[0], OUTPUT);
  pinMode(clcd_data_pin[1], OUTPUT);
  pinMode(clcd_data_pin[2], OUTPUT);
  pinMode(clcd_data_pin[3], OUTPUT);

  digitalWrite(clcd_en_pin, LO);

  delayMicroseconds(50000); // >40ms after Vcc rises

  // --- FIX 2: proper init sequence (only high nibbles first) ---
  // Send 0x3 nibble three times
  for (int i = 0; i < 3; i++) {
    digitalWrite(clcd_rs_pin, LO);
    digitalWrite(clcd_data_pin[0], 1);
    digitalWrite(clcd_data_pin[1], 1);
    digitalWrite(clcd_data_pin[2], 0);
    digitalWrite(clcd_data_pin[3], 0);

    digitalWrite(clcd_en_pin, HI);
    delayMicroseconds(5);
    digitalWrite(clcd_en_pin, LO);
    delayMicroseconds((i == 2) ? 150 : 4500);
  }

  // Switch to 4-bit mode (send 0x2 nibble)
  digitalWrite(clcd_rs_pin, LO);
  digitalWrite(clcd_data_pin[0], 0);
  digitalWrite(clcd_data_pin[1], 1);
  digitalWrite(clcd_data_pin[2], 0);
  digitalWrite(clcd_data_pin[3], 0);

  digitalWrite(clcd_en_pin, HI);
  delayMicroseconds(5);
  digitalWrite(clcd_en_pin, LO);
  delayMicroseconds(150);

  // --- Now safe to use full 8-bit commands via write() ---
  write(TWO_LINE_5x7_MATRIX_4_BIT, 0, 37);
  write(CURSOR_HOME, 0, 1640);
  write(DISP_ON_AND_CURSOR_OFF, 0, 37);
  write(CLEAR_DISP_SCREEN, 0, 1640);
}

void CLCD::print(const char *s, uint8_t addr) {
  write(addr, 0, 37);
  while (*s != '\0') {
    write(*s++, 1, 37);
  }
}

void CLCD::putch(int8_t data, uint8_t addr) {
  write(addr, 0, 37);
  write(data, 1, 37);
}


/*
#include "clcd.h"
#include "Arduino.h"

CLCD::CLCD(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t rs, uint8_t en) {

  clcd_rs_pin = rs;
  clcd_en_pin = en;

  clcd_data_pin[0] = d4;
  clcd_data_pin[1] = d5;
  clcd_data_pin[2] = d6;
  clcd_data_pin[3] = d7;
}


void CLCD::write(uint8_t data, bool rs_bit_val, uint16_t exec_time_us) {

  digitalWrite(clcd_rs_pin, rs_bit_val);


  digitalWrite(clcd_data_pin[0], (data >> 4) & 0x01);
  digitalWrite(clcd_data_pin[1], (data >> 5) & 0x01);
  digitalWrite(clcd_data_pin[2], (data >> 6) & 0x01);
  digitalWrite(clcd_data_pin[3], (data >> 7) & 0x01);


  digitalWrite(clcd_en_pin, HI);

  delayMicroseconds(1);

  digitalWrite(clcd_en_pin, LO);



  digitalWrite(clcd_data_pin[0], (data >> 0) & 0x01);
  digitalWrite(clcd_data_pin[1], (data >> 1) & 0x01);
  digitalWrite(clcd_data_pin[2], (data >> 2) & 0x01);
  digitalWrite(clcd_data_pin[3], (data >> 3) & 0x01);

  digitalWrite(clcd_en_pin, HI);

  delayMicroseconds(1);

  digitalWrite(clcd_en_pin, LO);

  delayMicroseconds(exec_time_us);
  
}



void CLCD::command(uint8_t data, uint16_t exec_time_us) {

    write( data , 0, exec_time_us );

}

void CLCD::begin(void) {

  digitalWrite(clcd_en_pin, LO);

  pinMode(clcd_rs_pin, OUTPUT);
  pinMode(clcd_en_pin, OUTPUT);
  pinMode(clcd_data_pin[0], OUTPUT);
  pinMode(clcd_data_pin[1], OUTPUT);
  pinMode(clcd_data_pin[2], OUTPUT);
  pinMode(clcd_data_pin[3], OUTPUT);

  delayMicroseconds(50000);

  write(0x03, 0, 4500);  // we start in 8 bit mode , try to set 4 bit mode
  write(0x03, 0, 4500);  // second try
  write(0x03, 0, 150);   // third go!

  write(TWO_LINE_5x7_MATRIX_4_BIT, 0, 37);
  write(CURSOR_HOME, 0, 1640);
  write(DISP_ON_AND_CURSOR_OFF, 0, 37);
  write(CLEAR_DISP_SCREEN, 0, 1640);
}

void CLCD::print(const char *s, uint8_t addr) {

  write(addr, 0, 37);
  while (*s != '\0') {
    write(*s++, 1, 37);
  }
}

void CLCD::putch(int8_t data, uint8_t addr) {

  write(addr, 0, 37);

  write(data, 1, 37);
}
*/