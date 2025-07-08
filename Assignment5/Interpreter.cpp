#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include "Interpreter.h"
using namespace std;

bool Interpreter::is_operator(char c) {
    return std::string("+-*/()").find(c) != std::string::npos;
}

int Interpreter::OperationPriority(std::string& operation) {
    if (operation == "+" || operation == "-") return 1;
    else if (operation == "*" || operation == "/") return 2;
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

std::string Interpreter::number() {
    std::string result;
    while (current_char != '\0' && isdigit(current_char)) {
        result += current_char;
        advance();
    }
    return result;
}

std::vector<std::string> Interpreter::tokenize(const std::string& text) {
    vector<std::string> tokens;
    std::string number;

    for (char c : text) {
        if (isdigit(c)) {
            number += c;
        }
        else if (isspace(c)) {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
        }
        else if (is_operator(c)) {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(std::string(1, c));
        }
        else {
            cerr << "Unknown character: " << c << endl;
        }
    }


    if (!number.empty()) {
        tokens.push_back(number);
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
            if (!stack.empty() && stack.top() == "(") {
                stack.pop();
            }
            else {
                cerr << "Mismatched parentheses!" << endl;
                return {};
            }
        }

        else if (is_operator(token[0])) {
            while (!stack.empty() && OperationPriority(token) <= OperationPriority(stack.top())) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
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
            int num2 = cal_stack.top();
            cal_stack.pop();
            int num1 = cal_stack.top();
            cal_stack.pop();
            int result = 0;

            if (token == "+") result = num1 + num2;
            else if (token == "-") result = num1 - num2;
            else if (token == "*") result = num1 * num2;
            else if (token == "/") result = num1 / num2;
            else
            {
                cout << "Invalid operator" << endl;
            }

            cal_stack.push(result);
        }
    }
    return cal_stack.top();

}

//5 + (3 * (2 + 4))