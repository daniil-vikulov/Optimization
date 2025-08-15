#ifndef DIFFERENTIATOR_HPP_
#define DIFFERENTIATOR_HPP_

#include <cmath>
#include "AAD22.hpp"


    enum class DiffMethod:int {
        Stencil3,
        Stencil3Extra,
        Stencil5,
        Stencil5Extra,
        FwdAAD
    };

   



    // for stencils:   если |x| < 1, то h = 1e-4
    //                 если |x| >= 1, то h = 1e-4 * |x|
    //                 same for |y|

    // stencil3 and stencil5 are trivial
    // extra я не распарсила пока


    // получает на вход callable-объект, x, y и возвращает значение производной
    template<WhichD W, DiffMethod M, typename Callable>
    double Differentiator(Callable const& F, double x, double y, double h_input = 1) {
        double h = 1e-4 * h_input;
        if (std::abs(x) >= 1) {
            h *= std::abs(x);
        }
        
        if constexpr (M == DiffMethod::Stencil3) {
            if constexpr (W == WhichD::x) {
                return (F(x + h, y) - F(x - h, y))/(2 * h);
            } else if constexpr (W == WhichD::y) {
                return (F(x, y + h) - F(x, y - h))/(2 * h);
            } else if constexpr (W == WhichD::xx) {
                return (F(x + h, y) - 2 * F(x, y) + F(x - h, y))/(h * h);
            } else if constexpr (W == WhichD::yy) {
                return (F(x, y + h) - 2 * F(x, y) + F(x, y - h))/(h * h);
            } else if constexpr (W == WhichD::xy) {
                return ((F(x + h, y + h)+ F(x - h, y - h)) - (F(x + h, y - h) + F(x - h, y + h))) / (4 * h * h);               
            }

        } else if constexpr (M == DiffMethod::Stencil3Extra) {
            //рекурсивно вызвать stencil3 
            double d3 = Differentiator<W, DiffMethod::Stencil3>(F, x, y);
            // n = 4
            double d_n = Differentiator<W, DiffMethod::Stencil3>(F, x, y, 0.25);
            return (16*d_n - d3) / 15;

        } else if constexpr (M == DiffMethod::Stencil5) {
            if constexpr (W == WhichD::x) {
                return (F(x - 2*h, y) - 8*F(x - h, y) + 8*F(x + h, y) - F(x + 2*h, y))/(12 * h);
            } else if constexpr (W == WhichD::y) {
                return (F(x, y - 2*h) - 8*F(x, y - h) + 8*F(x, y + h) - F(x, y + 2*h))/(12 * h);
            } else if constexpr (W == WhichD::xx) {
                return (-F(x -2*h, y) + 16 * F(x - h, y) -30 * F(x, y) + 16*F(x + h, y) - F(x + 2*h, y))/(12 * h * h);
            } else if constexpr (W == WhichD::yy) {
                return (-F(x, y - 2*h) + 16 * F(x, y - h) -30 * F(x, y) + 16*F(x, y + h) - F(x, y + 2*h))/(12 * h * h);               
            } else if constexpr (W == WhichD::xy) {
                return ((F(x + h, y + h) - F(x - h, y + h)) - F(x + h, y - h) + F(x - h, y - h)) / (4 * h * h);               
            }
        } else if constexpr (M == DiffMethod::Stencil5Extra) {
            // тут можно рекурсивно вызвать stencil5
            double d5 = Differentiator<W, DiffMethod::Stencil5>(F, x, y);
            // n = 4
            double d_n = Differentiator<W, DiffMethod::Stencil5>(F, x, y, 0.25);
            return (16*d_n - d5) / 15;

        } else if constexpr (M == DiffMethod::FwdAAD) {
            AAD22 X = AAD22::x(x);
            AAD22 Y = AAD22::y(y);
            AAD22 res = F(X, Y); // F -- callable in this case
            return res.derivative(W);
    } 
}

#endif