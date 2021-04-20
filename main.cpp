#include <iostream>
#include <cstdlib>

#include "vector_functions.h"

double f(vec x) {

}

vector<double> runGradient(const vec& x) {

}

double normal(const vec& x) {
    return sqrt(x * x);
}

pair<vector<double>, double> gradientDrop(double eps) {
    vector<double> x;
    vector<double> grad;
    double alpha = 1.0;
    while (normal(grad = runGradient(x)) > eps) {
        vector<double> y = x - alpha * grad;
    }
    return make_pair(x, f(x));
}

int main() {
    return 0;
}
