#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <StringUtil.h>
#include <Syntax.h>
#include <Libs.h>
#include <format>
#include <Variable.h>
#include <FindUtil.h>
using namespace std;

sys sLib = sys();

vector<Function> GlobalFunctions;
vector<Variable> Variables;
vector<string> LIBLIST;

void ParseScript(string& source);
void ParseFunctionBody(string& source);
void ParseFE(string& source);
void ParseFunction(string& source);
void ParsePrint(string& source);
bool IsContainsSemiColon(string& source);
string SErrorText();
void ParseInput(string& source);
void GetError(string message, string htfMSG);
void ParseVariable(string& source);
void ParseLocalVariable(string& source);