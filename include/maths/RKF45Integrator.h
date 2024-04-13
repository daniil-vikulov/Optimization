#pragma once

namespace adaai::solution {
    typedef int (*Equation)(double t, const double *y, double *dydt, void *params);

    class RKF45Integrator {
    private:
        static constexpr double Tolerance = 1e-4;

        static constexpr double A[7] = {0.0, 0.0, 1.0 / 2.0, 1.0 / 2.0, 1.0, 2.0 / 3.0, 1.0 / 5.0};
        static constexpr double B[7][7] = {{0.0, 0.0,          0.0,         0.0,           0.0,          0.0,   0.0},
                                           {0.0, 0.0,          0.0,         0.0,           0.0,          0.0,   0.0},
                                           {0.0, 1.0 / 2.0,    0.0,         0.0,           0.0,          0.0,   0.0},
                                           {0.0, 1.0 / 4.0,    1.0 / 4.0,   0.0,           0.0,          0.0,   0.0},
                                           {0.0, 0.0,          -1.0,        2.0,           0.0,          0.0,   0.0},
                                           {0.0, 7.0 / 27.0,   10.0 / 27.0, 0.0,           1.0 / 27.0,   0.0,   0.0},
                                           {0.0, 28.0 / 625.0, -1.0 / 5.0,  546.0 / 625.0, 54.0 / 625.0, -378.0 /
                                                                                                         625.0, 0.0},};
        static constexpr double Gamma[7] = {0.0, 1.0 / 24.0, 0.0, 0.0, 5.0 / 48.0, 27.0 / 56, 125.0 / 336.0};
        static constexpr double Sigma[7] = {0.0, 118.0, 0.0, 2.0 / 3.0, 1.0 / 16.0, -27.0 / 56.0, -125.0 / 336.0};

        Equation _equation{};
        int _n{};
        void *_parameters{};

        double *k1{};
        double *k2{};
        double *k3{};
        double *k4{};
        double *k5{};
        double *k6{};
        double *buf{};

    public:
        RKF45Integrator(Equation equation, int n, void *params);

        ~RKF45Integrator();

        void integrate(double *y, double *tStart, double tEnd);

    private:
        ///@brief calculates y(t + h).
        ///@param t - point
        ///@param h - step. Will be filled with a suggested step
        ///@param y - initial state. Will be updated with y(t + h) in case the step was successful, otherwise data will not be changed
        ///@return true - step accepted, false - step rejected and step() function should be called again with an updated (smaller) h
        bool step(double t, double &h, double *y);
    };
}