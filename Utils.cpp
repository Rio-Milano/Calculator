#include"Utils.h"

const std::string removeWhiteSpace(std::string& input)
{
    std::string s_expression{};
    for (char character : input)
    {
        if (character != ' ')
            s_expression += character;
    }
    return s_expression;
}

const std::vector<std::string> getMathExpression()
{
    //Variables
    std::vector<std::string> mathExpression;
    std::string buildString = "";
    std::string input;

    //Get expression
    std::cin.ignore();
    std::cout << "Enter math expression: ";
    std::getline(std::cin, input);

    input = removeWhiteSpace(input);

    for (unsigned int i = 0; i < input.size(); i++)//Loop through each character in expression
    {
        char character = input[i];//get the current character   

        if ((i == 0 || //Start Scope
            (input.size() > 0 && input[i - 1] == '(')) && //Open bracket scope
            character == '-')//Negative deceleration
            buildString += '-';//add a minus to the token so the following number can be build onto it

        else if (isdigit(character) || character == '.')//if character is a number
            buildString += character;//add to current token

        else if (character == '^' ||//if character is an operator
            character == '*' ||
            character == '/' ||
            character == '+' ||
            character == '-' ||
            character == '(' ||
            character == ')')
        {
            //Check if the operator is defining a negative
            if ((i >= 1 && character == '-') &&
                (input[i - 1] == '^' ||//if character is an operator
                    input[i - 1] == '*' ||
                    input[i - 1] == '/' ||
                    input[i - 1] == '+' ||
                    input[i - 1] == '-')
                )

                buildString += "-";//define the negative

            else//define a binary operator
            {
                if (buildString.size() > 0)//Add token to expression if there is one
                {
                    mathExpression.push_back(buildString);//push it to expression
                    buildString = "";//reset token
                }
                buildString += character;//put operator into token (to convert to string)
                mathExpression.push_back(buildString);//push token into expression
                buildString = "";//reset token
            }
        }
        else//if not a operand or operator then we must be taking in a function name
            buildString += character;//add the character of the function to the token
    }

    //once loop is complete
    if (buildString.size() > 0)//Push the remaining token into the expression
        mathExpression.push_back(buildString);

    return mathExpression;
}
