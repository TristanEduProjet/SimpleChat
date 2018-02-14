#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

#include <string>
/*
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <time.h>
*/

extern "C"
{
    // Retourne l'ip externe
    std::string real_ip();

    // A function adding two integers and returning the result
    int SampleAddInt(const int i1, const int i2);

    // A function doing nothing ;)
    void SampleFunction1();

    // A function always returning zero
    int SampleFunction2();
}

#endif // MAIN_HPP_INCLUDED
