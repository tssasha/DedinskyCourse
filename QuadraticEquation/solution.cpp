#include "library.hpp"
#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "debug") == 0) {
        Tester a = Tester();
        a.test_all();
    }
    else {
        double coefficients[3];
        PrintCoefficients(coefficients);
        double solutions[3]; //the first element is count of solutions, the next elements are solutions
        if (IsZero(coefficients[0]) && IsZero(coefficients[1])) {
            IdenticalSolution(solutions, coefficients[2]);
        }
        else if (IsZero(coefficients[0])) {
            LinearSolution(solutions, coefficients);
        }
        else {
            QuadraticSolution(solutions, coefficients);
        }
        PrintSolutions(solutions);
    }
    return 0;
}