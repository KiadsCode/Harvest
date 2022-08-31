#include "FindUtil.h"

FindUtil::FindUtil(vector<Variable> vars)
{
	VARIABLES = vars;
}

FindUtil::~FindUtil()
{
	VARIABLES.clear();
}
Variable FindUtil::FindVar(std::string name)
{
	int VARNUM = 0;
	try
	{
		for (size_t i = 0; i < VARIABLES.size(); ++i)
		{
			if (strcmp(VARIABLES[i].name.c_str(), name.c_str()) == 0)
			{
				VARNUM = i;
			}
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << "\n";
	}
	return VARIABLES.at(VARNUM);
}
int FindUtil::FindVarNUM(std::string name)
{
	int VARNUM = 0;
	try {
		for (size_t i = 0; i < VARIABLES.size(); ++i)
		{
			if (strcmp(VARIABLES[i].name.c_str(), name.c_str()) == 0)
			{
				VARNUM = i;
			}
		}
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << "\n";
	}
	return VARNUM;
}

bool FindUtil::FindLib(std::string name, vector<string> libsList)
{
	bool isFinded = false;
	try {
		for (size_t i = 0; i < libsList.size(); ++i)
		{
			if (strcmp(libsList[i].c_str(), name.c_str()) == 0)
			{
				isFinded = true;
			}
		}
	}
	catch (const std::exception& e) {
		cerr << e.what() << "\n";
	}
	return isFinded;
}
