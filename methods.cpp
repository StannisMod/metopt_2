#include "functions.h"

result gradientDrop(const double eps) {
    vec x;
    vec grad;
    double alpha = 1.0;
    vec y = x;
    vector<vec> iterations;
    while (normal(grad = runGradient(x)) > eps) {
        while (true) {
            iterations.push_back(y);
            y = x - alpha * grad;
            if (f(y) < f(x)) {
                x = y;
                break;
            } else {
                alpha = alpha / 2;
            }
        }
    }
    return make_result(x, f(x), iterations);
}

result fastestDrop(double eps) {

}

result conjugateGradients(double eps) {

}
