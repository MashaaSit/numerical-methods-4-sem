#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

double f(double x, double y) {
    return (3 * pow(x, 2) * exp(-x) - (x + 1) * y) / x;
}

void adams_bashforth_fixed(double a, double b, double y0, int N, const string &filename) {
    ofstream file(filename);

    double y[7];
    double x[7];
    double f_vals[7];
    f_vals[0] = f(x[0], y[0]);

    double h = (b - a) / N;
    y[0] = y0;
    x[0] = a;

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    file << x[0] << "\t" << y[0] << "\n";


    for (int i = 1; i < 6; i++) {
        x[i] = x[i - 1] + h;
        double y_mid = y[i - 1] + h / 2 * f(x[i - 1], y[i - 1]);
        y[i] = y[i - 1] + h * f(x[i - 1] + h / 2, y_mid);
        file << x[i] << "\t" << y[i] << "\n";
    }

    while (true) {
        if (x[5] > b) {
            break;
        }

        y[6] = y[5] + h / 24 * (9 * f_vals[5] + 19 * f_vals[4] - 5 * f_vals[3] + f_vals[2]);
        x[6] = x[5] + h;
        f_vals[6] = f(x[6], y[6]);
        file << x[6] << "\t" << y[6] << "\n";
        for (int i = 0; i < 6; i++) {
            y[i] = y[i + 1];
            x[i] = x[i + 1];
            f_vals[i] = f_vals[i + 1];
        }
    }


    file.close();
}


void adams_bashforth(double a, double b, double y0, double eps, string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    const int max_steps = 7;
    double y[max_steps];
    double x[max_steps];
    double f_vals[max_steps];
    double h = (b - a) * eps;
    y[0] = y0;
    x[0] = a;
    f_vals[0] = f(x[0], y[0]);

    file << x[0] << "\t" << y[0] << "\t" << h << "\n";

    for (int i = 1; i < 6; i++) {
        x[i] = x[i - 1] + h;
        double y_mid = y[i - 1] + h / 2 * f_vals[i - 1];
        y[i] = y[i - 1] + h * f(x[i - 1] + h / 2, y_mid);
        f_vals[i] = f(x[i], y[i]);
        file << x[i] << "\t" << y[i] << "\t" << h << "\n";
    }

    while (x[5] < b) {
        double h_half = h / 2;

        double y_mid_1 = y[5] + h_half / 24 * (9 * f_vals[5] + 19 * f_vals[4] - 5 * f_vals[3] + f_vals[2]);
        double y_next_h_2 = y[5] + h_half / 24 * (
                                9 * f(x[5] + h_half, y_mid_1) + 19 * f_vals[5] - 5 * f_vals[4]+ f_vals[3]);
        double y_next_h = y[5] + h / 24 * (9 * f_vals[5] + 19 * f_vals[4] - 5 * f_vals[3] + f_vals[2]);

        double runge_error = fabs(y_next_h - y_next_h_2) / 15.0;

        if (runge_error < eps / 10) {
            y[6] = y_next_h;
            x[6] = x[5] + h;
            f_vals[6] = f(x[6], y[6]);
            file << x[6] << "\t" << y[6] << "\t" << h << "\n";
            h = min(h * 1.5, 0.1);

            for (int i = 0; i < 6; i++) {
                y[i] = y[i + 1];
                x[i] = x[i + 1];
                f_vals[i] = f_vals[i + 1];
            }
        } else if (runge_error < eps) {
            y[6] = y_next_h;
            x[6] = x[5] + h;
            f_vals[6] = f(x[6], y[6]);
            file << x[6] << "\t" << y[6] << "\t" << h << "\n";

            for (int i = 0; i < 6; i++) {
                y[i] = y[i + 1];
                x[i] = x[i + 1];
                f_vals[i] = f_vals[i + 1];
            }
        } else {
            h = max(h * 0.5, 1e-7);
        }
    }

    file.close();
}


int main() {
    double a = 1.0;
    double y0 = 1 / exp(1);
    double b = 5.0;
    adams_bashforth_fixed(a, b, y0, 10, "adams_fixed_10.txt");
    adams_bashforth_fixed(a, b, y0, 100, "adams_fixed_100.txt");

    double eps = 0.1;
    for (int i = 0; i < 7; i++) {
        ostringstream stream;
        stream << fixed << setprecision(8) << eps;
        string filename = "adams_" + stream.str() + ".txt";
        adams_bashforth(a, b, y0, eps, filename);
        eps *= 0.1;
    }


    return 0;
}
