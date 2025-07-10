#include <iostream>
#include <string>
#include "Interpreter.h"
using namespace std;

int main()
{
    string text;
    cout << "Enter expression: ";
    getline(cin, text);

    if (text == "test") {
        std::string expr;
        while (getline(cin, expr)) {
            if (expr.empty()) break;

            Interpreter inter(expr);
            if (expr.substr(0, 3) == "def") {
                inter.define_function(expr);
            }
            else {
                auto tokens = inter.tokenize(expr);
                auto rpn = inter.toRPN(tokens);
                if (!rpn.empty()) {
                    int result = inter.calculate(rpn);
                    cout << "Result: " << result << endl;
                }
            }
        }
        return 0;
    }

    do {
        Interpreter inter(text);

        if (text.substr(0, 3) == "def") {
            inter.define_function(text);
        }
        else {
            auto tokens = inter.tokenize(text);
            auto rpn = inter.toRPN(tokens);
            if (!rpn.empty()) {
                int result = inter.calculate(rpn);
                cout << "Result: " << result << endl;
            }
        }

        cout << "Enter expression: ";
    } while (getline(cin, text) && text != "exit");

    return 0;
}


//for (const auto& pair : inter.user_functions) {
//    std::cout << pair.first << std::endl;
//}

//cout << "Tokens: ";
//for (const auto& t : tokens) cout << t << " ";
//cout << endl;

//cout << "RPN: ";
//for (const auto& t : rpn) cout << t << " ";
//cout << endl;
