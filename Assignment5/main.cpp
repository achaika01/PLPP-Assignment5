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
    cout << "Tokens: ";
    for (const auto& t : tokens) cout << t << " ";
    cout << endl;

    auto rpn = inter.toRPN(tokens);
    cout << "RPN: ";
    for (const auto& t : rpn) cout << t << " ";
    cout << endl;

    int result = inter.calculate(rpn);
    cout << "Result: " << result << endl;

    return 0;


}