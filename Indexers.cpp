#include "Indexers.h"
#include <stdint.h>

//=============================================================================
uint8_t xy(uint8_t x, uint8_t y) {
  if(x&1) return (x<<4) + 15 - y;
  else return (x<<4) + y;
}

//=============================================================================
uint8_t wrap(uint8_t index) {
  return xy(index & 0b1111, index >> 4);
}
