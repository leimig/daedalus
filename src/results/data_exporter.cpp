#include <fstream>
#include <iostream>
#include <ios>
#include <string>

#include "./data_exporter.hpp"
#include "./data_collector.hpp"

void results::data_exporter::write(network::network_config *config) {
    std::string file_name =
        config->output_file +
        "&p="  + config->policy_name +
        "&cs=" + std::to_string(config->cache_size) +
        "&ts=" + std::to_string(config->network_three_size) +
        "&np=" + std::to_string(config->number_of_packets) +
        "&rs=" + std::to_string(config->round_size) +
        "&ws=" + std::to_string(config->warmup_size) +
        "&za=" + std::to_string(config->zipf_distribution_alpha) +
        ".ddl";

    std::ofstream output_stream;
    output_stream.open(file_name, std::ios_base::app | std::ios_base::out);

    output_stream
        << std::to_string(results::data_collector::instance()->cache_lookups()) << std::endl
        << std::to_string(results::data_collector::instance()->cache_hits()) << std::endl
        << std::to_string(results::data_collector::instance()->cache_misses()) << std::endl
        << std::endl
        ;

    output_stream.close();
}