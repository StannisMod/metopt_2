#include <functional>
#include <cmath>
#include "dichotomy_method.h"
#include "golden_ratio_method.h"
#include "fibonacci_method.h"
#include "parabola_method.h"
#include "brent_method.h"
#include "steps_printer.h"
#include "steepest_descent.h"


int main() {
    quadratic_function func(2, 0.5, 0.5, 1);
    auto result = steepest_gradient_descent(func, 1e-5, {0.5, 1});
    cout << result.point.first << " " << result.point.second;
    return 0;
}
