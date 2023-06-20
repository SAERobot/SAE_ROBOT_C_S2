#include <mbed.h>
#include <robot.hpp>

void play(Robot& goofyBot) {
  int play[5] = {0x7E, 0x03, 0xAA, 0xAD, 0xEF};
  for (int i = 0; i < 5; i++) {
    goofyBot.com.putc(play[i]);
  }
}

void volume(Robot& goofyBot, int vol) {
  if (vol < 0 || vol > 31) {
    vol = 15;
  }
  char volume[6] = {0x7E, 0x04, 0xAE, 0x08, 0xBA, 0xEF};
  volume[3] = (char)vol;
  volume[4] = (volume[1] + volume[2] + volume[3]) & 0xFF;
  for (int i = 0; i < 6; i++) {
    goofyBot.com.putc(volume[i]);
  }
}

void change(Robot& goofyBot, int tit) {
  if (tit < 0 || tit > 65535) {
    tit = 0;
  }
  uint8_t hbyte = tit >> 8;
  uint8_t lbyte = tit & 0xFF;
  char buss[7] = {0x7E, 0x05, 0xA2, 0x00, 0x00, 0x00, 0xEF};
  buss[3] = hbyte;
  buss[4] = lbyte;
  buss[5] = (buss[1] + buss[2] + buss[3] + buss[4]) & 0xFF;
  for (int i = 0; i < 7; i++) {
    goofyBot.com.putc(buss[i]);
  }
}