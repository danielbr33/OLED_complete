/* Created on: 22.02.2021
   Author: daniel   */

#ifndef BITOPERATIONS_H
#define BITOPERATIONS_H

#include <stdint.h>

uint8_t reverseBits(uint8_t num);

uint8_t setBit(uint8_t &byte, uint8_t bit);
uint8_t setBit(uint16_t &byte, uint8_t bit);
uint8_t setBit(uint32_t &byte, uint8_t bit);

uint8_t clearBit(uint8_t &byte, uint8_t bit);

uint8_t toggleBit(uint8_t &byte, uint8_t bit);

uint8_t changeBit(uint8_t &byte, uint8_t bit, uint8_t value);

uint8_t getBit(uint64_t byte, uint8_t bit);
uint8_t getBit(uint32_t byte, uint8_t bit);
uint8_t getBit(uint16_t byte, uint8_t bit);
uint8_t getBit(uint8_t byte, uint8_t bit);

#endif // BITOPERATIONS_H
