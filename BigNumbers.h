//
// Created by oleh on 05.11.15.
//

#ifndef COMPARCH1_BIGNUMBERS_H
#define COMPARCH1_BIGNUMBERS_H

#include "vector"
#include "string"
#include <iostream>
#include "cmath"        // pow

using namespace std;

class BigNumbers {

public:
    void process();
    void output();
    vector<long> * get_result ();

    BigNumbers() : str_a(""), str_b(""), action('+') {};
    BigNumbers(const string a, const string b, char act) : str_a(a), str_b(b), action(act) {};
    ~BigNumbers() {};

private:
    bool is_correct(string & a);
    bool init();
    inline void process_by_sign(bool minus_A, bool minus_B);
    bool manage_CF(bool final_sign_minus, int i) ;
    void plus(vector<long> * a, vector<long> * b);
    void minus(vector<long> * a, vector<long> * b);
    vector<long> string_to_array(string & str);

    char action;
    string str_a, str_b;
    vector<long> A, B, C;

    static const unsigned int DEC_DIGITS_IN_LONG = 9;
};

#endif
