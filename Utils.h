#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<vector>
#include<iostream>

const std::string removeWhiteSpace(const std::string& input);


const std::vector<std::string> getMathExpression();

const int getOperatorPrecedance(const std::string& givenOperator);

const bool isOperator(const std::string& givenOperator);

const bool isFunction(const std::string& givenOperator);

#endif