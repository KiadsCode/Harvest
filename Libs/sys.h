#pragma once
#include <Lib.h>

class sys :
    public Lib
{
public:
    sys() :Lib("sys") {}
    void executeFunction(string com, string args[]) {
        Syntax syntaxEx = Syntax();
        if (com == syntaxEx.printf) {
            cout << args[0] << endl;
        }
        if (com == syntaxEx.inpuGetF) {
            getinf();
            return;
        }
    }
    void getinf() {
        cin.get();
    }
};

