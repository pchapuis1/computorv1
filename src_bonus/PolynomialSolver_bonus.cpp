#include "../include/PolynomialSolverBonus.hpp"

PolynomialSolver::PolynomialSolver(const std::string& equation) {
    parse_equation(equation);
}

void PolynomialSolver::parse_equation(const std::string& equation) {
    size_t equalPos;
    std::string leftMember;
    std::string rightMember;

    equalPos = equation.find('=');
    if (equalPos == std::string::npos) {
        std::cout << "An '=' is needed." << std::endl;
        exit(0);
    }
    leftMember = equation.substr(0, equalPos);
    rightMember = equation.substr(equalPos + 1, -1);
    
    get_coefficients(leftMember, 1);
    get_coefficients(rightMember, -1);
    return;
}

void PolynomialSolver::extract_coefficient(std::string term, int sign) {
    double coefficient;
    int exponent;
    size_t i = 0;
    std::string coefficient_str;

    if (term[i] == '-'){
        sign *= -1;
        i ++;
    }
    coefficient_str = term.substr(i, term.find('*') - i);
    coefficient = std::atof(coefficient_str.c_str());

    exponent = term[term.length() - 1] - '0';

    coefficients[exponent] += sign * coefficient;
    // std::cout << "Term: " << term << std::endl;
    // std::cout << coefficient_str << std::endl;
    return;
}

void PolynomialSolver::get_coefficients(std::string member, int sign) {
    (void)sign;
    std::vector<std::string> terms;
    std::string member_without_space;
    std::string terme;
    
    for (size_t i = 0; i < member.length(); ++i) {
        if (member[i] != ' ') {
            member_without_space += member[i];
        }
    }

    // std::cout << "member clear:" << member_without_space << std::endl;

    for (size_t i = 0; i < member_without_space.length(); ++i) {
        if (terme.empty()) {
            terme += member_without_space[i];
            continue;
        }

        if (member_without_space[i] == '-') {
            extract_coefficient(terme, sign);
            terms.push_back(terme);
            terme = member_without_space[i];
        } 
        else if (member_without_space[i] == '+') {
            extract_coefficient(terme, sign);
            terms.push_back(terme);
            terme = "";
        } 
        else
            terme += member_without_space[i];
    }
    
    if (!terme.empty()) {
        extract_coefficient(terme, sign);
        terms.push_back(terme);
    }

    // for (std::map<int, double>::const_iterator it = coefficients.begin(); it != coefficients.end(); ++it) {
    //     std::cout << "exponent: " << it->first << " coefficient: " << it->second << std::endl;
    // }

    return;
}

void PolynomialSolver::print_reduce_form() {
    std::cout << MAGENTA << "Reduced form: " << RESET;

    std::map<int, double>::const_iterator it = coefficients.begin();
    bool first = true;

    while (it != coefficients.end()) {
        int exponent = it->first;
        double coefficient = it->second;

        if (coefficient != 0) {
            if (!first) {
                if (coefficient > 0)
                    std::cout << " + ";
                else {
                    std::cout << " - ";
                    coefficient = -coefficient;
                }
            }
            std::cout << coefficient << " * X^" << exponent;
            first = false;
        }
        ++it;
    }
    if (!get_polynomial_degree(false) && coefficients[0] == 0)
        std::cout << "0";
    std::cout << " = 0" << std::endl;
    // std::cout << "degree: " << get_polynomial_degree(false) << std::endl;
    return ;
}

int PolynomialSolver::get_polynomial_degree(bool print) {
    std::map<int, double>::reverse_iterator it;
    int max_degree;
    // double max_degree_coeff;

    if (!coefficients.empty()){
        // max_degree = coefficients.rbegin()->first;
        for (it = coefficients.rbegin(); it != coefficients.rend() && it->second == 0; ++it) {
            // std::cout << "\n firdt: " << it->first << " " << it->second << std::endl;
            // max_degree_coeff = it->second;
        }
        max_degree = it->first;
    }
    else
        max_degree = -1;
    // if (max_degree_coeff == 0)
        // max_degree = 0
    // if (!coefficients.empty())
        // max_degree = coefficients.rbegin()->first;
    // else
    if (print)
        std::cout << GREEN << "Polynomial degree: " << RESET << max_degree << std::endl;
    return max_degree;
}

double mySqrt(double delta) {
    if (delta == 1)
        return delta;
    
    double x = delta;
    double result = x / 2.0;

    while (std::abs(x - result) > 1e-6) {
        x = result;
        result = (x + delta / x) / 2.0;
    }
    return result;
}

void PolynomialSolver::solve_equation() {
    int degree = get_polynomial_degree(true);

    if (degree > 2) {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return ;
    }
    if (degree == 0)
        std::cout << "There is an infinity of solution." << std::endl;
    else if (degree == 1) {
        double a = coefficients[1];
        double b = coefficients[0];
        // std::cout << "a: " << a << " b: " << b << std::endl;
        std::cout << "The solution is:" << std::endl;
        std::cout << CYAN << "x = " << RESET << RED << "-b / a" << RESET << std::endl;
        std::cout << CYAN << "x = " << RESET << RED << "-" << b << " / " << a << RESET << std::endl;
        std::cout << CYAN << "x = " << RESET << RED << -b / a << RESET << std::endl;
        std::cout << "The solution is x = " << RED << -b / a << RESET << std::endl;
    }
    else if (degree == 2) {
        double a = coefficients[2];
        double b = coefficients[1];
        double c = coefficients[0];
        double delta = b * b - 4 * a * c;
        
        std::cout << YELLOW << "The discriminant value is: " << RESET << delta << std::endl;
        if (delta < 0) {
            std::cout << YELLOW << "The discriminant is negative, there is no solutions." << RESET << std::endl;
        }
        else if (delta == 0) {
            double x1 = (-b / (2 * a));
            std::cout << YELLOW << "The discriminant is null, the unique solution is:" << RESET << std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << "-b / (2 * a)" << RESET<< std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << "-" << b << " / (2 * " << a << ")" << RESET << std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << x1 << RESET << std::endl;
            std::cout << "The unique solution is " << CYAN << "x1" << RESET << " = " << RED << x1 << RESET << "." << std::endl;

        }
        else {
            double x1 = (-b + mySqrt(delta)) / (2 * a);
            double x2 = (-b - mySqrt(delta)) / (2 * a);

            std::cout << YELLOW << "Discriminant is strictly positive, the two solutions are:" << RESET << std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << "(-b + sqrt(delta)) / (2 * a)" << RESET << " | " << CYAN << "x2" << RESET << " = " << RED << "(-b - sqrt(delta)) / (2 * a)" << RESET << std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << "(-" << b << " + sqrt(" << delta << ")) / (2 * " << a << ")" << RESET << " | " << CYAN << "x2" << RESET << " = " << RED << "(-" << b << " - sqrt(" << delta << ")) / (2 * " << a << ")" << RESET << std::endl;
            std::cout << CYAN << "x1" << RESET << " = " << RED << x1 << RESET << " | " << CYAN << "x2" << RESET << " = " << RED << x2 << RESET << std::endl;
            std::cout << "The two solutions are " << CYAN << "x1" << RESET << " = " << RED << x1 << RESET << " and " << CYAN << "x2" << RESET << " = " << RED << x2 << RESET << "." << std::endl;
        }
    }
    return;
}