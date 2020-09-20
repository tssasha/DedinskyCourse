#include <iostream>
#include <cmath>
#include "library.hpp"

int PrintCoefficients(double *coefficients) {
    std::cout << "Print the coefficients of the equation a*x^2 + b*x + c = 0" << std::endl;
    std::cout << "a = ";
    std::cin >> coefficients[0];
    std::cout << "b = ";
    std::cin >> coefficients[1];
    std::cout << "c = ";
    std::cin >> coefficients[2];
    return 0;
}

bool IsZero(double num) {
    return num < EPSILON && num > -EPSILON;
}

double Discriminant(double *coefficients) {
    return coefficients[1] * coefficients[1] - 4.0 * coefficients[0] * coefficients[2]; //-----?
}

int IdenticalSolution(double *solutions, double coefficient) {
    if (IsZero(coefficient)) {
        solutions[0] = 1;
        solutions[1] = 0;
    }
    else {
        solutions[0] = 0;
    }
    return 0;
}

int LinearSolution(double *solutions, double *coefficients) {
    solutions[0] = 1;
    solutions[1] = -coefficients[2] / coefficients[1];
    return 0;
}

int QuadraticSolution(double *solutions, double *coefficients) {
    double discriminant = Discriminant(coefficients);
    if (!IsZero(discriminant) && discriminant < 0) {
        solutions[0] = 0;
    }
    else if (IsZero(discriminant)) {
        solutions[0] = 1;
        solutions[1] = -coefficients[1] / 2 / coefficients[0];
    }
    else {
        solutions[0] = 2;
        solutions[1] = (-coefficients[1] + sqrt(discriminant)) / 2 / coefficients[0];
        solutions[2] = (-coefficients[1] - sqrt(discriminant)) / 2 / coefficients[0];
    }
    return 0;
}

void PrintSolutions(double *solutions) {
    if (IsZero(solutions[0])) {
        std::cout << "The equation has no solutions" << std::endl;
    }
    else if (IsZero(solutions[0] - 1)) {
        std::cout << "There is one solution of the equation:" << std::endl << "x = " << solutions[1] << std::endl;
    }
    else {
        std::cout << "There are two solutions of the equation:" << std::endl << "x1 = " << solutions[1] << std::endl << "x2 = " << solutions[2] << std::endl;
    }
}


Tester::Tester() : failed_tests(0) {
    std::cout << "Begin tests" << std::endl << std::endl;
}

void Tester::test_all() {
    test_is_zero();
    test_discriminant();
    test_identical_solution();
    test_linear_solution();
    test_quadratic_solution();
    print_test_result();
}

void Tester::test_is_zero() {
    int count = 8;
    double params[count] = {0, 1e-9, 15, 100500, -1e-9, -15, -100500};
    bool answers[count] = {0, 0, 1, 1, 0, 1, 1};
    std::cout << "Tests IsZero():" << std::endl;
    for (int i = 0; i < count; ++i) {
        if (IsZero(params[i]) == answers[i]) {
            ++failed_tests;
            std::cout << "[ERR] ";
        } 
        else {
            std::cout << "[OK ] ";
        }
        std::cout << params[i] << std::endl;
    }
    std::cout << std::endl;
}

void Tester::test_discriminant() {
    int count = 3;
    double params[count][3] = {{1, 2, 3}, {0, 0, 0}, {-100.8, 20.5, 35.2}};
    double answers[count] = {-8.0, 0, 14612.89};
    std::cout << "Tests Discriminant():" << std::endl;
    for (int i = 0; i < count; ++i) {
        if (!IsZero(Discriminant(params[i]) - answers[i])) {
            ++failed_tests;
            std::cout << "[ERR] ";
        } 
        else {
            std::cout << "[OK ] ";
        }
        std::cout << params[i][0] << " " << params[i][1] << " " << params[i][2] << std::endl;
    }
    std::cout << std::endl;
}

void Tester::test_identical_solution() {
    int count = 2;
    double params[count] = {0, 5};
    double answers[count] = {1, 0};
    double solutions[3];
    std::cout << "Tests IdenticalSolution():" << std::endl;
    for (int i = 0; i < count; ++i) {
        IdenticalSolution(solutions, params[i]);
        if (!IsZero(solutions[0] - answers[i])) {
            ++failed_tests;
            std::cout << "[ERR] ";
        } 
        else {
            std::cout << "[OK ] ";
        }
        std::cout << params[i] << std::endl;
    }
    std::cout << std::endl;
}

void Tester::test_linear_solution() {
    int count = 2;
    double params[count][3] = {{0, 10, -4}, {0, -100.68, 0}};
    double answers[count] = {0.4, 0};
    double solutions[3];
    std::cout << "Tests LinearSolution():" << std::endl;
    for (int i = 0; i < count; ++i) {
        LinearSolution(solutions, params[i]);
        if (!IsZero(solutions[1] - answers[i])) {
            ++failed_tests;
            std::cout << "[ERR] ";
        } 
        else {
            std::cout << "[OK ] ";
        }
        std::cout << params[i][1] << " " << params[i][2] << std::endl;
    }
    std::cout << std::endl;
}

void Tester::test_quadratic_solution() {
    int count = 3;
    double params[count][3] = {{1, -4, 4}, {1, 2, 3}, {1, -84.5, -1550}};
    double answers[count][3] = {{1, 2, 0}, {0, 0, 0}, {2, 100, -15.5}};
    double solutions[3];
    std::cout << "Tests QuadraticSolution():" << std::endl;
    QuadraticSolution(solutions, params[0]);
    if (!IsZero(solutions[0] - answers[0][0]) || !IsZero(solutions[1] - answers[0][1])) {
        ++failed_tests;
        std::cout << "[ERR] ";
    } 
    else {
        std::cout << "[OK ] ";
    }
    std::cout << params[0][0] << " " << params[0][1] << " " << params[0][2] << std::endl;

    QuadraticSolution(solutions, params[1]);
    if (!IsZero(solutions[0] - answers[1][0])) {
        ++failed_tests;
        std::cout << "[ERR] ";
    } 
    else {
        std::cout << "[OK ] ";
    }
    std::cout << params[1][0] << " " << params[1][1] << " " << params[1][2] << std::endl;

    QuadraticSolution(solutions, params[2]);
    if (!IsZero(solutions[0] - answers[2][0]) || !IsZero(solutions[1] - answers[2][1]) || !IsZero(solutions[2] - answers[2][2])) {
        ++failed_tests;
        std::cout << "[ERR] ";
    } 
    else {
        std::cout << "[OK ] ";
    }
    std::cout << params[2][0] << " " << params[2][1] << " " << params[2][2] << std::endl << std::endl;
}

void Tester::print_test_result() {
    std::cout << failed_tests << " tests failed" << std::endl;
}