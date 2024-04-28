#pragma once

namespace adaai::solution {
    typedef int (*Equation)(double t, const double *y, double *dydt, void *params);

    class EHIntegrator {
    public:
        EHIntegrator(Equation equation, int n, void *params);

        ~EHIntegrator();

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