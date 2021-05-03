#include <functional>
#include <cmath>
#include "dichotomy_method.h"
#include "golden_ratio_method.h"
#include "fibonacci_method.h"
#include "parabola_method.h"
#include "gradient_descent.h"
#include "conjugate_gradients.h"
#include "brent_method.h"
#include "steepest_descent.h"
#include "diag_form.h"
#include "utils.h"


int main() {
    quadratic_function func(3, 2, 2, 5);
    vector<double> p = {-28, 32};
    auto res = conjugate_gradients(&func, 1e-5, p);
    for (auto elem : res.iterations[0]){
        cout << elem << ", ";
    }
    cout << endl;
    for (auto elem : res.iterations[1]){
        cout << elem << ", ";
    }
    return 0;
}
