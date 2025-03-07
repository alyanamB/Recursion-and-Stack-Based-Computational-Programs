#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>


// evalPostFix Method: evaluate postfix expression.
int evalPostFix(const std::string &postfix) {
    // declare variables.
    std::stack<int> numbers;
    std::istringstream tokens(postfix);
    std::string token;

    // Read tokens from postfix expression.
    while (tokens >> token) {
        // Check if token is postive or negative
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            // Push token unto the stack.
            numbers.push(std::stoi(token));
        }
        else {
            // For debugging purposes.
            if (numbers.size() < 2) {
                std::cout << "Invalid postfix expression" << std:: endl;
                return -1;
            }
            
            //  Pop two numbers from stack.
            int right = numbers.top();
            numbers.pop();
            int left = numbers.top();
            numbers.pop();

            // Evaluate answer based on operator.
            if (token == "+") {
                numbers.push(left + right);
            } 
            else if (token == "-") {
                numbers.push(left - right);
            } 
            else if (token == "*") {
                numbers.push(left * right);
            } 
            else if (token == "/") {
                // For debugging purposes make sure there isn't division by zero.
                if (right == 0) {
                    std::cout << "Division by zero" << std::endl;
                    return -1;
                }
                int quotient = left / right;
                // For floor division
                if (left % right != 0 && (left < 0) != (right < 0)) {
                    quotient--;
                }
                numbers.push(quotient);
            }
            else if (token == "^") {
                numbers.push(static_cast<int>(std::pow(left, right)));
            }
            else {
                // For debugging purposes.
                std::cout << "Incorrect operator" << std::endl;
                return -1;
            }
        }
    }
    // Return answer if stack only has one element left.
    if (numbers.size() == 1) {
        return numbers.top();
    }
    std::cout << "Invalid expression" << std::endl;
    return -1;
}

// Main.
int main(int argc, char *argv[]) {
    // For debugging purposes.
    if (argc < 2) {
        std::cout << "Error: incorrect amount of arguements." << std::endl;
        return 1;
    }

    // Store command line arguement in corresponding variable.
    std::string postfix = argv[1];
    // If input is -1, output -1 and return.
    if (postfix == "-1") {
        std::cout << "-1" << std::endl;
        return 0;
    }
    // Store answer from evaluating postfix expression.
    int answer = evalPostFix(postfix);
    // Print output if evaluation is successful.
    if (answer != -1) {
        std::cout << answer << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }
    return 0;
}
