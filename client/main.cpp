#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include "common/sample.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    bool connected = true;
    string entry;

    while(connected)
    {
        cout << ">";
        cin >> entry;
        //if(entry == 'exit'){ connected = false; }
        cout << endl;
    }

    cout << "Hello world!" << endl;
    cout << "1+1=" << SampleAddInt(1, 1) << endl;

    return EXIT_SUCCESS;
}
