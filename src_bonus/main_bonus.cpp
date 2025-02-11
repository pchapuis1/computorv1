#include <iostream>
#include "../include/PolynomialSolverBonus.hpp"

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Usage: ./computor [equation] | example: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" << std::endl;
        return 0;
    }

    PolynomialSolver solver(argv[1]);
    solver.print_reduce_form();
    solver.solve_equation();
    return 0;
}