#pragma once

namespace bm{  class Integer {

private:
    int data_;

    static int count_plus;
    static int count_mult;
    static int count_div;

public:
    Integer();
    Integer(int data);
    Integer(const Integer& i);
    Integer& operator=(const Integer& i);
    ~Integer();

    int getInt() const;

    Integer operator+(const Integer& i);
    Integer operator-(const Integer& i);
    Integer& operator+=(const Integer& i);
    Integer& operator-=(const Integer& i);

private:
    bool ind(int num, int index);
    int carry_lookahead_add(int a, int b, bool is_minus);
};}
