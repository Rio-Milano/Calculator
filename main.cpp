#include<iostream>

#include <string>
#include <vector>
#include<unordered_map>
#include<utility>
#include <iomanip> 

#include"node.h"
#include"ExpressionParser.h"
#include"toPostFix.h"
#include"Utils.h"



int main()
{
    char answer{};

    std::cout << "Press enter :" << std::endl;
    do {
        toPostFix x(getMathExpression());

        Expression_Parser myTree(x.getPostFixExpression());

        std::shared_ptr<node> tree = myTree.toTree();
        std::cout << "Answer is: " << std::setprecision(15) << myTree.evaluateExpressionTree(tree) << std::endl;

        std::cout << "Enter another math expression Again (Y/N):";
        std::cin >> answer;

    }while (tolower(answer) == 'y');

}
