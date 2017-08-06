#include <iostream>
#include <string>

#include "./../lib/easylogging++.h"

#include "./input_parser.hpp"
#include "./network/node/network_node.hpp"
#include "./network/network_simulator.hpp"
#include "./network/topology/topology_factory.hpp"
#include "./network/topology/topology.hpp"

INITIALIZE_EASYLOGGINGPP

void print_help();
void print_configuration(network::network_config* network_config);

int main(int argc, char const *argv[]) {
    input_parser parser(argc, argv);

    if (parser.cmd_option_exists("-h")) {
        print_help();
        return 0;
    }

    START_EASYLOGGINGPP(argc, argv);

    /**************************************************************
    **************          GENERATE NETWORK         **************
    **************************************************************/
    LOG(INFO) << "[DAEDALUS] " << "Setting up network topology";
    network::network_config network_config;

    network_config.topology_name = network::topology::topology_factory::GRAPH_TYPE;

    if (parser.cmd_option_exists("-t")) {
        network_config.number_of_threads = stoi(parser.get_cmd_option("-t"));
    }

    if (parser.cmd_option_exists("-tn")) {
        network_config.topology_name = parser.get_cmd_option("-tn");
    }

    if (parser.cmd_option_exists("-n")) {
        network_config.number_of_nodes = stoi(parser.get_cmd_option("-n"));
    }

    if (parser.cmd_option_exists("-cs")) {
        network_config.max_number_of_nodes_in_clusters = stoi(parser.get_cmd_option("-cs"));
    }

    print_configuration(&network_config);

    network::topology::topology_factory factory;
    network::topology::topology* topology = factory.get(network_config.topology_name);

    network::node::network_node **nodes = topology->generate(&network_config);
    delete topology;

    /**************************************************************
    **************         START SIMULATION          **************
    **************************************************************/
    LOG(INFO) << "[DAEDALUS] Setting up network simulator";
    network::network_simulator simulator(network_config, nodes);

    LOG(INFO) << "[DAEDALUS] Starting simulation";
    simulator.start();

    return 0;
}

void print_configuration(network::network_config* network_config) {
    LOG(INFO) << "[DAEDALUS][CONFIG] "
        << "Number of threads: "
        << network_config->number_of_threads;

    LOG(INFO) << "[DAEDALUS][CONFIG] "
        << "Topology name: "
        << network_config->topology_name;

    LOG(INFO) << "[DAEDALUS][CONFIG] "
        << "Number of nodes: "
        << network_config->number_of_nodes;

    LOG(INFO) << "[DAEDALUS][CONFIG] "
        << "Maximum number of nodes in cluster: "
        << network_config->max_number_of_nodes_in_clusters;
}

void print_help() {
    std::cout << "OVERVIEW: Daedalus is an Information Centric Network simulator." << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE: daedalus [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << std::endl;
    std::cout << "-t <arg>"   << "\t" << "Number of threads. Default: 10"                      << std::endl;
    std::cout << "-tn <arg>"  << "\t" << "Topology name. Supported values are: GRAPH"          << std::endl;
    std::cout << "-n <arg>"   << "\t" << "Number of nodes. Default: 50"                        << std::endl;
    std::cout << "-cs <arg>"  << "\t" << "Maximum number of nodes in a cluster. Default: 5"    << std::endl;
}