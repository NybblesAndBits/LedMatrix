#ifndef CANVAS_H
#define CANVAS_H

#include "FastLED.h"

class Canvas {
private:
  CRGB *leds;

public:
  CRGB lineColor = CRGB::White;
  CRGB fillColor = CRGB::Black;

  Canvas(CRGB *leds);

  void rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

  void rectFill(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

  void square(uint8_t x, uint8_t y, uint8_t l);

  void squareFill(uint8_t x, uint8_t y, uint8_t l);

};

#endif //CANVAS_H
