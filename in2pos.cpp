#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>

// precendence Method: create precedence of operators.
int precedence(char op) {
    // Create precedence of operators by returning number corresponding to lower-higher precedence.
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    return 0;
}

// leftAssociative Method: Check that operator is left associative.
bool leftAssociative(char op) {
    // Return true if operator is not exponential, false otherwise.
    return op != '^';
}

// isOperator Method: Check that character is an operator.
bool isOperator(char c) {
    // Return true if character is one of the operators.
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// infixtoPostfix Method: convert infix expression to postfix notation.
std::string infixToPostfix(const std::string &infix) {
    // Declare variables.
    std::stringstream postfix;
    std::stack<char> operators;
    std::istringstream tokens(infix);
    std::string token;

    // Read each token in expression.
    while (tokens >> token) {
        // Check if token is a number.
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            // Add number to postfix expression.
            postfix << token << ' ';
        }
        // Check if token is a open parenthesis.
        else if (token == "(") {
            // Add open parenthesis onto the stack.
            operators.push('(');
        }
        // Check if token is a closed parenthesis.
        else if (token == ")") {
            // While operators is not empty and there is not an open parenthesis continue to loop.
            while (!operators.empty() && operators.top() != '(') {
                // Add operators to postfix.
                postfix << operators.top() << ' ';
                // Pop operators.
                operators.pop();
            }
            // Check if operators is not empty.
            if (!operators.empty()) {
                // Pop open parenthesis.
                operators.pop();
            }
        }
        // Check if token is an operator.
        else if (isOperator(token[0])) {
            // Store operator.
            char currentOp = token[0];
            // pop operators based on precendence and left or right associativity.
            while (!operators.empty() && 
                ((leftAssociative(currentOp) && precedence(operators.top()) >= precedence(currentOp)) ||
                (!leftAssociative(currentOp) && precedence(operators.top()) > precedence(currentOp)))) {
                    postfix << operators.top() << ' ';
                    operators.pop();
                  }
                  // Push current operator onto the stack.
                  operators.push(currentOp);
        }
    }

    // Pop remaining operators, add to postfix.
    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }

    // return postfix output.
    return postfix.str();
}

// Main.
int main(int argc, char *argv[]) {
    // for debugging purrposes.
    if (argc != 2) {
        std::cout << "Error: incorrect amount of arguements." << std::endl;
        return 1;
    }

    // Store command line arguement in corresponding variable.
    std::string infix = argv[1];
    // Store infix to postfix output.
    std::string postfix = infixToPostfix(infix);
    // Print output.
    std::cout << postfix << std::endl;
    return 0;
}
