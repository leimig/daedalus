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

        int m_round_step;
        int m_warmup_step;

        void warmup();
        void send_interest_packet();

        void handle_lookup(node::protocol::interest_packet packet);
        void handle_answer(node::protocol::data_packet packet);

        bool is_warmup_active();
        bool is_round_active();
        node::protocol::interest_packet* next_lookup_to_answer();

    public:
        network_simulator(network::network_config config);
        ~network_simulator();

        void run();

        virtual void handle(node::protocol::packet packet);
    };
}

#endif