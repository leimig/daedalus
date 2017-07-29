#include <ctime>
#include <random>
#include <vector>

#include "./../../../lib/easylogging++.h"

#include "./graph_topology.hpp"
#include "./../node/network_node.hpp"
#include "./../node/link.hpp"
#include "./../node/cache/no_cache.hpp"

network::topology::graph_topology::graph_topology() {

}

network::topology::graph_topology::~graph_topology() {

}

std::list<network::node::network_node*> network::topology::graph_topology::generate(network::topology::topology_config* config) {
    std::srand(std::time(0));
    std::list<network::node::network_node*> nodes;
    std::vector<std::vector<network::node::network_node*>*> clusters;
    int clusters_size = 0;

    int uuid = 0;

    do {
        int nodes_in_cluster = 1 + (std::rand() % config->max_number_of_nodes_in_clusters);
        LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes in Cluster " << nodes_in_cluster;

        if ((nodes.size() + nodes_in_cluster) > config->number_of_nodes) {
            nodes_in_cluster = nodes.size() - config->number_of_nodes;
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes in Cluster (updated)" << nodes_in_cluster;
        }

        std::vector<network::node::network_node*>* cluster = new std::vector<network::node::network_node*>(nodes_in_cluster);

        /**************************************************************
        **************            BUILD CLUSTER          **************
        **************************************************************/
        for (int i = 0; i < nodes_in_cluster; i++) {
            cluster->insert(cluster->end(), new network::node::network_node(++uuid, new network::node::cache::no_cache));
            nodes.push_back((*cluster)[i]);

            LOG(INFO) << "[TOPOLOGY_BULD] " << "Create node in cluster. Id:" << uuid;
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes counter:" << nodes.size();
        }
        LOG(INFO) << "[TOPOLOGY_BULD] " << "Connect Nodes";
        /**************************************************************
        **************   LINK MAIN NODE TO ALL CHILDREN   *************
        **************************************************************/
        for (int i = 1; i < nodes_in_cluster; i++) {
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connect node " << cluster[0]->id() << " to node " << cluster[i]->id();
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connect node " << (*cluster)[i]->id() << " to node " << (*cluster)[0]->id();
            (*cluster)[0]->register_forwarding_node((*cluster)[i]);
            (*cluster)[i]->register_forwarding_node((*cluster)[0]);
        }

        LOG(INFO) << "[TOPOLOGY_BULD] " << "Register Cluster";
        clusters.insert(clusters.end(), cluster);
        clusters_size++;
        LOG(INFO) << "[TOPOLOGY_BULD] " << "Cluster Registered";

    } while (nodes.size() < config->number_of_nodes);

    LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Clusters";

    for (int i = 0; i < clusters_size; i++) {
        int number_of_edges = 1 + (std::rand() % 2);

        for (int j = 1; j <= number_of_edges; j++) {
            int cluster_j = ((i + (2*j)) % clusters_size);
            (*clusters[i])[0]->register_forwarding_node((*clusters[cluster_j])[0]);

            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connection node " << (*clusters[i])[0]->id() << " to node " << (*clusters[cluster_j])[0]->id();
        }
    }

    LOG(INFO) << "[TOPOLOGY_BULD] " << "Topology Generated";

    return nodes;
}