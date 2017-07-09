#include <iostream>

#include "./network/network_simulator.hpp"

int main(int argc, char const *argv[]) {
    network::network_simulator simulator(1);

    simulator.start();

    std::cout << "Hello World\n";
    return 0;
}