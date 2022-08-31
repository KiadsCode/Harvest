#pragma once
#include <vector>
#include "Variable.h"
using namespace std;

class FindUtil
{
public:
	vector<Variable> VARIABLES;
	Variable FindVar(std::string name);
	int FindVarNUM(std::string name);
	bool FindLib(std::string name, vector<string> libsList);
	FindUtil(vector<Variable> vars);
	~FindUtil();
};