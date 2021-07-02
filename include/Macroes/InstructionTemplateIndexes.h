//
// Created by plays on 6/18/2021.
//

#ifndef GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H
#define GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H

//The following macros are passed to the instruction templates to determine which register and addressing type are used
#define REGA 0 //A
#define REGB 1 //B
#define REGC 2 //C
#define REGD 3 //D
#define REGE 4 //E
#define REGH 5 //H
#define REGL 6 //L
#define REGF 7 //F
#define REGSP 8 //SP
#define REGPC 9 //PC
#define REGAF 10 //AF
#define REGBC 11 //BC
#define REGDE 12 //DE
#define REGHL 13 //HL
#define REGINDA 14 //(A)
#define REGINDB 15 //(B)
#define REGINDC 16 //(C)
#define REGINDD 17 //(D)
#define REGINDE 18 //(E)
#define REGINDH 19 //(H)
#define REGINDL 20 //(L)
#define REGINDF 21 //(F)
#define REGINDAF 22 //(AF)
#define REGINDBC 23 //(BC)
#define REGINDDE 24 //(DE)
#define REGINDHL 25 //(HL)
#define REGINDHLINC 26 //(HL+)
#define REGINDHLDEC 27 //(HL-)
//Numeric value inputs
#define IMMEDIATE8 28 //d8
#define IMMEDIATE16 29 //d16
#define UNSIGNED8 30 //a8
#define ADDRESS16 31 //a16
#define SIGNED8 32 //r8
#define INDIRECTADDRESS16 33 //(a16)
#define INDIRECTUNSIGNED8 //(a8)
//jump conditions
#define JUMPZRESET 35 //NZ
#define JUMPZSET 36 //Z
#define JUMPCRESET 37 //NC
#define JUMPCSET 38 //C
#define JUMPNOCONDITION 39 //JR with no condition
#endif //GBNEXT_INSTRUCTIONTEMPLATEINDEXES_H

