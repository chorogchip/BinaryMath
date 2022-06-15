#pragma once
#include<iostream>
#include"Logger.hpp"
#include"Integer.hpp"

namespace tst {

using namespace std;
using namespace bm;

typedef Integer<32> myint;

static void testcomp_equal() {
    Logger::start_test("compare equal");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a == b) != (i == j))
                Logger::error(i, j);
        }
    Logger::end_test();
}
static void testcomp_not_equal() {
    Logger::start_test("compare not equal");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a != b) != (i != j))
                Logger::error(i, j);
        }
    Logger::end_test();
}
static void testcomp_bigger() {
    Logger::start_test("compare bigger");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a < b) != (i < j))
                Logger::error(i, j);
        }
    Logger::end_test();
}
static void testcomp_smaller() {
    Logger::start_test("compare smaller");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a > b) != (i > j))
                Logger::error(i, j);
        }
    Logger::end_test();
}
static void testcomp_not_smaller() {
    Logger::start_test("compare not smaller");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a <= b) != (i <= j))
                Logger::error(i, j);
        }
    Logger::end_test();
}
static void testcomp_not_bigger() {
    Logger::start_test("compare not bigger");
    for (int i = -100; i <= 100; ++i)
        for (int j = -100; j <= 100; ++j) {
            myint a(i);
            myint b(j);
            if ((a >= b) != (i >= j))
                Logger::error(i, j);
        }
    Logger::end_test();
}

};