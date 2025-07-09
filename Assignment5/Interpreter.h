#include <string>
#include <vector>

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
    //std::string number();
    std::vector<std::string> tokenize(const std::string& text);
    std::vector<std::string> toRPN(const std::vector<std::string>& tokens);
    int calculate(const std::vector<std::string>& rpn);

};
