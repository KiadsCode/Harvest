#pragma once
#include <vector>
#include <iostream>
#include "Variable.h"
using namespace std;

class Function
{
public:
	vector<Variable> vars;
	string name;
	int onLine, endLine;
	Function(string NAME, int ONLINE, int ENDLINE, vector<Variable> VARIABLES);
};

