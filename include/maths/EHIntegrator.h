#pragma once

namespace adaai::solution {
    ///Pointer to the function, which specifies how f(t_0, y(t_0), y'(t_0)) will be calculated in the equation: y'' = f(t, y, y')
    ///@param y - vector y(t_0)
    ///@param y_prime - vector y'(t_0)
    ///@param f - will contain vector f(t_0, y(t_0), y'(t_0))
    ///@param params - additional parameters used for calculation
    typedef void (*Equation)(double t_0, const double *y, const double y_prime, double *f, void *params);

    class EHIntegrator {
    public:
        EHIntegrator(Equation equation, int n, void *params);

        ~EHIntegrator();

        ///@brief calculates y(t_0 + h) and y'(t_0 + h), where y(t_0) = y_0 and y'(t_0) = y_prime_0
        void integrate(double *y_0, double *y_prime_0, double t_0, double h);

    };
}