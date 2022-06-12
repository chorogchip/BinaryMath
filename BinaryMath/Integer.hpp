#pragma once
#include<iostream>
#include<cstring>
#include"Algorithms.hpp"

namespace bm{

template<int sz>
class Integer {

private:
    bool data_[sz];

    static int count_plus;
    static int count_mult;
    static int count_div;

public:
    Integer();
    Integer(int data);
    Integer(const Integer<sz>& itg);
    Integer<sz>& operator=(const Integer<sz>& itg);
    ~Integer();

    static int get_count_plus();
    static int get_count_mult();
    static int get_count_div();
    
    Integer<sz> operator~() const;
    Integer<sz>& operator++();
    Integer<sz>& operator--();
    Integer<sz> operator++(int) const;
    Integer<sz> operator--(int) const;
    Integer<sz> operator+() const;
    Integer<sz> operator-() const;
    operator int() const;
    bool operator==(const Integer<sz>& itg) const;
    bool operator!=(const Integer<sz>& itg) const;
    /*bool operator<(const Integer<sz>& itg) const;
    bool operator>(const Integer<sz>& itg) const;
    bool operator<=(const Integer<sz>& itg) const;
    bool operator>=(const Integer<sz>& itg) const;*/
    Integer<sz> operator+(const Integer<sz>& itg) const;
    Integer<sz> operator-(const Integer<sz>& itg) const;
    Integer<sz> operator*(const Integer<sz>& itg) const;
    /*Integer<sz> operator/(const Integer<sz>& itg) const;
    Integer<sz> operator%(const Integer<sz>& itg) const;
    Integer<sz> operator<<(const Integer<sz>& itg) const;
    Integer<sz> operator>>(const Integer<sz>& itg) const;
    Integer<sz> operator&(const Integer<sz>& itg) const;
    Integer<sz> operator^(const Integer<sz>& itg) const;
    Integer<sz> operator|(const Integer<sz>& itg) const;*/
    Integer<sz>& operator+=(const Integer<sz>& itg);
    Integer<sz>& operator-=(const Integer<sz>& itg);
    /*Integer<sz>& operator*=(const Integer<sz>& itg);
    Integer<sz>& operator/=(const Integer<sz>& itg);
    Integer<sz>& operator%=(const Integer<sz>& itg);
    Integer<sz>& operator<<=(const Integer<sz>& itg);
    Integer<sz>& operator>>=(const Integer<sz>& itg);
    Integer<sz>& operator&=(const Integer<sz>& itg);
    Integer<sz>& operator^=(const Integer<sz>& itg);
    Integer<sz>& operator|=(const Integer<sz>& itg);
    friend std::ostream& operator<<(td::ostream &out, const Integer<sz> &itg);*/

};

template<int sz>
int Integer<sz>::count_plus = 0;
template<int sz>
int Integer<sz>::count_mult = 0;
template<int sz>
int Integer<sz>::count_div = 0;

template<int sz>
Integer<sz>::Integer() {
    for (int i = 0; i < sz; ++i)
        data_[i] = false;
}
template<int sz>
Integer<sz>::Integer(int data) {
    for (int i = 0; i < sz; ++i)
        data_[i] = (bool)(data & (1<<i));
}
template<int sz>
Integer<sz>::Integer(const Integer& itg) {
    for (int i = 0; i < sz; ++i)
        data_[i] = itg.data_[i];
}
template<int sz>
Integer<sz>& Integer<sz>::operator=(const Integer& itg) {
    for (int i = 0; i < sz; ++i)
        data_[i] = itg.data_[i];
    return *this;
}
template<int sz>
Integer<sz>::~Integer() {}


template<int sz>
int Integer<sz>::get_count_plus() {
    return count_plus;
}
template<int sz>
int Integer<sz>::get_count_mult() {
    return count_mult;
}
template<int sz>
int Integer<sz>::get_count_div() {
    return count_div;
}


template<int sz>
Integer<sz> Integer<sz>::operator~() const {
    Integer<sz> ret;
    for (int i = 0; i < sz; ++i)
        ret.data_[i] = !data_[i];
    return ret;
}
template<int sz>
Integer<sz>& Integer<sz>::operator++() {
    char arr[sz] = { 1, 0, };
    Algorithms<sz>::add(data_, arr, data_, false);
    return *this;
}
template<int sz>
Integer<sz>& Integer<sz>::operator--() {
    char arr[sz] = { 1, 0, };
    Algorithms<sz>::add(data_, arr, data_, true);
    return *this;
}
template<int sz>
Integer<sz> Integer<sz>::operator++(int) const {
    Integer<sz> ret(data_);
    char arr[sz] = { 1, 0, };
    Algorithms<sz>::add(data_, arr, data_, false);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator--(int) const {
    Integer<sz> ret(data_);
    char arr[sz] = { 1, 0, };
    Algorithms<sz>::add(data_, arr, data_, true);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator+() const {
    Integer<sz> ret(data_);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator-() const {
    Integer<sz> ret(~*this);
    char arr[sz] = { 1, 0, };
    Algorithms<sz>::add(data_, arr, data_, false);
    return ret;
}
template<int sz>
Integer<sz>::operator int() const {
    int ret = 0;
    int msz = std::max(sz, (int)sizeof(int)*8);
    for (int i = 0; i < msz; ++i) {
        ret |= (int)data_[i] << i;
    }
    return ret;
}
template<int sz>
bool Integer<sz>::operator==(const Integer<sz>& itg) const {
    for (int i = 0; i < sz; ++i)
        if (data_[i] != itg.data_[i]) return false;
    return true;
}
template<int sz>
bool Integer<sz>::operator!=(const Integer<sz>& itg) const {
    return !(*this == itg);
}/*
template<int sz>
bool Integer<sz>::operator<(const Integer<sz>& itg) const {}
template<int sz>
bool Integer<sz>::operator>(const Integer<sz>& itg) const {}
template<int sz>
bool Integer<sz>::operator<=(const Integer<sz>& itg) const {}
template<int sz>
bool Integer<sz>::operator>=(const Integer<sz>& itg) const {}*/

template<int sz>
Integer<sz> Integer<sz>::operator+(const Integer<sz>& itg) const {
    Integer<sz> ret;
    Algorithms<sz>::add(data_, itg.data_, ret.data_, false);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator-(const Integer<sz>& itg) const {
    Integer<sz> ret;
    Algorithms<sz>::add(data_, itg.data_, ret.data_, true);
    return ret;
}

template<int sz>
Integer<sz> Integer<sz>::operator*(const Integer<sz>& itg) const {
    Integer<sz> ret;
    Algorithms<sz>::mult(data_, itg.data_, ret.data_, sz);
    return ret;
}

template<int sz>
Integer<sz>& Integer<sz>::operator+=(const Integer<sz>& itg) {
    Algorithms<sz>::dd(data_, itg.data_, data_, false);
    return *this;
}
template<int sz>
Integer<sz>& Integer<sz>::operator-=(const Integer<sz>& itg) {
    Algorithms<sz>::add(data_, itg.data_, data_, true);
    return *this;
}

}
