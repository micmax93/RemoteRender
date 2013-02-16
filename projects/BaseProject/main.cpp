#include <iostream>
#include <vector>
#include <stdio.h>
#include <fcntl.h>
#include "protocol.hpp"
#include "connectivity.hpp"
#include "utilities.hpp"
#include "server.hpp"
#include "renderer.hpp"
#include "Reader.h"
#include "client.hpp"
using namespace std;

int debug_mode = TRUE;

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Invalid initialization, use: '%s start port' or %s stop pid'\n", argv[0], argv[0]);
        exit(0);
    }

    string cmd(argv[1]);
    int port = atoi(argv[2]);

    if (cmd == "start") {
        if (!fork()) {
            server::initConection(port);
            server::mainLoop(client::new_connection);
        }
    } else if (cmd == "stop") {
        int pid = server::getServerPid(port);
        kill(pid, SIGTERM);
    } else {
        printf("Invalid initialization, use: '%s start port' or %s stop'\n", argv[0], argv[0]);
        exit(0);
    }

    return 0;
}
