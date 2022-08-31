#include "Function.h"

Function::Function(string NAME, int ONLINE, int ENDLINE, vector<Variable> VARIABLES)
{
	name = NAME;
	onLine = ONLINE;
	endLine = ENDLINE;
	vars = VARIABLES;
}
