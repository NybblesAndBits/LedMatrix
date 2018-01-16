#include "FastLED.h"

const uint8_t DOUT = 10;
const uint8_t LFT_BUT = 5;
const uint8_t MID_BUT = 6;
const uint8_t RGT_BUT = 7;

/*
  const CRGB PALETTE[] = {
  CRGB::Black,
  CRGB(255, 204, 103),
  CRGB(35, 250, 35),
  CRGB(96, 66, 26)
  };

  const uint8_t MARIO[16][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
  {0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 3, 1, 0, 3, 3, 3},
  {0, 0, 0, 0, 3, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 3},
  {0, 0, 0, 0, 3, 1, 3, 3, 1, 1, 1, 3, 1, 1, 1, 3},
  {0, 0, 0, 0, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0},
  {0, 0, 3, 3, 3, 3, 3, 2, 3, 3, 3, 2, 3, 0, 0, 0},
  {0, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3, 2, 0, 0, 3},
  {1, 1, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 0, 0, 3},
  {1, 1, 1, 0, 0, 2, 3, 2, 2, 2, 1, 2, 1, 2, 3, 3},
  {0, 1, 0, 3, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3},
  {0, 0, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3},
  {0, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0},
  {0, 3, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}
  };
*/

//CRGB frame[16][16];

uint8_t x = 0;
uint8_t y = 0;
uint8_t dx = 3;
uint8_t dy = 7;

const int LED_COUNT = 256;
CRGB leds[LED_COUNT];

void setup() {
  pinMode(DOUT, OUTPUT);
  pinMode(LFT_BUT, INPUT_PULLUP);
  pinMode(MID_BUT, INPUT_PULLUP);
  pinMode(RGT_BUT, INPUT_PULLUP);

  Serial.begin(9600);

  FastLED.addLeds<WS2811, DOUT, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(15);
  FastLED.setCorrection(TypicalSMD5050);
  //FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);

}

uint32_t lastHueTick = 0;
uint8_t hueOffset = 0;

void loop() {

  uint32_t now = millis();

  /*
  if (now - lastHueTick > 10) {
    lastHueTick = now;
    for (int d = 0; d < 31; d++) {
      setDiag(d, CHSV((d << 1) + hueOffset, 255, 255));
    }
    hueOffset--;
  }
  */

  /*
  if(now - lastHueTick > 10) {
    lastHueTick = now;
    for(int d=0; d<16; d++) {
      setDiag(d, CHSV((d<<3) + hueOffset, 255, 255));
      setDiag(30-d, CHSV((d<<3) + hueOffset, 255, 255));
    }
    hueOffset++;
  }
  */

  ///*
  if(now - lastHueTick > 10) {
    lastHueTick = now;
    for(int i=0; i<8; i++) {
      setRect(i, i, 16-(i<<1), 16-(i<<1), CHSV((i*3) + hueOffset, 255, 255));
    }
    hueOffset++;
  }
  //*/

  FastLED.show();
}

//===============================================================
uint8_t xy(uint8_t x, uint8_t y) {
  return (x << 4) + ((x & 1) ? (15 - y) : (y));
}

//===============================================================
void set(uint8_t x, uint8_t y, const CRGB &color) {
  uint8_t index = (x << 4) + ((x & 1) ? (15 - y) : (y));
  leds[index] = color;
}

//===============================================================
void invert(uint8_t x, uint8_t y) {
  uint8_t index = (x << 4) + ((x & 1) ? (15 - y) : (y));
  leds[index] = -leds[index];
}

//===============================================================
void safeSet(uint8_t x, uint8_t y, const CRGB &color) {
  if (x > 15 || y > 15) return;
  set(x, y, color);
}

//===============================================================
void set(uint8_t index, const CRGB &color) {
  set(index & 0b1111, index >> 4, color);
}

//===============================================================
void set16(uint8_t x, uint8_t y, uint16_t color) {
  set(x, y, CRGB((color >> 11) & 0x1F, (color >> 5) & 0x2F, color & 0x1F));
}

//===============================================================
void safeSet16(uint8_t x, uint8_t y, uint16_t color) {
  if (x > 15 || y > 15) return;
  set(x, y, color);
}

//===============================================================
void setDiag(uint8_t d, const CRGB &color) {
  if (d < 16) {
    uint8_t x = 0;
    uint8_t y = d;
    while (true) {
      set(x, y, color);
      if (x == d) return;
      x++;
      y--;
    }
  } else if (d < 31) {
    uint8_t x = (d & 0b1111) + 1;
    uint8_t y = 15;
    while (true) {
      set(x, y, color);
      if (x == 15) return;
      x++;
      y--;
    }
  }
}

//===
void setRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const CRGB &color) {
  for (uint8_t i = 0; i < w; i++) {
    set(x + i, y, color);
  }
  for (uint8_t i = 0; i < h; i++) {
    set(x + w - 1, y + i, color);
  }
  for (uint8_t i = 0; i < w; i++) {
    set(x + i, y + h - 1, color);
  }
  for (uint8_t i = 0; i < h; i++) {
    set(x, y + i, color);
  }
}

//===
void invertRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  for (uint8_t i = 0; i < w; i++) {
    invert(x + i, y);
  }
  for (uint8_t i = 0; i < h; i++) {
    invert(x + w - 1, y + i);
  }
  for (uint8_t i = 0; i < w; i++) {
    invert(x + i, y + h - 1);
  }
  for (uint8_t i = 0; i < h; i++) {
    invert(x, y + i);
  }
}

