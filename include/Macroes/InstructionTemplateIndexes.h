//
// Created by plays on 6/18/2021.
//

#ifndef GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H
#define GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H

//The following macros are passed to the instruction templates to determine which register and addressing type are used
#define REGA 0
#define REGB 1
#define REGC 2
#define REGD 3
#define REGE 4
#define REGH 5
#define REGL 6
#define REGF 7
#define REGSP 8
#define REGPC 9
#define REGAF 10
#define REGBC 11
#define REGDE 12
#define REGHL 13
//These are referring to (A), (B), (AF), (BC), etc
#define REGINDA 14
#define REGINDB 15
#define REGINDC 16
#define REGINDD 17
#define REGINDE 18
#define REGINDH 19
#define REGINDL 20
#define REGINDF 21
#define REGINDAF 22
#define REGINDBC 23
#define REGINDDE 24
#define REGINDHL 25
#define REGINDHLINC 26
#define REGINDHLDEC 27
//Numeric value inputs
#define IMMEDIATE8 28
#define IMMEDIATE16 29
#define UNSIGNED8 30
#define ADDRESS16 31
#define SIGNED8 32
#define INDIRECTADDRESS16 33
#define INDIRECTUNSIGNED8
//jump conditions
#define JUMPZRESET 35
#define JUMPZSET 36
#define JUMPCRESET 37
#define JUMPCSET 38
#endif //GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H

