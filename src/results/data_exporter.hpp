#ifndef DATA_EXPORTER_HPP
#define DATA_EXPORTER_HPP

#include "../network/network_simulator.hpp"

namespace results {
    class data_exporter {
    public:
        static void write(network::network_config *config);
    };
}

#endif