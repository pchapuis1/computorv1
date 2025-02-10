#include <iostream>
#include "../include/PolynomialSolver.hpp"

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Only one arguments needed!" << std::endl;
        return 0;
    }

    PolynomialSolver solver(argv[1]);
    solver.print_reduce_form();
    solver.solve_equation();
    return 0;
}