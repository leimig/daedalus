#ifndef NETWORK_SIMULATOR_HPP
#define NETWORK_SIMULATOR_HPP

#include <thread>

#include "./node/network_node.hpp"

namespace network {
    class network_simulator {
    private:
        std::list<std::thread*> m_threads;
        std::list<node::network_node*> m_nodes;

    public:
        network_simulator(int n_nodes);
        ~network_simulator();

        void start();
    };
}

#endif