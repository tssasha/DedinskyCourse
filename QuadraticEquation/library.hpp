#define EPSILON 1e-8

int PrintCoefficients(double *coefficients);

bool IsZero(double num);

double Discriminant(double *coefficients);

int IdenticalSolution(double *solutions, double coefficient);

int LinearSolution(double *solutions, double *coefficients);

int QuadraticSolution(double *solutions, double *coefficients);

void PrintSolutions(double *solutions);

class Tester {
private:
    int failed_tests;
public:
    Tester();
    void test_all ();
    void test_is_zero();
    void test_discriminant();
    void test_identical_solution();
    void test_linear_solution();
    void test_quadratic_solution();
    void print_test_result();
};

