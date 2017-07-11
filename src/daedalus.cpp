#include <iostream>

#include "./../lib/easylogging++.h"
#include "./network/network_simulator.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char const *argv[]) {
    START_EASYLOGGINGPP(argc, argv);

    LOG(INFO) << "Setting up network simulator";
    network::network_simulator simulator(1);

    LOG(INFO) << "Starting simulation";
    simulator.start();

    return 0;
}