#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

float square_root(float y, float t) {
    return sqrt(y);
}

float integrated_square_root(float t) {
    return (t*t/4) + t + 1; // (t / 2 + 1) ^ 2 
}

void analytic_sol(float y_0, float T, float delta_t, float (*f_func) (float)) {
    std::ofstream AnalyticSol("analytic_res.dat");
    AnalyticSol << to_string(0.0f) + "\t" + to_string(y_0) + "\n";
    for (float t=0; t <= T; t+=delta_t) {
        AnalyticSol << to_string(t) + "\t" + to_string(integrated_square_root(t)) + "\n";
    }

    AnalyticSol.close();
}

void solve_euler(float y_0, float T, float delta_t, float (*f_func) (float, float)) {
    std::ofstream EulerResFile("euler_res.dat");
    float temp_y = y_0;
    EulerResFile << to_string(0.0f) + "\t" + to_string(temp_y) + "\n";
    for (float t=0; t <= T; t+=delta_t) {
        temp_y += delta_t * (f_func(temp_y, t));

        EulerResFile << to_string(t+delta_t) + "\t" + to_string(temp_y) + "\n";
    }
    
    EulerResFile.close();
}

void runge_kutta_scheme(float y_0, float T, float delta_t, float (*f_func) (float, float)) {
    std::ofstream RungeKuttaFile("runge_kutta.dat");
    float temp_y = y_0;
    RungeKuttaFile << to_string(0.0f) + "\t" + to_string(temp_y) + "\n";
    for (float t=0; t<=T; t+=delta_t) {
        float k1 = f_func(temp_y, t);
        float k2 = f_func(temp_y + (k1*delta_t), t);
        temp_y += 0.5 * delta_t * (k1 + k2);

        RungeKuttaFile << to_string(t+delta_t) + "\t" + to_string(temp_y) + "\n";
    }

    RungeKuttaFile.close();
}

int main(void) {
    float y_0, T, delta_t;
    std::cout << "Enter y_0: " << std::endl;
    cin >> y_0;
    std::cout << "Enter T: " << std::endl;
    cin >> T;
    std::cout << "Enter delta_t: " << std::endl;
    cin >> delta_t;

    solve_euler(y_0, T, delta_t, square_root);
    runge_kutta_scheme(y_0, T, delta_t, square_root);
    analytic_sol(y_0, T, delta_t, integrated_square_root);

    return 0;
}