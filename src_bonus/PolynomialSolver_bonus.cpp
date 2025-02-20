#include "../include/PolynomialSolverBonus.hpp"

PolynomialSolver::PolynomialSolver(const std::string& equation) {
    parse_equation(equation);
}

int nbIterationOrPos(const std::string& term, char to_find) {
    int pos = 0;
    int nb = 0;

    for (size_t i = 0; i < term.length(); i ++) {
        if (term[i] == to_find){
            nb ++;
            pos = i;
        }
    }
    if (nb == 0)
        return -1;
    if (nb > 1)
        return (-2);
    else
        return (pos);
}

void PolynomialSolver::parse_equation(const std::string& equation) {
    size_t equalPos;
    std::string leftMember;
    std::string rightMember;
    int nb_equal = nbIterationOrPos(equation, '=');

    if (nb_equal == -2) {
        std::cout << "Error: only one equal is needed." << std::endl;
        exit (0);
    }
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
    double      exponent;
    std::string exponent_str;
    size_t i = 0;

    if (term[i] == '-'){
        sign *= -1;
        i ++;
    }

    size_t  j = i;
    bool    dot = false;
    while ((term[j] >= '0' && term[j] <= '9') || (term[j] == '.' && dot == false)){
        if (term[j] == '.')
            dot = true;
        j ++;
    }
    if (j == i)
        coefficient = 1;
    else {
        coefficient_str = term.substr(i, j - i);
        coefficient = std::atof(coefficient_str.c_str());
    }

    if (j == term.length())
        exponent = 0;
    else {
        j = term.length() - 1;
        while ((term[j] >= '0' && term[j] <= '9')){
            j --;
        }
        if (term[j] == '-') {
            std::cout << "Error in exponent: " << term << std::endl;
            exit(0);
        }
        if (term[j] == 'X' || term[j] == 'x')
            exponent = 1;
        else {
            exponent_str = term.substr(j + 1, term.length() - 1);
            exponent = std::atof(exponent_str.c_str());
            if (exponent > 2147483647) {
                std::cout << "Error in exponent: " << term << std::endl;
                exit(0);
            }
        }
    }
    coefficients[exponent] += sign * coefficient;
    return;
}

int PolynomialSolver::check_term(const std::string& term) {
    int nb_minus = nbIterationOrPos(term, '-');
    int nb_asterisk = nbIterationOrPos(term, '*');
    int nb_dot = nbIterationOrPos(term, '.');
    int nb_x = nbIterationOrPos(term, 'x');
    int nb_X = nbIterationOrPos(term, 'X');
    int nb_x_abs;
    int nb_caret = nbIterationOrPos(term, '^');

    if (nb_asterisk == -2) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_minus == -2 || nb_minus > 0 || (nb_minus == 0 && term.size() == 1)) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if ((nb_X >= 0 && nb_x >= 0) || nb_x == -2 || nb_X == -2) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_X >= 0)
        nb_x_abs = nb_X;
    else
        nb_x_abs = nb_x;
    if (nb_asterisk >=0 && nb_asterisk + 1 != nb_x_abs) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_caret == -2 || nb_caret == static_cast<int>(term.length()) -1) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_caret >= 0 && (nb_x_abs == -1 || nb_caret - nb_x_abs != 1)) {
        if (nb_x_abs == -1) {
            std::cout << "Error in term: " << term << std::endl;
            return 1;
        }
        if (nb_caret - nb_x_abs != 1) {
            std::cout << "Error in term: " << term << std::endl;
            return 1;
        }
        if (term[nb_caret] ) {
            std::cout << "Error in term: " << term << std::endl;
            return 1;
        }
    }
    if (nb_caret == -1 && nb_x_abs >= 0 && nb_x_abs != static_cast<int>(term.length()) -1) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_dot == -2 || (nb_dot >= 0 && nb_x_abs >= 0 && (nb_x_abs - nb_dot < 0))) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    if (nb_dot == 0 || (nb_dot > 0 && (term[nb_dot - 1] < '0' || term[nb_dot - 1] > '9' || term[nb_dot + 1] < '0' || term[nb_dot + 1] > '9'))) {
        std::cout << "Error in term: " << term << std::endl;
        return 1;
    }
    return 0;
}

void PolynomialSolver::get_coefficients(std::string member, int sign) {
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
            if (check_term(terme))
                exit (0);
            extract_coefficient(terme, sign);
            terme = member_without_space[i];
        } 
        else if (member_without_space[i] == '+') {
            if (check_term(terme))
                exit (0);
            extract_coefficient(terme, sign);
            terme = "";
        } 
        else
            terme += member_without_space[i];
    }
    
    if (!terme.empty()) {
        if (check_term(terme))
            exit (0);
        extract_coefficient(terme, sign);
    }
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
            if (exponent == 0)
                std::cout << coefficient;
            else if (exponent == 1)
                std::cout << coefficient << " * X";
            else
                std::cout << coefficient << " * X^" << exponent;
            first = false;
        }
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
    bool empty = true;

    if (!coefficients.empty()){
        for (it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
            if (it->second != 0){
                empty = false;
                break;
            }
        }
        if (empty)
            max_degree = 0;
        else
            max_degree = it->first;
    }
    else
        max_degree = -1;
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

double myAbs(double x) {
    if (x < 0)
        return -x;
    return x;
}

double round_double(double nb) {
    int intNb = static_cast<int>(nb);
    double fraction = nb - intNb;

    if (fraction >= 0.5) {
        return intNb + 1;
    }
    return intNb;
}

std::string get_irreductible_fraction(double nb, int return_type) {
    int i = 1;
    double result = nb * i;
    
    while (myAbs(result - round_double(result)) > 1e-9) {
        i++;
        result = nb * i;
    }
    
    int numerator = static_cast<int>(round_double(result));
    
    std::stringstream fraction;
    if (return_type == 1)
        fraction << numerator;
    else if (return_type == 2)
        fraction << i;
    else
        fraction << numerator << "/" << i;
    return fraction.str();
}

void PolynomialSolver::solve_equation() {
    int degree = get_polynomial_degree(true);

    if (degree > 2) {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return ;
    }
    if (degree == 0){
        if (coefficients[0] == 0)
            std::cout << "Any real number is a solution." << std::endl << std::endl;
        else
            std::cout << "No solution." << std::endl << std::endl;
    }
    else if (degree == 1) {
        double a = coefficients[1];
        double b = coefficients[0];
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
            std::cout << YELLOW << "Discriminant is strictly negative, the two complex solutions are:" << RESET << std::endl;
            std::cout << get_irreductible_fraction(-b / (2 * a), 3) << " + " << get_irreductible_fraction(mySqrt(-delta) / (2 * a), 1) << "i/" << get_irreductible_fraction(mySqrt(-delta) / (2 * a), 2) << std::endl;
            std::cout << get_irreductible_fraction(-b / (2 * a), 3) << " - " << get_irreductible_fraction(mySqrt(-delta) / (2 * a), 1) << "i/" << get_irreductible_fraction(mySqrt(-delta) / (2 * a), 2) << std::endl << std::endl;
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