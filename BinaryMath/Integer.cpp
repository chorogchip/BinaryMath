#include "Integer.h"

namespace bm {

int Integer::count_plus = 0;
int Integer::count_mult = 0;
int Integer::count_div = 0;

Integer::Integer(): data_(0) {}
Integer::Integer(int data): data_(data) {}
Integer::Integer(const Integer& i): data_(i.data_) {}
Integer& Integer::operator=(const Integer& i) { data_ = i.data_; return *this; }
Integer::~Integer() {}


int Integer::getInt() const {
    return data_;
}
int Integer::get_count_plus() {
    return count_plus;
}
int Integer::get_count_mult() {
    return count_mult;
}
int Integer::get_count_div() {
    return count_div;
}


Integer Integer::operator+(const Integer& i) {
    return Integer(carry_lookahead_add(data_, i.data_, false));
}
Integer Integer::operator-(const Integer& i) {
    return Integer(carry_lookahead_add(data_, i.data_, true));
}

Integer& Integer::operator+=(const Integer& i) {
    data_ = carry_lookahead_add(data_, i.data_, false);
    return *this;
}
Integer& Integer::operator-=(const Integer& i) {
    data_ = carry_lookahead_add(data_, i.data_, true);
    return *this;
}


bool Integer::ind(int num, int index) {
    return (bool)(num & (1 << index));
}

int Integer::carry_lookahead_add(int a, int b, bool is_minus) {
    // carry-lookahead adder
    // reason for using carry-lookahead adder even if this cannot run parallelly :
    // i think this way will be more close to real-used method.

    if (is_minus) b = ~b;
    int p = a ^ b;  // pi = ai ^ bi
    int g = a & b;  // gi = a6 & bi
    int ret = (bool)(p & 1) != is_minus; // s0 = p0 ^ c0
    for (int i = 1; i != 32; ++i) {  // s1 ~ s31

        // s3 = p3 ^ c2
        // c2 = g2 + v2
        // v2 = (p2 * g1) + (p2 * p1 * g0) + (p2 * p1 * p0 * minus)

        bool ci = ind(g,i-1);  // ci+1 = gi + v2
        for (int j = i-2; j >= 0; --j) {
            bool pipigi = ind(g,j);
            for (int k = i-1; k > j; --k) {
                pipigi = pipigi && ind(p,k);
            }
            ci = ci || pipigi;
        }
        bool pipim = is_minus;
        for (int k = i-1; k >= 0; --k) {
            pipim = pipim && ind(p,k);
        }
        ci = ci || pipim;

        ret |= (int)(ind(p,i) != ci) << i;  // si = pi ^ ci
    }
    count_plus++;
    return ret;
}

}