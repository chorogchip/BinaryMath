#pragma once

namespace bm {

template<int sz>
class Algorithms {

public:
    static void add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus);
    static void add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size);
    static void mult(const bool a[sz], const bool b[sz], bool s[sz], int size);

private:
    static void carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus);
    static void carry_lookahead_add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size);
    static void karastuba_multiply(const bool a[sz], const bool b[sz], bool s[sz], int size);
};

template<int sz>
void Algorithms<sz>::add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus) {
    carry_lookahead_add(a, b, s, is_minus);
}

template<int sz>
void Algorithms<sz>::add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size) {
    carry_lookahead_add_size(a, b, s, is_minus, size);
}

template<int sz>
void Algorithms<sz>::mult(const bool a[sz], const bool b[sz], bool s[sz], int size) {
    karastuba_multiply(a, b, s, size);
}

template<int sz>
void Algorithms<sz>::carry_lookahead_add(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus) {
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
    return;
}

template<int sz>
void Algorithms<sz>::carry_lookahead_add_size(const bool a[sz], const bool b[sz], bool s[sz], bool is_minus, int size) {
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
    return;
}

template<int sz>
void Algorithms<sz>::karastuba_multiply(const bool a[sz], const bool b[sz], bool s[sz], int size) {
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

    return;
}

}