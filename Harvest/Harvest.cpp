﻿#include "Harvest.h"

#pragma region Utils

#define SU StringUtil()
FindUtil FU = FindUtil(Variables);

#pragma endregion
#pragma region CORE

#define Synx Syntax()

#pragma endregion

bool isRun = true;
bool hasError = false;

vector<string> SourceCode;
vector<Variable> FunctionLocalVariables;
int targetLine = 0;

void ParseScript(string& source) {
	FU.VARIABLES = Variables;
	ParseVariable(source);
	//ParseFunction(source);
	ParsePrint(source);
	ParseInput(source);
}

void ParseFunction(string& source) {
	string valid = "";
	string funcName = "";
	for (int i = 0; i < source.length(); i++) {
		if (valid != Synx.voidKeyWord)
			valid += i;
		else
			break;
	}
	if (valid != Synx.varKeyWord)
		return;
	for (size_t i = valid.length(); source[i] != '('; i++)
	{
		if (source[i] != ' ' && source[i] != '(')
			funcName += source[i];
	}
}

void ParseFunctionBody(string& source) {
	ParseLocalVariable(source);
	ParsePrint(source);
	ParseInput(source);
}

void ParsePrint(string& source)
{
	string valid = "";
	for (size_t i = 0; i < source.length(); i++)
	{
		if (valid != Synx.printf) {
			valid += source[i];
		}
		else
			break;
	}
	if (source.at(source.length() - 1) != ';') {
		string text = format("Semicolon required on line - {}", targetLine + 1);
		GetError(text, "ndc");
		return;
	}
	bool inBrackets = false;
	string msg = "";
	bool isVarPrint = false;
	bool inStringBrackets = false;
	for (size_t i = valid.length(); i < source.length(); i++)
	{
		//Brackets switch
		switch (source[i])
		{
		case '(':
			inBrackets = true;
			break;
		case ')':
			inBrackets = false;
			break;
		}

		if (source[i] == '\"' && inBrackets)
			inStringBrackets = !inStringBrackets;
		if (source[i] != '\"' && source[i] != '(' && source[i] != ')' && inBrackets && inStringBrackets) {
			msg += source[i];
			isVarPrint = false;
		}
		if (source[i] != '\"' && source[i] != '(' && source[i] != ')' && inBrackets && !inStringBrackets) {
			msg += source[i];
			isVarPrint = true;
		}
	}
	if (isVarPrint) {
		Variable var = Variables.at(FU.FindVarNUM(msg));
		if (msg != "" && isVarPrint && var.type == Synx.typeString)
			std::cout << var.valueS << endl;
		if (msg != "" && isVarPrint && var.type == Synx.typeInt)
			std::cout << var.valueI << endl;
	}
	else {
		if (msg == "" && isVarPrint) {
			string text = format("No variable data -LINE-- {}", targetLine + 1);
			GetError(text, "ndc");
			return;
		}
		if (msg != "" && !isVarPrint)
			std::cout << msg << endl;
	}
}
void ParseInput(string& source)
{
	int tryTH = 0;
	string valid = "";
	if (tryTH == 0) {
		for (size_t i = 0; i < source.length(); i++)
		{
			if (valid != Synx.inputf) {
				valid += source[i];
			}
			else
				break;
		}
	}
	if (valid != Synx.inputf)
		tryTH++;
	if (source.at(source.length() - 1) != ';') {
		string text = format("Semicolon required on line - {}", targetLine + 1);
		GetError(text, "ndc");
		return;
	}
	bool inBrackets = false;
	string msg = "";
	int arg = 0;
	string varForInput = "";
	bool inStringBrackets = false;
	Variable var("", "", "");
	switch (tryTH)
	{
	case 0:
		for (size_t i = valid.length(); i < source.length(); i++)
		{
			//Brackets switch
			switch (source[i])
			{
			case '(':
				inBrackets = true;
				break;
			case ')':
				inBrackets = false;
				break;
			}

			if (source[i] == '\"' && inBrackets)
				inStringBrackets = !inStringBrackets;
			if (source[i] == ',') {
				arg++;
				inStringBrackets = false;
			}
			if (arg > 1)
				return;
			if (source[i] != '\"' && source[i] != '(' && source[i] != ')' && inBrackets && inStringBrackets && arg == 0) {
				msg += source[i];
			}
			if (source[i] != ' ' && source[i] != ',' && source[i] != '(' && source[i] != ')' && inBrackets && !inStringBrackets && arg == 1) {
				varForInput += source[i];
			}
		}
		if (varForInput == "") {
			string text = format("Can't get access for not existing variable -LINE-- {}", targetLine + 1);
			GetError(text, "try to create or fix name of variable");
			return;
		}
		var = FU.FindVar(varForInput);
		std::cout << msg;
		if (var.type == Synx.typeString)
			cin >> var.valueS;
		if (var.type == Synx.typeInt) {
			string val = "";
			cin >> val;
			var.valueI = atoi(val.c_str());
		}
		Variables.at(FU.FindVarNUM(varForInput)) = var;
		break;
	case 1:
		string val = "";
		for (size_t i = 0; i < source.length(); i++)
		{
			if (val != Synx.inpuGetF)
				val += source[i];
		}
		if (val == Synx.inpuGetF && FU.FindLib("sys", LIBLIST))
			cin >> val;
		break;
	}
}

void ParseLib(string src){}

void addLib(Lib lib) {
	if (!lib.isExported)
		LIBLIST.push_back(lib.name);
}

/// <summary>
/// Выводит ошибку которая произошла во время компиляции
/// </summary>
/// <param name="message">Сообщение для вывода</param>
/// <param name="htfMSG">Способ исправить (для того чтоб не выводить напишите 'ndc')</param>
void GetError(string message, string htfMSG = "ndc") {
	if (!hasError && isRun) {
		isRun = false;
		hasError = true;
		printf("Error occured: %s\n", message.c_str());
		if (htfMSG != "ndc")
			printf("How to fix: %s\n", htfMSG.c_str());
	}
}

