#ifndef METOPT_2_FUNCTIONS_H
#define METOPT_2_FUNCTIONS_H

#include <vector>

using namespace std;

typedef vector<double> vec;

class result {
public:
    const vec x;
    const double value;
    const vector<vec> iterations;

    result(vec& x, double value, vector<vec>& iterations) : x(x), value(value), iterations(iterations) {}
};

result make_result(vec& x, double value, vector<vec>& iterations) {
    return result(x, value, iterations);
}

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

ostream& operator<<(ostream& out, const vec& v) {
    //out << "(";
    for (int i = 0; i < v.size() - 1; i++) {
        out << v[i]; //<< ", ";
    }
    out << v[v.size() - 1];
    //out << ")" << endl;
    return out;
}

double f(vec& x) {

}

vec runGradient(const vec& x) {

}

double normal(const vec& x) {
    return sqrt(x * x);
}

// Methods' forward declarations

result gradientDrop(double eps);
result fastestDrop(double eps);
result conjugateGradients(double eps);

#endif //METOPT_2_FUNCTIONS_H
