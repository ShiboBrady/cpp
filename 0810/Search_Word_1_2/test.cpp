#include "Server.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    Server server(9999, "out.txt");
    server.start();
    return 0;
}
