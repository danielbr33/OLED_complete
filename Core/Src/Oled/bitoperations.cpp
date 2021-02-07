/*
 * bitoperations.cpp
 *
 *  Created on: 03.01.2019
 *      Author: rvbc-
 */

#include "bitoperations.h"

uint8_t reverseBits(uint8_t num)
{
    uint8_t  NO_OF_BITS = sizeof(num) * 8;
    uint8_t reverse_num = 0;
    for (uint8_t i = 0; i < NO_OF_BITS; i++)
    {
        if((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}

uint8_t setBit(uint8_t& byte, uint8_t bit) {
    return byte |= 1UL << bit;
}

uint8_t setBit(uint16_t &byte, uint8_t bit){
	return byte |= 1UL << bit;
}

uint8_t setBit(uint32_t& byte, uint8_t bit) {
    return byte |= 1UL << bit;
}

uint8_t clearBit(uint8_t &byte, uint8_t bit){
	return byte &= ~(1UL << bit);
}

uint8_t toggleBit(uint8_t &byte, uint8_t bit){
	return byte ^= 1UL << bit;
}

uint8_t changeBit(uint8_t &byte, uint8_t bit, uint8_t value){
    return byte ^= (-value ^ byte) & (1UL << bit);
}

uint8_t getBit(uint64_t byte, uint8_t bit){
    return (byte >> bit) & 1U;
}

uint8_t getBit(uint32_t byte, uint8_t bit){
    return (byte >> bit) & 1U;
}

uint8_t getBit(uint16_t byte, uint8_t bit){
    return (byte >> bit) & 1U;
}

uint8_t getBit(uint8_t byte, uint8_t bit){
    return (byte >> bit) & 1U;
}
