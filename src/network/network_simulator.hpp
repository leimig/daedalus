#ifndef NETWORK_SIMULATOR_HPP
#define NETWORK_SIMULATOR_HPP

#include <list>
#include <chrono>
#include <string>
#include <memory>
#include <functional>

#include "./node/network_interface.hpp"
#include "./node/network_node.hpp"
#include "./node/cache/no_cache.hpp"
#include "./node/protocol/packet.hpp"
#include "./node/protocol/data_packet.hpp"
#include "./node/protocol/interest_packet.hpp"

namespace network {
    typedef struct network_config {
        std::string output_file = "output";
        std::string policy_name = network::node::cache::no_cache::id;
        int cache_size = 20;
        int network_three_size = 50;
        int number_of_packets = 500;
        int round_size = 8000;
        int warmup_size = 500;
        double zipf_distribution_alpha = 0.5;
    } network_config;

    typedef struct received_lookup {
        std::string packet_id;
        std::chrono::milliseconds response_timestamp;
    } received_lookup;

    class network_simulator : public network::node::network_interface {
    private:
        network::network_config m_config;
        node::network_node *m_node;

        std::list<received_lookup> m_received_lookups;

        int m_round_step;
        int m_warmup_step;

        void warmup();
        void send_interest_packet();

        void run_round(int* step, int* size);
        std::shared_ptr<network::node::protocol::data_packet> next_lookup_to_answer();

    public:
        network_simulator(network::network_config config);
        ~network_simulator();

        void run();

        virtual int id();

        virtual void handle_lookup(network::node::protocol::interest_packet packet);
        virtual void handle_answer(network::node::protocol::data_packet packet);
    };
}

#endif