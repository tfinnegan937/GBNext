//
// Created by plays on 6/14/2021.
//

#ifndef GBNEXT_MBC3_H
#define GBNEXT_MBC3_H
#include <memory>
using namespace std;
class MBC3 {
private:
    int myVar;
    shared_ptr<int> ptr;
public:
    int getMyVar() const;
    void DoSomething();

public:
};


#endif //GBNEXT_MBC3_H
