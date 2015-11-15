//
// Created by oleh on 05.11.15.
//

#include "BigNumbers.h"

using namespace std;

// Checking input line. Line must contain only digits and can't be empty
bool BigNumbers::is_correct(string & a) {
    if (!a.size()) return false;

    for (int i = 0; i < a.size(); i++)
        if (int(a[i]) > 57 || int(a[i]) < 44 || int(a[i]) == 46 || int(a[i]) == 47)
            return false;

    return true;
}

// Input string line convert to vector<long>
vector<long> BigNumbers::string_to_array(string & str){
    bool is_minus = str.find('-') != string::npos;
    if (is_minus) str.erase(str.begin());

    int N = (int) (str.size() / DEC_DIGITS_IN_LONG) + (str.size() % DEC_DIGITS_IN_LONG > 0);

    vector<long> Array;

    for (int i = 0; i < N - 1; i++)
    {
        string tmp = string(str.begin() + str.size() - (i + 1) * DEC_DIGITS_IN_LONG, str.begin() + str.size() - i * DEC_DIGITS_IN_LONG);
        Array.push_back(stoi(tmp));
    }
    Array.push_back(stoi(string(str.begin(), str.begin() + str.size() - (N - 1) * DEC_DIGITS_IN_LONG)));

    if (is_minus) Array[Array.size() - 1] *= -1;

    return Array;
}

// Prepare all data for calculating
bool BigNumbers::init() {
    if (!is_correct(str_a) || !is_correct(str_b))
        return false;

    A = string_to_array(str_a);
    B = string_to_array(str_b);

    // Initial fill result vector
    for (int i = 0; i <= max(A.size(), B.size()); i++)
        C.push_back(0);

    return true;
}

// Plus two vectors and result is written to final vector C
void BigNumbers::plus(vector<long> * a, vector<long> * b) {
    unsigned long n = max(a->size(), b->size());

    for (int i = 0; i < n; ++i)
    {
        if (i < a->size()) C[i] += abs((*a)[i]);
        if (i < b->size()) C[i] += abs((*b)[i]);

        if (C[i] >= pow(10, DEC_DIGITS_IN_LONG))
        {
            C[i + 1]++;
            C[i] -= pow(10, DEC_DIGITS_IN_LONG);
        }
    }
}

// Minus two vectors and result is written to final vector C
void BigNumbers::minus(vector<long> *a, vector<long> *b) {
    unsigned long n = max(a->size(), b->size());
    bool final_sign_minus = false;

    for (int i = 0; i < n; ++i)
    {
        if (i < a->size()) C[i] += (*a)[i];
        if (i < b->size()) C[i] -= abs((*b)[i]); //5

        final_sign_minus = manage_CF(final_sign_minus, i);

        C[i] = abs(C[i]);
    }

    if (final_sign_minus)
        C[n - 1] *= -1;
}

// Manages carry flag. If there's negative element then organize transmit from higher bits
bool BigNumbers::manage_CF(bool final_sign_minus, int i) {
    // If result element is negative and final sign isn't negative
    if (C[i] < 0 && !final_sign_minus)
            if (i + 1 < A.size())
            {
                A[i + 1]--;
                C[i] = pow(10, DEC_DIGITS_IN_LONG) - abs(C[i]);
            }
            // If last element then we know that final sign is minus
            else
                return true;
    return final_sign_minus;
}

// Runner that sets all other functions
void BigNumbers::process() {
    if (!init()) return;

    bool minus_A = A[A.size() - 1] < 0, minus_B = B[B.size() - 1] < 0;

    // Work as with positive numbers knowing theirs signs
    A[A.size() - 1] = abs(A[A.size() - 1]);
    B[B.size() - 1] = abs(B[B.size() - 1]);

    process_by_sign(minus_A, minus_B);
}

//
inline void BigNumbers::process_by_sign(bool minus_A, bool minus_B) {
    if (action == '+' && !minus_A && !minus_B || action == '-' && !minus_A && minus_B)
        plus(&A, &B);
    else if (action == '+' && !minus_A && minus_B || action == '-' && !minus_A && !minus_B)
        minus(&A, &B);
    else if (action == '+' && minus_A && !minus_B || action == '-' && minus_A && minus_B)
        minus(&B, &A);
    else if (action == '+' && minus_A && minus_B || action == '-' && minus_A && !minus_B)
    {
        plus(&A, &B);
        C[C.size() - 1] > 0 ? C[C.size() - 1] *= -1 : C[C.size() - 2] *= -1;
    }
}

// Output and check if value is found
void BigNumbers::output() {
    if (!C.size())
    {
        cout << "Wrong data" << endl;
        return;
    }

    cout << "Result:  ";

    int n = (int) (C.size() - (C[C.size() - 1] != 0 ? 1 : 2));
    for (int i = n; i >= n - 10; i--)
        cout << C[i];
}

vector<long> * BigNumbers::get_result() {
    return &C;
}
