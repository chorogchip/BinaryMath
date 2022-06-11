#pragma once
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

    int getInt() const;
    static int get_count_plus();
    static int get_count_mult();
    static int get_count_div();

    Integer<sz> operator+(const Integer<sz>& itg);
    Integer<sz> operator-(const Integer<sz>& itg);
    Integer<sz>& operator+=(const Integer<sz>& itg);
    Integer<sz>& operator-=(const Integer<sz>& itg);

private:
    void carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus);
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
int Integer<sz>::getInt() const {
    int ret = 0;
    for (int i = 0; i < sz; ++i) {
        ret |= (int)data_[i] << i;
    }
    return ret;
}
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
Integer<sz> Integer<sz>::operator+(const Integer<sz>& itg) {
    Integer<sz> ret;
    carry_lookahead_add(data_, itg.data_, ret.data_, false);
    return ret;
}
template<int sz>
Integer<sz> Integer<sz>::operator-(const Integer<sz>& itg) {
    Integer<sz> ret;
    carry_lookahead_add(data_, itg.data_, ret.data_, true);
    return ret;
}

template<int sz>
Integer<sz>& Integer<sz>::operator+=(const Integer<sz>& itg) {
    char s[sz];
    carry_lookahead_add(data_, itg.data_, s, false);
    memcpy(data_, s, sz);
    return *this;
}
template<int sz>
Integer<sz>& Integer<sz>::operator-=(const Integer<sz>& itg) {
    char s[sz];
    carry_lookahead_add(data_, itg.data_, s, true);
    memcpy(data_, s, sz);
    return *this;
}


template<int sz>
void Integer<sz>::carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus) {
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

}
