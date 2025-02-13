#ifndef POLYNOMIALSOLVERBONUS_HPP
# define POLYNOMIALSOLVERBONUS_HPP

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

#define YELLOW  "\033[93m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define RED     "\033[31m"

#define BLUE    "\033[95m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

class PolynomialSolver {

private:
    std::map<int, double> coefficients;

    void    parse_equation(const std::string& equation);
    void    get_coefficients (std::string member, int sign);
    void    extract_coefficient (std::string term, int sign);
    int     get_polynomial_degree(bool print);
    void    print_result();
    int     check_term(const std::string& term);

public:
    PolynomialSolver(const std::string& equation);

    void    print_reduce_form();
    void    solve_equation();
};

#endif