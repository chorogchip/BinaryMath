#pragma once
#include<iostream>
#include<cstring>

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

private:
    void carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus) const;
    void carry_lookahead_add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size) const;
    void karastuba_multiply(const bool a[sz], const bool b[sz], bool s[sz], int size) const;
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
    carry_lookahead_add(data_, arr, data_, false);
    return *this;
}
template<int sz>
Integer<sz>& Integer<sz>::operator--() {
    char arr[sz] = { 1, 0, };
    carry_lookahead_add(data_, arr, data_, true);
    return *this;
}
template<int sz>
Integer<sz> Integer<sz>::operator++(int) const {
    Integer<sz> ret(data_);
    char arr[sz] = { 1, 0, };
    carry_lookahead_add(data_, arr, data_, false);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator--(int) const {
    Integer<sz> ret(data_);
    char arr[sz] = { 1, 0, };
    carry_lookahead_add(data_, arr, data_, true);
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
    carry_lookahead_add(data_, arr, data_, false);
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
    carry_lookahead_add(data_, itg.data_, ret.data_, false);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator-(const Integer<sz>& itg) const {
    Integer<sz> ret;
    carry_lookahead_add(data_, itg.data_, ret.data_, true);
    return ret;
}

template<int sz>
Integer<sz> Integer<sz>::operator*(const Integer<sz>& itg) const {
    Integer<sz> ret;
    karastuba_multiply(data_, itg.data_, ret.data_, sz);
    return ret;
}

template<int sz>
Integer<sz>& Integer<sz>::operator+=(const Integer<sz>& itg) {
    carry_lookahead_add(data_, itg.data_, data_, false);
    return *this;
}
template<int sz>
Integer<sz>& Integer<sz>::operator-=(const Integer<sz>& itg) {
    carry_lookahead_add(data_, itg.data_, data_, true);
    return *this;
}


template<int sz>
void Integer<sz>::carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus) const {
    // carry-lookahead adder
    // reason for using carry-lookahead adder even if this cannot run parallelly :
    // i think this way will be more close to real-used method.

    bool b_[sz], p[sz], g[sz], c[sz];
    if (is_minus) for (int i = 0; i < sz; ++i) b_[i] = !b[i];
    else for (int i = 0; i < sz; ++i) b_[i] = b[i];
    
    for (int i = 0; i < sz; ++i) p[i] = a[i] != b_[i];  // pi = ai ^ bi
    for (int i = 0; i < sz; ++i) g[i] = a[i] && b_[i];  // gi = a6 & bi

    s[0] = p[0] != is_minus;  // s0 = p0 ^ c0
    for (int i = 1; i < sz; ++i) {  // s1 ~ s(sz-1)

        // s3 = p3 ^ c2
        // c2 = g2 + v2
        // v2 = (p2 * g1) + (p2 * p1 * g0) + (p2 * p1 * p0 * minus)

        c[i] = g[i-1];  // ci+1 = gi + v2
        for (int j = i-2; j >= 0; --j) {
            bool pipigi = g[j];
            for (int k = i-1; k > j; --k) {
                pipigi = pipigi && p[k];
            }
            c[i] = c[i] || pipigi;
        }
        bool pipim = is_minus;
        for (int k = i-1; k >= 0; --k) {
            pipim = pipim && p[k];
        }
        c[i] = c[i] || pipim;

        s[i] = p[i] != c[i];  // si = pi ^ ci
    }
    count_plus++;
    return;
}

template<int sz>
void Integer<sz>::carry_lookahead_add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size) const {
    size = std::min(size + 1, sz);
    bool b_[sz], p[sz], g[sz], c[sz];
    if (is_minus) for (int i = 0; i < sz; ++i) b_[i] = !b[i];
    else for (int i = 0; i < sz; ++i) b_[i] = b[i];

    for (int i = 0; i < size; ++i) p[i] = a[i] != b_[i];  // pi = ai ^ bi
    for (int i = 0; i < size; ++i) g[i] = a[i] && b_[i];  // gi = a6 & bi

    s[0] = p[0] != is_minus;  // s0 = p0 ^ c0
    for (int i = 1; i < size; ++i) {  // s1 ~ s(sz-1)

        c[i] = g[i-1];  // ci+1 = gi + v2
        for (int j = i-2; j >= 0; --j) {
            bool pipigi = g[j];
            for (int k = i-1; k > j; --k) {
                pipigi = pipigi && p[k];
            }
            c[i] = c[i] || pipigi;
        }
        bool pipim = is_minus;
        for (int k = i-1; k >= 0; --k) {
            pipim = pipim && p[k];
        }
        c[i] = c[i] || pipim;

        s[i] = p[i] != c[i];  // si = pi ^ ci
    }
    count_plus++;
    return;
}

template<int sz>
void Integer<sz>::karastuba_multiply(const bool a[sz], const bool b[sz], bool s[sz], int size) const {
    if (size == 1) {
        s[0] = a[0] && b[0];
        return;
    }
    const int hsz0 = size >> 1;
    const int hsz1 = size - hsz0;
    bool c1[sz], c0[sz], d1[sz], d0[sz];
    int i;
    for (i = 0; i < hsz0; ++i) c0[i] = a[i];
    for (; i < size; ++i) c1[i-hsz0] = a[i];
    for (i = 0; i < hsz0; ++i) d0[i] = b[i];
    for (; i < size; ++i) d1[i-hsz0] = b[i];

    bool r0[sz], r1[sz], r2[sz];
    karastuba_multiply(c1, d1, r2, hsz1);
    karastuba_multiply(c0, d0, r1, hsz0);
    carry_lookahead_add_size(c1, c0, c0, true, hsz0);
    carry_lookahead_add_size(d0, d1, d1, true, hsz0);
    karastuba_multiply(c0, d1, r0, hsz1);

    carry_lookahead_add_size(r1, r0, s, false, hsz1);
    carry_lookahead_add_size(s, r1, s, false, hsz1);
    for (int i = 0; i < hsz1; ++i) s[hsz0+i] = s[i];
    carry_lookahead_add_size(s, r1, s, false, size);

    if (size == sz) count_mult++;
    return;
}

}
