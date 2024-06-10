#pragma once
#include <vector>


/// NOTE: C-like interface for full GSL-compatibility in terms of arguments and appearance:)

namespace adaai::solution {
    ///Pointer to the function, which specifies how f(t_0, y(t_0), y'(t_0)) will be calculated in the equation: y'' = f(t, y, y')
    ///@param t0
    ///@param y - vector y(t_0)
    ///@param yPrime - vector y'(t_0)
    ///@param params - additional parameters used for calculation
    ///@return f - will contain vector f(t_0, y(t_0), y'(t_0))
    typedef std::vector<double> (*Equation)(double t0, std::vector<double> &y, const std::vector<double> &yPrime,
                                            void *params);

    class EHIntegrator {
        ///@brief RHS of the ODE: (t, y(t), y'(t))
        Equation _equation;

        ///@brief parameters of the equation
        void *_parameters{};

        ///@brief number of interpolation nodes (t_0, t_1 .. t_{k-1}, t_k = t_0 + h)
        constexpr int K = 6;

        ///@brief dimension of vectors to operate with. Say, y, y', y''. Correspondingly, f: R^{2*n+1} - > R^n
        int _dimension;

        ///@brief [nodeIndex][dimension]
        std::vector<std::vector<double> > _yInNodes;

        ///@brief [nodeIndex][dimension]
        std::vector<std::vector<double> > _yPrimeInNodes;

        ///@brief [nodeIndex][dimension]
        std::vector<std::vector<double> > _b;

        ///@brief double[nodeIndex][order][dimension], containing devided difference
        std::vector<std::vector<std::vector<double> > > _dd;

    public:
        EHIntegrator(Equation equation, int dimension, void *parameters = nullptr);

        ~EHIntegrator() = default;

        ///@brief calculates y(t_0 + h) and y'(t_0 + h) where y(t_0) = y_0 and y'(t_0) = y_prime_0
        ///@details fills vectors with desired data
        void integrate(std::vector<double> &y0, std::vector<double> &yPrime0, double t0, double h);

    private:
        ///@brief calculates approximation for y(t_0 + h), y'(t_0 + h), y''(t_0 + h)
        ///@details Fills vectors with desired data. Evoke multiple times with the same paramters to increase accuracy
        void step(double t0, double h);

        ///@brief fills _b array with coefficients, calculated with _dd
        void fillB(double t0);

        ///@brief fills _dd array with divided difference
        void fillDD(double t0);
    };
}
