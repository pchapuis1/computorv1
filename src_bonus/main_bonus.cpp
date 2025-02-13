#include <iostream>
#include "../include/PolynomialSolverBonus.hpp"

size_t input_check(const std::string& equation) {
    std::string allowedChars = "0123456789+-*.=Xx^ ";
    
    return equation.find_first_not_of(allowedChars);
}

int main(int argc, char **argv){
    size_t forbidden_char_pos;

    if (argc != 2){
        std::cout << "Usage: ./computor [polynomial equation] | example: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" << std::endl;
        return 0;
    }

    forbidden_char_pos = input_check(argv[1]);
    if (forbidden_char_pos != std::string::npos){ 
        std::cout << "Forbidden character is in the equation: " << argv[1][forbidden_char_pos] <<". Example: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" << std::endl;
        return 0;
    }
    PolynomialSolver solver(argv[1]);
    solver.print_reduce_form();
    solver.solve_equation();
    return 0;
}