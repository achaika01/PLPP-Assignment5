#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cmath>
#include <algorithm>
#include "Interpreter.h"
using namespace std;

std::map<std::string, FunctionDef> Interpreter::user_functions;

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
    int i = 0;

    while (i < text.size()) {
        if (isspace(text[i])) {
            i++;
            continue;
        }

        if (isdigit(text[i])) {
            std::string number;
            while (i < text.size() && isdigit(text[i])) {
                number += text[i];
                i++;
            }
            tokens.push_back(number);
            continue;
        }

        if (isalpha(text[i])) {
            std::string func_name;
            while (i < text.size() && (isalpha(text[i]))) {
                func_name += text[i];
                i++;
            }
            tokens.push_back(func_name);
            continue;
        }

        if (text[i] == ',') {
            tokens.push_back(",");
            i++;
            continue;
        }

        if (text[i] == '(' || text[i] == ')') {
            tokens.push_back(std::string(1, text[i]));
            i++;
            continue;
        }

        if (is_operator(text[i])) {
            std::string op(1, text[i]);
            if (op == "-" && (tokens.empty() || is_operator(tokens.back()[0]) || tokens.back() == "(" || tokens.back() == ",")) {
                tokens.push_back("u-");
            }
            else {
                tokens.push_back(op);
            }

            i++;
            continue;
        }

        std::cerr << "Unknown character: " << text[i] << std::endl;
        i++;
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
                (user_functions.count(stack.top()) || stack.top() == "pow" || stack.top() == "abs" || stack.top() == "max" || stack.top() == "min")) {
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

        else if (user_functions.count(token) || token == "pow" || token == "abs" || token == "max" || token == "min") {
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
            else if (user_functions.count(token)) {
                FunctionDef func = user_functions[token];

                if (cal_stack.size() < func.parameters.size()) cerr << "Not enough parameters" << endl;

                std::vector<int> args(func.parameters.size());

                for (int i = func.parameters.size() - 1; i >= 0; --i) {
                    args[i] = cal_stack.top();
                    cal_stack.pop();
                }

                std::string new_body = func.body;
                for (int i = 0; i < func.parameters.size(); ++i) {
                    const std::string& param = func.parameters[i];
                    std::string val = std::to_string(args[i]);

                    int position = 0;
                    while ((position = new_body.find(param, position)) != std::string::npos) {
                        bool left_ok = (position == 0) || !isalnum(new_body[position - 1]);
                        bool right_ok = (position + param.length() == new_body.length()) || !isalnum(new_body[position + param.length()]);
                        if (left_ok && right_ok) {
                            new_body.replace(position, param.length(), val);
                            position += val.length();
                        }
                        else {
                            position += param.length();
                        }
                    }
                }

                std::vector<std::string> new_tokens = tokenize(new_body);
                std::vector<std::string> new_rpn = toRPN(new_tokens);
                int result = calculate(new_rpn);

                cal_stack.push(result);
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

void Interpreter::define_function(const std::string& line) {
    if (line.substr(0, 3) != "def") {
        cerr << "Not a function declaration" << line << endl;
        return;
    }

    FunctionDef func;
    std::string func_name;
    std::vector<std::string> param;
    std::string bod;

    int i = 3;

    while (i < line.size() && isspace(line[i])) i++;


    while (line[i] != '(' && i < line.size()) {
        if (!isspace(line[i])) {
            func_name += line[i];
        }
        i++;
    }

    if (i >= line.size() || line[i] != '(') {
        cerr << "Expected '(' after function name\n";
        return;
    }

    if (line[i] == '(') {
        i++;
        std::string param_buf;
        while (line[i] != ')' && i < line.size()) {
            if (line[i] == ',' || isspace(line[i])) {
                if (!param_buf.empty()) {
                    param.push_back(param_buf);
                    param_buf.clear();
                }
                i++;
                continue;
            }
            param_buf += line[i];
            i++;
        }
    
        if (!param_buf.empty()) {
            param.push_back(param_buf);
        }
    }

    if (i >= line.size() || line[i] != ')') {
        cerr << "Expected ')' after parameters\n";
        return;
    }

    if (line[i] == ')') i++;

    while (i < line.size() && isspace(line[i])) i++;

    if (i >= line.size() || line[i] != '{') {
        cerr << "Expected '{' before function body\n";
        return;
    }

    if (line[i] == '{') i++;

    while (i < line.size() && line[i] != '}') {
        bod += line[i];
        i++;
    }
    
    if (i >= line.size() || line[i] != '}') {
        cerr << "Expected '}' at end of function body\n";
        return;
    }

    func.parameters = param;
    func.body = bod;

    user_functions[func_name] = func;
}

//def sum(a, b) { a + b }