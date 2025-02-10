#ifndef POLYNOMIALSOLVER_HPP
# define POLYNOMIALSOLVER_HPP

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class PolynomialSolver {

private:
    std::map<int, double> coefficients;

    void parse_equation(const std::string& equation);
    void get_coefficients (std::string member, int sign);
    void extract_coefficient (std::string term, int sign);
    int get_polynomial_degree();
    void print_result();

public:
    PolynomialSolver(const std::string& equation);

    void print_reduce_form();
    void solve_equation();
};

#endif