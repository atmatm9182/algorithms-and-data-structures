#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

double random_range(double min, double max) {
    int r = rand();
    return (double)r / RAND_MAX * (max - min) + min;
}

double solve_function(double x) {
    return sin(x) + sin(2 * x) + sin(4 * x);
}

double solve_integral(double a, double b, double h, double count_above, double count_below) {
    return (b - a) * h * count_below / (count_above + count_below);
}

double solve(double a, double b, double h, double precision) {
    uint32_t count_above = 0;
    uint32_t count_below = 0;

    while (1) {
        uint32_t cab = count_above;
        uint32_t cbb = count_below;
        
        double x = random_range(a, b);
        double y = random_range(0, h);

        if (y > solve_function(x)) {
            count_above++;
        } else if (y < solve_function(x)) {
            count_below++;
        }

        double ib = solve_integral(a, b, h, cab, cbb);
        double ia = solve_integral(a, b, h, count_above, count_below);

        if (ia != 0 && ib != 0 && fabs((ia) - (ib)) <= precision) {
            return ia;
        }
    }

    assert(0 && "this should be unreachable");
}

int main() {
    srand(time(NULL));
    const int a = 0;
    const int b = 2 * M_PI;
    const int h = 3;
    const double precision = 0.1;

    double result = solve(a, b, h, precision);
    printf("%f\n", result);

    return 0;
}
