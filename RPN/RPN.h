#pragma once
#include<queue>
#include<string>
#include<stack>
void parseExpression(std::string& s, std::queue<std::string>&exp);
std::queue<std::string> evaluate(std::queue<std::string>&exp, double&result);