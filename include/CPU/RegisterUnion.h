//
// Created by plays on 6/16/2021.
//

#ifndef GBNEXT_REGISTERUNION_H
#define GBNEXT_REGISTERUNION_H


#include <cstdint>
#include <iostream>
using namespace std;
class RegisterUnion {
private:
    uint16_t getHighByte(uint16_t input) const;
    uint16_t getLowByte(uint16_t input) const;
    uint16_t getHighByte(RegisterUnion input) const;
    uint16_t getLowByte(RegisterUnion input) const;
public:
    uint8_t * high;
    uint8_t * low;
    RegisterUnion(uint8_t * high_in, uint8_t * low_in);

    //equals Overloads
    RegisterUnion& operator=(const uint16_t& input);
    RegisterUnion& operator=(const RegisterUnion & input);
    RegisterUnion& operator=(const uint8_t & input);


    uint16_t operator&(const uint16_t& input);
    uint16_t operator&(const RegisterUnion & input);
    uint16_t operator&(const uint8_t& input);

    uint16_t operator|(const uint16_t& input);
    uint16_t operator|(const RegisterUnion & input);
    uint16_t operator|(const uint8_t& input);

    uint16_t operator^(const uint16_t& input);
    uint16_t operator^(const RegisterUnion & input);
    uint16_t operator^(const uint8_t& input);

    ostream& operator<<(ostream& os);


    istream& operator>>(istream& is);


    uint16_t operator+(const uint16_t& input);
    uint16_t operator+(const RegisterUnion & input);
    uint16_t operator+(const uint8_t& input);

    uint16_t operator-(const uint16_t& input);
    uint16_t operator-(const RegisterUnion & input);
    uint16_t operator-(const uint8_t& input);

    uint16_t operator%(const uint16_t& input);
    uint16_t operator%(const RegisterUnion & input);
    uint16_t operator%(const uint8_t& input);

    uint16_t operator++(int);
    uint16_t operator--(int);

    uint16_t get() const;

};


#endif //GBNEXT_REGISTERUNION_H
