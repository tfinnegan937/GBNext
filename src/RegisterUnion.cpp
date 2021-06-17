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
    *high = getHighByte(input) >> 8;
    *low = (getLowByte(input));

    return *this;
}

RegisterUnion& RegisterUnion::operator=(const uint8_t &input) {
    *high = 0x00;
    *low = input;
    return *this;
}

RegisterUnion& RegisterUnion::operator=(const RegisterUnion &input) = default;

//AND
uint16_t RegisterUnion::operator&(const uint16_t &input) {

    uint16_t highByte = getHighByte(*this) & getHighByte(input);
    uint16_t lowByte = getLowByte(*this) & getLowByte(input);
    return (highByte | lowByte);
}

uint16_t RegisterUnion::operator&(const RegisterUnion &input) {
    uint16_t highByte = getHighByte(*this) & getHighByte(input);
    uint16_t lowByte = getLowByte(*this) & getLowByte(input);
    return(highByte | lowByte);
}

uint16_t RegisterUnion::operator&(const uint8_t &input) {
    return (uint16_t)(input & *low);
}

//OR
uint16_t RegisterUnion::operator|(const uint16_t &input) {
    uint16_t highByte = getHighByte(*this) | getHighByte(input);
    uint16_t lowByte = getLowByte(*this) | getLowByte(input);
    return (highByte | lowByte);
}

uint16_t RegisterUnion::operator|(const RegisterUnion &input) {
    uint16_t highByte = getHighByte(*this) | getHighByte(input);
    uint16_t lowByte = getLowByte(*this) | getLowByte(*this);
    return(highByte | lowByte);
}

uint16_t RegisterUnion::operator|(const uint8_t &input) {
    return (uint16_t)(input | *low);
}

uint16_t RegisterUnion::operator^(const uint16_t &input) {
    uint16_t highByte = getHighByte(*this) ^ getHighByte(input);
    uint16_t lowByte = getLowByte(*this) ^ getLowByte(input);

    return (highByte | lowByte);
}

uint16_t RegisterUnion::operator^(const RegisterUnion &input) {
    uint16_t highByte = getHighByte(*this) ^ getHighByte(input);
    uint16_t lowByte = getLowByte(*this) ^ getLowByte(input);
    return(highByte | lowByte);
}

uint16_t RegisterUnion::operator^(const uint8_t &input) {
    return(uint16_t)input ^ (uint16_t)*low;
}

uint16_t RegisterUnion::operator+(const uint16_t &input) {
    return get() + input;
}

uint16_t RegisterUnion::operator+(const RegisterUnion &input) {
    return get() + input.get();
}

uint16_t RegisterUnion::operator+(const uint8_t &input) {
    return get() + (uint16_t)input;
}

uint16_t RegisterUnion::operator-(const uint16_t &input) {
    return get() - input;
}

uint16_t RegisterUnion::operator-(const RegisterUnion &input) {
    return get() - input.get();
}

uint16_t RegisterUnion::operator-(const uint8_t &input) {
    return get() - (uint16_t)input;
}

uint16_t RegisterUnion::operator%(const uint16_t &input) {
    return get() % input;
}

uint16_t RegisterUnion::operator%(const RegisterUnion &input) {
    return get() % input.get();
}

uint16_t RegisterUnion::operator%(const uint8_t &input) {
    return get() % (uint16_t)input;
}

uint16_t RegisterUnion::get() const {
    uint16_t highByte = getHighByte(*this);
    uint16_t lowByte = getLowByte(*this);
    return (highByte | lowByte);
}

ostream &RegisterUnion::operator<<(ostream &os) {
    os << get();
    return os;
}

istream &RegisterUnion::operator>>(istream &is) {
    uint16_t i;
    is >> i;
    *this = i;
    return is;
}

uint16_t RegisterUnion::operator++(int j) {
    uint16_t i = get() + 1;
    *this = i;
    return i;
}

uint16_t RegisterUnion::operator--(int j) {
    uint16_t i = get() - 1;
    *this = i;
    return i;
}

uint16_t RegisterUnion::getHighByte(uint16_t input) const{
    return (input & 0xFF00);
}

uint16_t RegisterUnion::getLowByte(uint16_t input) const{
    return (input & 0x00FF);
}

uint16_t RegisterUnion::getHighByte(RegisterUnion input) const{
    return (((uint16_t)(*input.high) << 8));
}

uint16_t RegisterUnion::getLowByte(RegisterUnion input) const{
    return (uint16_t)(*input.low);
}