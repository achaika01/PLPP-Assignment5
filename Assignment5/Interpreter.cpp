#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>
#include <algorithm>
#include "Interpreter.h"
using namespace std;

bool Interpreter::is_operator(char c) {
    return std::string("+-*/()u-").find(c) != std::string::npos;
}

int Interpreter::OperationPriority(std::string& operation) {
    if (operation == "+" || operation == "-") return 1;
    else if (operation == "*" || operation == "/") return 2;
    else if (operation == "u-") return 3;
    else if (operation == "pow" || operation == "abs" || operation == "max" || operation == "min") return 4;
    return 0;
}

void Interpreter::advance() {
    pos++;
    if (pos >= text.size()) {
        current_char = '\0';
    }
    else {
        current_char = text[pos];
    }
}

void Interpreter::skip_whitespace() {
    while (current_char != '\0' && isspace(current_char)) {
        advance();
    }
}

//std::string Interpreter::number() {
//    std::string result;
//    while (current_char != '\0' && isdigit(current_char)) {
//        result += current_char;
//        advance();
//    }
//    return result;
//}

std::vector<std::string> Interpreter::tokenize(const std::string& text) {
    vector<std::string> tokens;
    std::string token;
    std::string func;

    for (int i = 0; i < text.size();i++) {
        if (isdigit(text[i])) {
            if (!func.empty()) {
                tokens.push_back(func);
                func.clear();
            }
            token += text[i];
        }
        else if (isspace(text[i])) {
            if (!func.empty()) {
                tokens.push_back(func);
                func.clear();
            }
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (is_operator(text[i])) {
            if (!func.empty()) {
                tokens.push_back(func);
                func.clear();
            }
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            std::string op(1, text[i]);
            if (op == "-" && (tokens.empty() || is_operator(tokens.back()[0]) || tokens.back() == "(" || tokens.back() == ",")) {
                tokens.push_back("u-");
            }
            else {
                tokens.push_back(op);
            }
        }
        else if (isalpha(text[i])) {
            func += text[i];
        }
        else if (text[i] == ',') {
            if (!func.empty()) {
                tokens.push_back(func);
                func.clear();
            }
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(",");
        }
        else {
            cerr << "Unknown character: " << text[i] << endl;
        }
    }


    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<std::string> Interpreter::toRPN(const vector<std::string>& tokens) {
    vector<std::string> output;
    stack<std::string> stack;

    for (int i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];

        if (isdigit(token[0])) {
            output.push_back(token);
        }

        else if (token == "(") {
            stack.push(token);
        }

        else if (token == ")") {
            while (!stack.empty() && stack.top() != "(") {
                output.push_back(stack.top());
                stack.pop();
            }

            if (stack.empty()) {
                cerr << "Mismatched parentheses!" << endl;
                return {};
            }

            stack.pop();

            if (!stack.empty() &&
                (stack.top() == "pow" || stack.top() == "abs" || stack.top() == "max" || stack.top() == "min")) {
                output.push_back(stack.top());
                stack.pop();
            }
        }

        else if (is_operator(token[0])) {
            while (!stack.empty() && OperationPriority(token) <= OperationPriority(stack.top())) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }

        else if (token == "pow" || token == "abs" || token == "max" || token == "min") {
            stack.push(token);
        }
        else if (token == ",") {
            while (!stack.empty() && stack.top() != "(") {
                output.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                cerr << "Error: misplaced comma or mismatched parentheses" << endl;
                return {};
            }
        }

        else {
            cerr << "unknown token" << endl;
        }
    }
    while (!stack.empty()) {
        if (stack.top() == "(") {
            cerr << "Mismatched parentheses!" << endl;
            return {};
        }
        output.push_back(stack.top());
        stack.pop();
    }
    return output;
}

int Interpreter::calculate(const vector<std::string>& rpn) {
    stack<int> cal_stack;

    for (const std::string token : rpn) {
        if (isdigit(token[0])) {
            cal_stack.push(stoi(token));
        }
        else {
            if (token == "u-") {
                int num = cal_stack.top();
                cal_stack.pop();
                cal_stack.push(-num);
            }
            else if (token == "abs") {
                int num = cal_stack.top();
                cal_stack.pop();
                cal_stack.push(abs(num));
            }
            else {
                int num2 = cal_stack.top();
                cal_stack.pop();
                int num1 = cal_stack.top();
                cal_stack.pop();
                int result = 0;

                if (token == "+") result = num1 + num2;
                else if (token == "-") result = num1 - num2;
                else if (token == "*") result = num1 * num2;
                else if (token == "/") {
                    if (num2 == 0) {
                        cerr << "You can't divide by 0" << endl;
                        exit(1);
                    }
                    else result = num1 / num2;
                }
                else if (token == "max") result = max(num1, num2);
                else if (token == "min") result = min(num1, num2);
                else if (token == "pow") result = pow(num1, num2);
                else
                {
                    cout << "Invalid operator" << endl;
                }

                cal_stack.push(result);
            }
           
        }
    }
    return cal_stack.top();

}