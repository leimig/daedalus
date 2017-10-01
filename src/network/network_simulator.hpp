#ifndef NETWORK_SIMULATOR_HPP
#define NETWORK_SIMULATOR_HPP

#include <list>

#include "./node/network_interface.hpp"
#include "./node/network_node.hpp"
#include "./node/protocol/packet.hpp"
#include "./node/protocol/data_packet.hpp"
#include "./node/protocol/interest_packet.hpp"

namespace network {
    struct network_config {
        std::string policy_name = "NO_POLICY";
        int network_three_size = 50;
        int number_of_packets = 500;
        int round_size = 8000;
        int warmup_size = 500;
    };

    typedef network_config network_config;

    class network_simulator : public network::node::network_interface {
    private:
        network::network_config m_config;
        node::network_node *m_node;

    public:
        network_simulator(network::network_config config);
        ~network_simulator();

        void start();
        void warmup();

        virtual void lookup(node::protocol::interest_packet packet);
        virtual void respond(int id, node::protocol::data_packet packet);
    };
}

#endif