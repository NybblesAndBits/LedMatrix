#ifndef INDEXERS_H
#define INDEXERS_H

//############################################################################
// All functions in this file assume a serpintine LED matrix. See the diagram
// below for a visual representation of the LED layout.
//############################################################################
//  0   31---32   63---64             255
//  1   30   33   62   65             254
//  |   |    |    |    |   ...   |     |
//  |   |    |    |    |   ...   |     |
// 14   17   46   49            238   241
// 15---16   47---48            239---240
//############################################################################

//=============================================================================
// This function converts cartesian (x,y) coordinates to an index value. The
// origin point (0, 0) is the top left. The bottom right corner is (15, 15).
uint8_t xy(uint8_t x, uint8_t y);

//=============================================================================
// This function converts an index value to a left to right wrapping index
// value. Indexes 0-15 make up the first horizontal row (left to right).
// Indexes 16-31 make up the second horizontal row (left to right).
uint8_t wrap(uint8_t index);

#endif // INDEXERS_H
