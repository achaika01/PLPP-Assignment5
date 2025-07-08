#include <iostream>
#include <string>
#include "Interpreter.h"
using namespace std;

int main()
{
    string text;
    cout << "Enter expression: ";
    getline(cin, text);

    Interpreter inter(text);

    auto tokens = inter.tokenize(text);

    auto rpn = inter.toRPN(tokens);

    int result = inter.calculate(rpn);
    cout << "Result: " << result << endl;

    return 0;


}