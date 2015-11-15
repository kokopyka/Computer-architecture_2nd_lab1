#include "BigNumbers.h"
#include <fstream>

void read(const char * name, string & num1, string & num2, char & action);
void write(const char * name, const vector<long> * numb);

int main() {

    string number1, number2;  // Operands
    char action;              // Action (minus or plus)

    read("data.txt", number1, number2, action);

    // Initialize class instance with numbers and math action
    BigNumbers BigNumb = BigNumbers(number1, number2, action);

    // Start timer
    clock_t time = clock();

    // Calculate
    BigNumb.process();

    // Write result to file
    write("result.txt", BigNumb.get_result());

    // Write time of execution
    time = clock() - time;
    cout << "Time of execution: " << (double)time/CLOCKS_PER_SEC << endl;

    // For 10 minutes processing
//    while ((clock() - time) / CLOCKS_PER_SEC <= 10 * 60)
//        BigNumb.process();

    return 0;
}

void read(const char * name, string & num1, string & num2, char & action)
{
    ifstream f(name);

    // First line holds number1, second - action, third - number2
    f >> num1;
    f >> action;
    f >> num2;

    f.close();
}

void write(const char * name, const vector<long> * numb)
{
    ofstream f(name);

    int n = (int) (numb->size() - ((*numb)[numb->size() - 1] != 0 ? 1 : 2));
    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; i != n && j < (int)(log10(pow(10, 9) / (*numb)[i])); j++)
            f << '0';
        f << (*numb)[i];
    }

    f.close();
}