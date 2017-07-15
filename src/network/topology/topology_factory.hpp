#ifndef TOPOLOGY_FACTORY_HPP
#define TOPOLOGY_FACTORY_HPP

#include <string>

namespace network {
    namespace topology {
        class topology;

        class topology_factory {
        public:
            static const std::string GRAPH_TYPE;

            topology_factory();
            ~topology_factory();

            topology* get(std::string type);
        };
    }
}

#endif