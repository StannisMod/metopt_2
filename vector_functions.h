#ifndef METOPT_2_VECTOR_FUNCTIONS_H
#define METOPT_2_VECTOR_FUNCTIONS_H

#include <vector>

using namespace std;

typedef vector<double> vec;

vec operator*(double a, const vec& v) {
    vec result;
    for (double value : v) {
        result.push_back(a * value);
    }
    return result;
}

vec operator-(const vec& x, const vec& y) {
    if (x.size() != y.size()) {
        throw exception();
    }
    vec result;
    for (int i = 0; i < x.size(); i++) {
        result.push_back(x[i] - y[i]);
    }
    return result;
}

double operator*(const vec& x, const vec& y) {
    if (x.size() != y.size()) {
        throw exception();
    }
    double result = 0;
    for (int i = 0; i < x.size(); i++) {
        result += x[i] * y[i];
    }
    return result;
}

#endif //METOPT_2_VECTOR_FUNCTIONS_H