void ParseVariable(string& source)
{
	string valid = "";
	string variableName = "";
	string varType = "";
	bool assignToOther = false;
	string varValue = "";
	for (size_t i = 0; i < source.length(); i++)
	{
		if (valid != Synx.varKeyWord)
			valid += source[i];
		else
			break;
	}
	if (valid != Synx.varKeyWord)
		return;
	if (source.at(source.length() - 1) != ';') {
		string text = format("Semicolon required on line - {}", targetLine + 1);
		GetError(text, "ndc");
		return;
	}

	for (size_t i = Synx.varKeyWord.length() + 1; i < source.length(); i++)
	{
		if (source[i] != ' ' && source[i] != '=')
			variableName += source[i];
		else
			break;
	}
	bool inStringBrackets = false;
	for (size_t i = Synx.varKeyWord.length() + variableName.length() + 1; i < source.length(); i++)
	{
		if (source[i] == '\"') {
			inStringBrackets = !inStringBrackets;
			varType = Synx.typeString;
		}
		if (source[i] != '=' && source[i] != ';' && source[i] != '\"' && inStringBrackets && varType == Synx.typeString) {
			varValue += source[i];
			varType = Synx.typeString;
		}
		if (source[i] != '=' && source[i] != ' ' && source[i] != ';' && source[i] != '\"' && !inStringBrackets && varType != Synx.typeString) {
			if (source[i] != '0' && source[i] != '1' && source[i] != '2' && source[i] != '3' && source[i] != '4' && source[i] != '5' && source[i] != '6' && source[i] != '7' && source[i] != '8' && source[i] != '9')
				assignToOther = true;
			else {
				assignToOther = false;
				varType = Synx.typeInt;
			}
			varValue += source[i];
		}
	}
	if (assignToOther && varType == "") {
		Variable vr = FU.FindVar(varValue);
		if (vr.type == Synx.typeInt)
			varValue = vr.valueI;
		if (vr.type == Synx.typeString)
			varValue = vr.valueS;
		varType = vr.type;
	}

	if (varType != Synx.typeString && varType != Synx.typeInt) {
		string text = format("Variable can't be without type -LINE-- {}", targetLine + 1);
		GetError(text, "ndc");
		return;
	}

	if (varType != "" && variableName != "" && varValue != "") {
		Variable var(variableName, varType, varValue);
		Variables.push_back(var);
		FU.VARIABLES = Variables;
	}

}
void ParseLocalVariable(string& source)
{
	string valid = "";
	string variableName = "";
	string varType = "";
	bool assignToOther = false;
	string varValue = "";
	for (size_t i = 0; i < source.length(); i++)
	{
		if (valid != Synx.varKeyWord)
			valid += source[i];
		else
			break;
	}
	if (valid != Synx.varKeyWord)
		return;
	if (source.at(source.length() - 1) != ';')
		return;

	for (size_t i = Synx.varKeyWord.length() + 1; i < source.length(); i++)
	{
		if (source[i] != ' ' && source[i] != '=')
			variableName += source[i];
		else
			break;
	}
	bool inStringBrackets = false;
	for (size_t i = Synx.varKeyWord.length() + variableName.length() + 1; i < source.length(); i++)
	{
		if (source[i] == '\"') {
			inStringBrackets = !inStringBrackets;
			varType = Synx.typeString;
		}
		if (source[i] != '=' && source[i] != ';' && source[i] != '\"' && inStringBrackets && varType == Synx.typeString) {
			varValue += source[i];
			varType = Synx.typeString;
		}
		if (source[i] != '=' && source[i] != ' ' && source[i] != ';' && source[i] != '\"' && !inStringBrackets && varType != Synx.typeString) {
			if (source[i] != '0' && source[i] != '1' && source[i] != '2' && source[i] != '3' && source[i] != '4' && source[i] != '5' && source[i] != '6' && source[i] != '7' && source[i] != '8' && source[i] != '9')
				assignToOther = true;
			else {
				assignToOther = false;
				varType = Synx.typeInt;
			}
			varValue += source[i];
		}
	}
	if (assignToOther && varType == "") {
		Variable vr = FU.FindVar(varValue);
		if (vr.type == Synx.typeInt)
			varValue = vr.valueI;
		if (vr.type == Synx.typeString)
			varValue = vr.valueS;
		varType = vr.type;
	}

	if (varType != "" && variableName != "" && varValue != "") {
		Variable var(variableName, varType, varValue);
		if (varType != Synx.typeString || varType != Synx.typeInt) {
			string text = format("Variable can't be without type -LINE-- {}", targetLine + 1);
			GetError(text, "ndc");
			return;
		}
		FunctionLocalVariables.push_back(var);
	}

}

int main(int argc, const char* argv[])
{
	if (argv[1] != nullptr)
	{
		addLib(sLib);
		ifstream file(argv[1]);
		string srcCode = "";
		if (file.is_open()) {
			while (!file.eof())
			{
				srcCode = "";
				getline(file, srcCode);
				srcCode = SU.tabRemover(srcCode);
				srcCode = SU.spaceRemover(srcCode);
				SourceCode.push_back(srcCode);
			}
			file.close();
			while (targetLine < SourceCode.size() && isRun && !hasError)
			{
				ParseScript(SourceCode.at(targetLine));
				targetLine++;
			}
			if (isRun) {
				Variables.clear();
			}
			if (!isRun && hasError)
			{
				printf("Press any key to continue...");
				_getch();
			}
			return 0;
		}
	}
}