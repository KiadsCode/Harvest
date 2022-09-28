#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <Libs.h>
#include <Function.h>
using namespace std;

class Lib
{
public:
	void update(vector<Function> nFuncs) {
		funcs = nFuncs;
	}
	vector<Function> funcs;
	string name = "test Lib";
	bool isExported = false;
	Lib(string NAME = "test lib", bool needToExport = false) {
		name = NAME;
		if (needToExport)
			exportLib(true);
	}
private:
	void exportLib(bool needToExport) {
		if (needToExport && !isExported) {
			isExported = true;
		}
	}
};