#include "AAD22.hpp"

#include <cmath>

//all + operators
AAD22 AAD22::operator +(AAD22 const& right) const {
    AAD22 res = *this;
    res.m_val += right.m_val;
    res.m_d1[0] += right.m_d1[0];
    res.m_d1[1] += right.m_d1[1];
    res.m_d2[0] += right.m_d2[0];
    res.m_d2[1] += right.m_d2[1];
    res.m_d2[2] += right.m_d2[2];
    return res;
}

AAD22 AAD22::operator +(double const& right) const {
    return *this + AAD22(right);
}

AAD22 operator +(double const& right, AAD22 const& value) {
    return AAD22(right) + value;
}

AAD22 operator +(AAD22 const& value, double const& right) {
    return value + AAD22(right);
}
//TODO: add +=


//all - operators
AAD22 AAD22::operator -(AAD22 const& right) const {
    AAD22 res = *this;
    res.m_val -= right.m_val;
    res.m_d1[0] -= right.m_d1[0];
    res.m_d1[1] -= right.m_d1[1];
    res.m_d2[0] -= right.m_d2[0];
    res.m_d2[1] -= right.m_d2[1];
    res.m_d2[2] -= right.m_d2[2];
    return res;
}

AAD22 AAD22::operator -(double const& right) const {
    return *this - AAD22(right);
}

AAD22 operator -(double const& right, AAD22 const& value) {
    return AAD22(right) - value;
}

AAD22 operator -(AAD22 const& value, double const& right) {
    return value - AAD22(right);
}
// TODO: add -=


//all * operators
AAD22 AAD22::operator *(AAD22 const& right) const {
    AAD22 res = *this;
    res.m_val = right.m_val * res.m_val;
    res.m_d1[0] = right.m_d1[0] * this->m_val + res.m_d1[0] * right.m_val;
    res.m_d1[1] = right.m_d1[1] * this->m_val + res.m_d1[1] * right.m_val;
    res.m_d2[0] = right.m_d2[0] * this->m_val + res.m_d2[0] * right.m_val + 2 * this->m_d1[0] * right.m_d1[0];
    res.m_d2[1] = right.m_d2[1] * this->m_val + res.m_d2[1] * right.m_val + 2 * this->m_d1[1] * right.m_d1[1];
    res.m_d2[2] = right.m_d2[2] * this->m_val + res.m_d2[2] * right.m_val + this->m_d1[1] * right.m_d1[0] + this->m_d1[0] * right.m_d1[1];
    return res;
}

AAD22 AAD22::operator *(double const& right) const{
   return *this * AAD22(right); 
}

AAD22 operator *(double const& right, AAD22 const& value) {
    return AAD22(right) * value;
}

AAD22 operator *(AAD22 const& value, double const& right) {
    return value * AAD22(right);
}
//TODO: add *=


//all / operators
AAD22 AAD22::operator /(AAD22 const& right) const {
    AAD22 res = *this;
    res.m_val = right.m_val / res.m_val;
    res.m_d1[0] = -1*(right.m_d1[0] * this->m_val - res.m_d1[0] * right.m_val) / (right.m_val * right.m_val);
    res.m_d1[1] = -1*(right.m_d1[1] * this->m_val - res.m_d1[1] * right.m_val) / (right.m_val * right.m_val);
    res.m_d2[0] = (2*this->m_d1[0]*right.m_d1[0] - this->m_d2[0]* right.m_val * right.m_val -
                   this->m_val * (2*right.m_d1[0] * right.m_d1[0] * right.m_val * right.m_d2[0])) /
                  ( -1 * right.m_val * right.m_val * right.m_val);
    res.m_d2[1] =  (2*this->m_d1[1]*right.m_d1[1] - this->m_d2[1]* right.m_val * right.m_val -
                   this->m_val * (2*right.m_d1[1] * right.m_d1[1] * right.m_val * right.m_d2[1])) /
                   ( -1 * right.m_val * right.m_val * right.m_val);

    res.m_d2[2] = (-1*this->m_d1[0]*right.m_d1[1]*right.m_val - this->m_d1[1]*right.m_d1[0]*right.m_val +
                   this->m_d2[2]*right.m_val*right.m_val - this->m_val*right.m_d2[2]*right.m_val + 
                   2*this->m_val*right.m_d1[1]*right.m_d1[0]) / (right.m_val * right.m_val * right.m_val);
    return res;
}

AAD22 AAD22::operator /(double const& right) const{
   return *this / AAD22(right); 
}

AAD22 operator /(double const& right, AAD22 const& value) { 
    return AAD22(right) / value;
}

AAD22 operator /(AAD22 const& value, double const& right) {
    return value / AAD22(right);
}
//TODO: add /= 

