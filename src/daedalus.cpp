#include <iostream>
#include <string>

#include "./../lib/easylogging++.h"

#include "./results/data_collector.hpp"
#include "./results/data_exporter.hpp"
#include "./input_parser.hpp"
#include "./network/network_simulator.hpp"

INITIALIZE_EASYLOGGINGPP

void print_help();
void print_configuration(network::network_config* network_config);

int main(int argc, char const *argv[]) {
    int rounds_count = 1;
    input_parser parser(argc, argv);

    if (parser.cmd_option_exists("-h")) {
        print_help();
        return 0;
    }

    START_EASYLOGGINGPP(argc, argv);

    /**************************************************************
    **************             READ INPUT            **************
    **************************************************************/
    if (parser.cmd_option_exists("-rc")) {
        rounds_count = stoi(parser.get_cmd_option("-rc"));
    }

    network::network_config network_config;

    if (parser.cmd_option_exists("-of")) {
        network_config.output_file = parser.get_cmd_option("-of");
    }

    if (parser.cmd_option_exists("-p")) {
        network_config.policy_name = parser.get_cmd_option("-p");
    }

    if (parser.cmd_option_exists("-cs")) {
        network_config.cache_size = stoi(parser.get_cmd_option("-cs"));
    }

    if (parser.cmd_option_exists("-ts")) {
        network_config.network_three_size = stoi(parser.get_cmd_option("-ts"));
    }

    if (parser.cmd_option_exists("-np")) {
        network_config.number_of_packets = stoi(parser.get_cmd_option("-np"));
    }

    if (parser.cmd_option_exists("-rs")) {
        network_config.round_size = stoi(parser.get_cmd_option("-rs"));
    }

    if (parser.cmd_option_exists("-ws")) {
        network_config.warmup_size = stoi(parser.get_cmd_option("-ws"));
    }

    if (parser.cmd_option_exists("-za")) {
        network_config.zipf_distribution_alpha = stoi(parser.get_cmd_option("-za"));
    }

    print_configuration(&network_config);

    /**************************************************************
    **************         START SIMULATION          **************
    **************************************************************/
    for (int i = 0; i < rounds_count; ++i) {
        VLOG(0) << "[DAEDALUS] Starting round " << (i+1);

        VLOG(0) << "[DAEDALUS] Setting up network simulator";
        network::network_simulator simulator(network_config);

        VLOG(0) << "[DAEDALUS] Executing simulation";
        simulator.run();

        VLOG(0) << "[DAEDALUS] Simulation finished";

        VLOG(0) << "[DAEDALUS][RESULTS] Cache lookups: " << results::data_collector::instance()->cache_lookups();
        VLOG(0) << "[DAEDALUS][RESULTS] Cache hits/misses: "
            << results::data_collector::instance()->cache_hits() << "/"
            << results::data_collector::instance()->cache_misses();
        VLOG(0) << "[DAEDALUS][RESULTS] Cache hits percentage: "
            << ((double)(results::data_collector::instance()->cache_hits() * 100) / (double)(results::data_collector::instance()->cache_lookups()))
            << "%";

        VLOG(0) << "[DAEDALUS] Writing results in file";
        results::data_exporter::write(&network_config);
        VLOG(0) << "[DAEDALUS] Results written in output file";

        VLOG(0) << "[DAEDALUS] Round " << (i+1) << " finished";

        results::data_collector::reset();
    }

    VLOG(0) << "[DAEDALUS] Thanks for using me!";
    return 0;
}

void print_configuration(network::network_config* network_config) {
    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Policy: "
        << network_config->policy_name;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Cache size: "
        << network_config->cache_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Number of nodes in the network three under the target node: "
        << network_config->network_three_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Number of unique packets: "
        << network_config->number_of_packets;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "How many packets will be used during simulation: "
        << network_config->round_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Number of packets used during warm up: "
        << network_config->warmup_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Zipf's Alpha: "
        << network_config->zipf_distribution_alpha;
}

void print_help() {
    network::network_config network_config;

    std::cout << "OVERVIEW: Daedalus is an Information Centric Network simulator." << std::endl;
    std::cout << std::endl;

    std::cout << "USAGE: daedalus [options]" << std::endl;
    std::cout << std::endl;

    std::cout << "OPTIONS:" << std::endl;
    std::cout << "-of <arg>   Output file. Default: "                                                     << network_config.output_file        << std::endl;
    std::cout << "-p  <arg>   Policy name. Default: "                                                     << network_config.policy_name        << std::endl;
    std::cout << "-cs <arg>   Cache size. How many packets can be stored by the Content Store. Default: " << network_config.cache_size         << std::endl;
    std::cout << "-ts <arg>   Number of nodes in the network three under the target node. Default: "      << network_config.network_three_size << std::endl;
    std::cout << "-np <arg>   Number of unique packets. Default: "                                        << network_config.number_of_packets  << std::endl;
    std::cout << "-rs <arg>   Round duration. How many packets represent a round. Default: "              << network_config.round_size         << std::endl;
    std::cout << "-ws <arg>   Number of packets used during warm up. Default: "                           << network_config.warmup_size        << std::endl;
    std::cout << "-za <arg>   Zipf's Alpha. Alpha parameter in Zipf distribution. Default: "              << network_config.zipf_distribution_alpha << std::endl;
    std::cout << "-rc <arg>   Round counts. How many rounds should be executed. Default: "                << 1 << std::endl;
    std::cout << std::endl;

    std::cout << "LOGGING OPTIONS:" << std::endl;
    std::cout << "--v=<arg>   Verbosity Level. Default: 0. Possible options: 0 (GENERAL), 1 (INFO), 2 (WARNING), 9 (DEBUG)"  << std::endl;
}