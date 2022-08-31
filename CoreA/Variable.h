#pragma once

#include <string>
#include "Syntax.h"
#include <iostream>
using namespace std;

class Variable
{
public:
    int valueI;
    string name;
    string type;
    string valueS;
    Variable(string NAME, string TYPE, string VALUE);
    ~Variable();
};