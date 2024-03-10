#ifndef AAD22_HPP_
#define AAD22_HPP_

enum class WhichD:int {
        x, // dF/dx
        y, // dF/dy
        xx, // d^{2} F/dx^{2}
        yy, // d^{2} F/dy^{2}
        xy // d^{2} F/dydx
    }


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
        constexpr AAD22(double c)  :  m_val(0),
                            m_d1{0, 0},
                            m_d2{0, 0, 0} {};

    private:
        constexpr AAD22(int i, double v)  :// i = 0 for x, i = 1 for y
                                m_val(v),
                                m_d1{(i == 0)? 1.0 : 0.0, (i == 0)? 0.0 : 1.0},
                                m_d2{0, 0, 0} {};
    public:
        constexpr static AAD22 x(double v) {
            return AAD22(0, v);
        }
        constexpr static AAD22 y(double v) {
            return AAD22(1, v);
        }
        // operator overloading
        // implement    unary '+', '-';
        //              binary '+', '+=', '-', '-=', '*', '*=', '/', '/='
        //              elementaty functions: sin, cos, exp
        AAD22 operator +(AAD22 const& right);

        AAD22 operator +(double const &c) const;

        AAD22 operator *(AAD22 const &r) const;

        AAD22 operator *(double const&n) const;

        AAD22 derivative(WhichD type);
 
    };

    AAD22 operator*(double const&n, AAD22 const&val);

    AAD22 operator+(double const&n, AAD22 const&val);


    AAD22 sin(AAD22 const &val);

    AAD22 cos(AAD22 const &val);

    AAD22 exp(AAD22 const &val);
    

#endif