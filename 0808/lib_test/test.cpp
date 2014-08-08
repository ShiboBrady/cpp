#include "Server.h"

int main(int argc, const char *argv[])
{
    Server echo_server(9999);
    echo_server.start();
    return 0;
}
