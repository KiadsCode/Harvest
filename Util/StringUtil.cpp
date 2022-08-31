#include "StringUtil.h"

string StringUtil::replace(string& source, char oldChar, char newChar)
{
    string edited = source;

	for (size_t i = 0; i < edited.length(); i++)
	{
		if (edited[i] == oldChar)
			edited[i] = newChar;
	}

    return edited;
}

string StringUtil::tabRemover(string& source)
{
	string edited = source;
	int EndOfTabs = 0;

	for (size_t i = 0; i < edited.length(); i++)
	{
		if (edited[i] != '\t') {
			EndOfTabs = i;
			break;
		}
	}
	edited = edited.substr(EndOfTabs, edited.length());

	return edited;
}
string StringUtil::spaceRemover(string& source)
{
	string edited = source;
	int EndOfSpaces = 0;

	for (size_t i = 0; i < edited.length(); i++)
	{
		if (edited[i] != ' ') {
			EndOfSpaces = i;
			break;
		}
	}
	edited = edited.substr(EndOfSpaces, edited.length());

	return edited;
}