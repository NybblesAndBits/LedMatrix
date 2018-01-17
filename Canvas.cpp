#include "Canvas.h"
#include "Indexers.h"
#include "FastLED.h"

Canvas::Canvas(CRGB *leds) {
  this->leds = leds;
}

void Canvas::rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  for(int i=0; i<w; i++) leds[xy(x+i, y)] = lineColor;
  for(int i=0; i<w; i++) leds[xy(x+i, y+h-1)] = lineColor;
  for(int i=0; i<h; i++) leds[xy(x, y+i)] = lineColor;
  for(int i=0; i<h; i++) leds[xy(x+w-1, y+i)] = lineColor;
}

void Canvas::rectFill(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  for(int i=0; i<w; i++) {
    for(int j=0; j<h; j++) {
      if(i==0 || j==0 || i==w-1 || j==h-1) leds[xy(x+i, y+j)] = lineColor;
      else leds[xy(x+i, x+j)] = fillColor;
    }
  }
}

void Canvas::square(uint8_t x, uint8_t y, uint8_t l) {
  rect(x, y, l, l);
}

void Canvas::squareFill(uint8_t x, uint8_t y, uint8_t l) {
  rectFill(x, y, l, l);
}

void Canvas::circle(int x0, int y0, int r)
{
    int x = r-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y)
    {
        leds[xy(x0 + x, y0 + y)] = lineColor;
        leds[xy(x0 + y, y0 + x)] = lineColor;
        leds[xy(x0 - y, y0 + x)] = lineColor;
        leds[xy(x0 - x, y0 + y)] = lineColor;
        leds[xy(x0 - x, y0 - y)] = lineColor;
        leds[xy(x0 - y, y0 - x)] = lineColor;
        leds[xy(x0 + y, y0 - x)] = lineColor;
        leds[xy(x0 + x, y0 - y)] = lineColor;

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}
