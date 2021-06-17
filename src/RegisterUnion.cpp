//
// Created by plays on 6/16/2021.
//

#include "CPU/RegisterUnion.h"

RegisterUnion::RegisterUnion(uint8_t *high_in, uint8_t *low_in) {
    high = high_in;
    low = low_in;
}

//Equals
RegisterUnion& RegisterUnion::operator=(const uint16_t &input) {
    *high = (uint8_t)((input & 0xF0) >> 8);
    *low = (uint8_t)(input & 0x0F);

    return *this;
}

RegisterUnion& RegisterUnion::operator=(const uint8_t &input) {
    *high = 0x00;
    *low = input;
    return *this;
}

RegisterUnion& RegisterUnion::operator=(const RegisterUnion &input) {
    *high = *(input.high);
    *low = *(input.low);
    return *this;
}

//AND
uint16_t RegisterUnion::operator&(const uint16_t &input) {

    uint16_t highByte = ((uint16_t)(*high) << 8) & ((input & 0xF0));
    uint16_t lowByte = (uint16_t(*low)) & (input & 0x0F);
    return (highByte | lowByte);
}

uint16_t RegisterUnion::operator&(const RegisterUnion &input) {
    uint16_t highByte = ((uint16_t)(*high) & (uint16_t)(*(input.high))) << 8;
    uint16_t lowByte = (uint16_t)(*low) & (uint16_t)(*(input.low));
    return(highByte | lowByte);
}

uint16_t RegisterUnion::operator&(const uint8_t &input) {
    return (uint16_t)input & *low;
}

//OR
uint16_t RegisterUnion::operator|(const uint16_t &input) {
    uint16_t highByte = ((uint16_t)(*high) << 8) | ((input & 0xF0));
    uint16_t lowByte = (uint16_t(*low)) | (input & 0x0F);
    return (highByte | lowByte);
}

uint16_t RegisterUnion::operator|(const RegisterUnion &input) {
    uint16_t highByte = ((uint16_t)(*high) | (uint16_t)(*(input.high))) << 8;
    uint16_t lowByte = (uint16_t)(*low) | (uint16_t)(*(input.low));
    return(highByte | lowByte);
}

uint16_t RegisterUnion::operator|(const uint8_t &input) {
    return (uint16_t)input & *low;
}

