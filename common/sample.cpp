extern "C"
{
    /*std::string real_ip() {

        HINTERNET net = InternetOpen("IP retriever",
            INTERNET_OPEN_TYPE_PRECONFIG,
            NULL,
            NULL,
            0);

        HINTERNET conn = InternetOpenUrl(net,
                                         "http://myexternalip.com/raw",
                                          NULL,
                                          0,
                                          INTERNET_FLAG_RELOAD,
                                          0);

        char buffer[4096];
        DWORD read;

        InternetReadFile(conn, buffer, sizeof(buffer)/sizeof(buffer[0]), &read);
        InternetCloseHandle(net);

        return std::string(buffer, read);
    }*/

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
