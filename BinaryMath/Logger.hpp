#pragma once
#include<cstdio>
#include<string>
#include<iostream>

namespace tst {

using namespace std;

class Logger {

private:
    static std::string test_name_;
    static bool succeed;

    template<class T>
    static void error_prt(T data1);
    template<class T, class... Types>
    static void error_prt(T arg, Types... datas);

public:
    static void start_test(std::string test_name);
    static void end_test();

    static void error();
    template<class... Types>
    static void error(Types... datas);

};


std::string Logger::test_name_ = "";
bool Logger::succeed = true;

template<class T>
void Logger::error_prt(T data1) {
    cout << data1;
}
template<class T, class... Types>
void Logger::error_prt(T arg, Types... datas) {
    cout << arg << " / ";
    Logger::error_prt(datas...);
}



void Logger::start_test(std::string test_name) {
    Logger::test_name_ = test_name;
    cout << "test : " << test_name << endl;
    Logger::succeed = true;
}
void Logger::end_test() {
    if (succeed) cout << "test succeed : " << test_name_ << endl;
    else cout << "test failed : " << test_name_ << endl;
}

void Logger::error() {
    cout << "    error occured in test : " << Logger::test_name_ << endl;
    Logger::succeed = false;
}
template<class... Types>
void Logger::error(Types... datas) {
    cout << "    error occured in test : " << Logger::test_name_ << endl;
    cout << "        data : ";
    Logger::error_prt(datas...);
    cout << endl;
    Logger::succeed = false;
}

}