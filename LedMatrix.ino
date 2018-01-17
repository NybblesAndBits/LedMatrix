#include "FastLED.h"
#include "Indexers.h"
#include "Canvas.h"

//============================================================================
// GPIO Constants
const uint8_t DOUT = 10;
const uint8_t LFT_BUT = 5;
const uint8_t MID_BUT = 6;
const uint8_t RGT_BUT = 7;

//============================================================================
// Constants
const uint16_t LED_COUNT = 256;
const uint8_t BRIGHTNESS_MAX = 255;
const uint8_t BRIGHTNESS_MIN = 0;

//============================================================================
// Global Variables
CRGB leds[LED_COUNT];
uint8_t brightness = 15;
Canvas canvas(leds);

//============================================================================
void initGpio() {
  pinMode(DOUT, OUTPUT);
  pinMode(LFT_BUT, INPUT_PULLUP);
  pinMode(MID_BUT, INPUT_PULLUP);
  pinMode(RGT_BUT, INPUT_PULLUP);
}

//============================================================================
void initLeds() {
  FastLED.addLeds<WS2811, DOUT, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(brightness);
  FastLED.setCorrection(TypicalSMD5050);
}

//============================================================================
void setup() {
  initGpio();
  initLeds();

  canvas.lineColor = CRGB::Red;
  canvas.fillColor = CRGB::Blue;
  //canvas.circle(7, 7, 8);
  FastLED.show();
}

uint32_t lastHueTick = 0;
uint8_t hueOffset = 0;

void loop() {

  //uint32_t now = millis();

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

  /*
  if(now - lastHueTick > 10) {
    lastHueTick = now;
    for(int i=0; i<8; i++) {
      setRect(i, i, 16-(i<<1), 16-(i<<1), CHSV((i*3) + hueOffset, 255, 255));
    }
    hueOffset++;
  }
  */



  //FastLED.show();
}

//===============================================================
void setDiag(uint8_t d, const CRGB &color) {
  if (d < 16) {
    uint8_t x = 0;
    uint8_t y = d;
    while (true) {
      leds[xy(x, y)] = color;
      if (x == d) return;
      x++;
      y--;
    }
  } else if (d < 31) {
    uint8_t x = (d&0xF) + 1;
    uint8_t y = 15;
    while (true) {
      leds[xy(x, y)] = color;
      if (x == 15) return;
      x++;
      y--;
    }
  }
}

//===
void setRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const CRGB &color) {
  for (uint8_t i = 0; i < w; i++) {
    leds[xy(x+i, y)] = color;
  }
  for (uint8_t i = 0; i < h; i++) {
    leds[xy(x+w-1, y+i)] = color;
  }
  for (uint8_t i = 0; i < w; i++) {
    leds[xy(x+i, y+h-1)] = color;
  }
  for (uint8_t i = 0; i < h; i++) {
    leds[xy(x, y+i)] = color;
  }
}
