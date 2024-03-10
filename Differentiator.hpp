#ifndef DIFFERENTIATOR_HPP_
#define DIFFERENTIATOR_HPP_

#include <cmath>
#include "AAD22.hpp"

namespace adaai::solution {

    enum class DiffMethod:int {
        Stencil3,
        Stencil3Extra,
        Stencil5,
        Stencil5Extra,
        FwdAAD
    };

    enum class WhichD:int {
        x, // dF/dx
        y, // dF/dy
        xx, // d^{2} F/dx^{2}
        yy, // d^{2} F/dy^{2}
        xy // d^{2} F/dydx
    }

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
                return (F(x, y - 2*h) - 8*F(x, y - h) + 8*f(x, y + h) - F(x, y + 2*h))/(12 * h);
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
            return (16*d_n - d3) / 15;

        } else if constexpr (M == DiffMethod::FwdAAD) {
            AAD22 x = AAD22::x(x);
            AAD22 y = AAD22::y(y);
            AAD22 res = F(x, y); // F -- callable in this case
        }
    } // Differentiator<WhichD::x, DiffMethod::Stencil3>(F, x, y)





    // Callable AAD22(AAD22 const&, AAD22 const& )
    class AAD22 {
    private:
        double m_val; // value of func f or arg
        double m_d1[2]; // df/dx, df/dy в той же точке (x,y), где было вычислено m_val
        double m_d2[3]; // d^{2} f/dx^{2}, d^{2} f/dy^{2}, d^{2} f/dxdy в той же точке  

    // constructors
    public:
        AAD22() = delete; // make no sense
        // copy constructor можно оставить
        // constructor from a const
        constexpr AAD22(double c)  :  m_val = 0,
                            m_d1 = {0, 0},
                            m_d2 = {0, 0, 0} {}

    private:
        constexpr AAD22(int i, double v)  :// i = 0 for x, i = 1 for y
                                m_val = v,
                                m_d1{(i == 0)? 1.0 : 0.0, (i == 0)? 0.0 : 1.0},
                                m_d2{0, 0, 0} {}
    public:
        constexpr static AAD22 x(double v) {
            return AAD22(0, v);
        }
        constexpr static AAD22 y(double v) {
            return AAD22(1, v);
        }
        // operator overloading
        AAD22& operator +(AAD22 const& right) { // ну тут не ссылку возвращать надо
            AAD22 res = *this;
            res.m_val += right.m_val;
            res.m_d1[0] += right.m_d1[0];
            res.m_d1[1] += right.m_d1[1];
            res.m_d2[0] += right.m_d2[0];
            res.m_d2[1] += right.m_d2[1];
            res.m_d2[2] += right.m_d2[2];

            return res;
        }
        // implement    unary '+', '-';
        //              binary '+', '+=', '-', '-=', '*', '*=', '/', '/='
        //              elementaty functions: sin, cos, exp

        // implement accessors for m_val, m_d1, m_d2

        // make test:)
    }
} // namespace adaai::solution

#endif