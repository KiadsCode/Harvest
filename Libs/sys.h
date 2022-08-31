#pragma once
#include <Lib.h>

class sys :
    public Lib
{
public:
    sys() :Lib("sys") {}
    void getinf() {
        cin.get();
    }
};

