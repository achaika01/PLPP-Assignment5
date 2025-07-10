#include <string>
#include <vector>
#include <map>
#include "FunctionDef.h"

class Interpreter {
    std::string text;
    int pos;
    char current_char;

public:
    Interpreter(std::string& t) : text(t) {
        pos = 0;
        if (text.empty()) {
            current_char = '\0';
        }
        else {
            current_char = text[pos];
        }
    }
    bool is_operator(char c);
    int OperationPriority(std::string& operation);
    void advance();
    void skip_whitespace();
    std::vector<std::string> tokenize(const std::string& text);
    std::vector<std::string> toRPN(const std::vector<std::string>& tokens);
    int calculate(const std::vector<std::string>& rpn);

    static std::map<std::string, FunctionDef> user_functions;

    void define_function(const std::string& line);

};


