#include "../include/PolynomialSolver.hpp"

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
    double      coefficient;
    std::string coefficient_str;
    int         exponent;
    std::string exponent_str;
    size_t i = 0;

    if (term[i] == '-'){
        sign *= -1;
        i ++;
    }
    coefficient_str = term.substr(i, term.find('*') - i);
    coefficient = std::atof(coefficient_str.c_str());

    size_t j = term.length() - 1;
    while ((term[j] >= '0' && term[j] <= '9')){
        j --;
    }
    exponent_str = term.substr(j + 1, term.length() - 1);
    exponent = std::atof(exponent_str.c_str());

    coefficients[exponent] += sign * coefficient;
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
    return;
}

void PolynomialSolver::print_reduce_form() {
    std::cout << "Reduced form: ";

    std::map<int, double>::const_iterator it = coefficients.begin();
    bool first = true;

    while (it != coefficients.end()) {
        int exponent = it->first;
        double coefficient = it->second;

        if (!first) {
            if (coefficient >= 0)
                std::cout << " + ";
            else {
                std::cout << " - ";
                coefficient = -coefficient;
            }
        }
        std::cout << coefficient << " * X^" << exponent;
        first = false;
        ++it;
    }
    if (!get_polynomial_degree(false) && coefficients[0] == 0)
        std::cout << "0";
    std::cout << " = 0" << std::endl;
    return ;
}

int PolynomialSolver::get_polynomial_degree(bool print) {
    std::map<int, double>::reverse_iterator it;
    int max_degree;

    if (!coefficients.empty()){
        for (it = coefficients.rbegin(); it != coefficients.rend() && it->second == 0; ++it) {}
        max_degree = it->first;
    }
    else
        max_degree = -1;
    if (print)
        std::cout << "Polynomial degree: " << max_degree << std::endl;
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

    if (degree > 2){
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return ;
    }
    if (degree == 0)
        std::cout << "There is an infinity of solution." << std::endl;
    else if (degree == 1) {
        double a = coefficients[1];
        double b = coefficients[0];
        std::cout << "The solution is:" << std::endl << -b / a << std::endl;
    }
    else if (degree == 2) {
        double a = coefficients[2];
        double b = coefficients[1];
        double c = coefficients[0];
        double delta = b * b - 4 * a * c;
        
        if (delta < 0) {
            std::cout << "The discriminant is negative, there is no solutions." << std::endl;
        }
        else if (delta == 0) {
            std::cout << "The discriminant is null, the unique solution is:" << std::endl << (-b / (2 * a)) << std::endl;
        }
        else {
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << (-b - mySqrt(delta)) / (2 * a) << std::endl;
            std::cout << (-b + mySqrt(delta)) / (2 * a) << std::endl;
        }
    }
    return;
}
