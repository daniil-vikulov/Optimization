#include "AAD22.hpp"

#include <cmath>


AAD22 AAD22::operator +(AAD22 const &r) const {
    AAD22 res = *this;
    res.m_val += r.m_val;
    res.m_d1[0] += r.m_d1[0];
    res.m_d1[1] += r.m_d1[1];
    res.m_d2[0] += r.m_d2[0];
    res.m_d2[1] += r.m_d2[2];
    res.m_d2[2] += r.m_d2[2];
    return res;
}


