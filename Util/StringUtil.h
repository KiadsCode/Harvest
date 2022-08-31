#pragma once

#include <iostream>
#include <string>
using namespace std;

class StringUtil
{
public:
	string replace(string& source, char oldChar, char newChar);
	string tabRemover(string& source);
	string spaceRemover(string& source);
};