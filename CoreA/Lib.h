#pragma once
#include <string>
#include <iostream>
#include <Libs.h>
using namespace std;

class Lib
{
public:
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