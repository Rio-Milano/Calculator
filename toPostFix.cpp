#include "toPostFix.h"

toPostFix::toPostFix(const std::vector<std::string>& givenInFixExpression)
{
    inFixExpression = givenInFixExpression;//take in the post fix expression
}

const std::vector<std::string>& toPostFix::getPostFixExpression()

{
    for (unsigned int i = 0; i < inFixExpression.size(); i++)//loop through all tokens
    {
        std::string token = inFixExpression[i];//get the current token
        if (!isOperator(token) && !isFunction(token))//if the token is not a function and not an operator
            postFixExpression.emplace_back(token);//add token to result
        else
        {
            if (token == "(")
                operatorStack.push_back(token);
            else if (token == ")")
            {
                //while we dont have access to the ( 
                while (!operatorStack.empty() && operatorStack[operatorStack.size() - 1] != "(") {
                    postFixExpression.emplace_back(operatorStack[operatorStack.size() - 1]);//put the top of the operator stack into the result
                    operatorStack.pop_back();//remove the top of the operator stack
                }
                operatorStack.pop_back();//when we have access to ( then remove it
            }
            else//if we have an operator
            {
                //get the operator precedance of the token
                int tokenOperatorPrecedance = getOperatorPrecedance(token);
                while (!operatorStack.empty() && getOperatorPrecedance(operatorStack[operatorStack.size() - 1]) >= tokenOperatorPrecedance)//"and precedance is left to right"
                {//while the operator stack is not empty and the top of the operator stack has a greater operator 
                 //precedance than the operator precedance of the token and the token is not right associative 

                    //^ can be stacked on top of eachother but cant be stacked onto a function
                    if (token == "^" && (operatorStack[operatorStack.size() - 1] == "^"))
                        break;
                    postFixExpression.emplace_back(operatorStack[operatorStack.size() - 1]);//put the top of the operator stack into the expression
                    operatorStack.pop_back();//remove the top of the operator stack
                }
                operatorStack.push_back(token);//when we can finally insert the token then do so
            }
        }
    }
    while (operatorStack.size() > 0)//push any remaining operators into the expression
    {
        postFixExpression.push_back(operatorStack[operatorStack.size() - 1]);
        operatorStack.pop_back();
    }

    return postFixExpression;
}

const int toPostFix::getOperatorPrecedance(const std::string& givenOperator)
{
    //get the precedance of the token
    if (givenOperator == "^")
        return 4;
    if (givenOperator == "*")
        return 3;
    if (givenOperator == "/")
        return 3;
    if (givenOperator == "+")
        return 2;
    if (givenOperator == "-")
        return 2;
    if (givenOperator == "(")
        return 1;
    if (givenOperator == ")")
        return 1;
    if (givenOperator == "cos")
        return 5;
    if (givenOperator == "tan")
        return 5;
    if (givenOperator == "sin")
        return 5;
    else
        return 0;

}

const bool toPostFix::isOperator(const std::string& givenOperator)
{
    //determine if the token is an operator
    if (givenOperator == "^")
        return true;
    if (givenOperator == "*")
        return true;
    if (givenOperator == "/")
        return true;
    if (givenOperator == "+")
        return true;
    if (givenOperator == "-")
        return true;
    if (givenOperator == "(")
        return true;
    if (givenOperator == ")")
        return true;
    return false;
}

const bool toPostFix::isFunction(const std::string& givenOperator)
{
    //determine if the token is a function
    if (givenOperator == "cos")
        return true;
    if (givenOperator == "tan")
        return true;
    if (givenOperator == "sin")
        return true;
    return false;
}
