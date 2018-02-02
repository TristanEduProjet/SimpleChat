#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <time.h>

extern "C"
{
    // Fermeture de la socket //
    close( socketRecepteur );

    // A function adding two integers and returning the result
    int SampleAddInt(const int i1, const int i2)
    {
        return i1 + i2;
    }

    // A function doing nothing ;)
    void SampleFunction1()
    {
        // insert code here
    }

    // A function always returning zero
    int SampleFunction2()
    {
        // insert code here
        
        return 0;
    }
}
