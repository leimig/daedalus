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

network::node::network_node** network::topology::graph_topology::generate(network::topology::topology_config* config) {
    std::srand(std::time(0));

    network::node::network_node** nodes = new network::node::network_node*[config->number_of_nodes + 1];
    int nodes_count = 0;

    std::vector<int> clusters_pos;
    int uuid = 0;

    // position of first cluster in []nodes
    clusters_pos.push_back(0);

    do {
        int nodes_in_cluster = 1 + (std::rand() % config->max_number_of_nodes_in_clusters);
        LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes in Cluster: " << nodes_in_cluster;

        if ((nodes_count + nodes_in_cluster) > config->number_of_nodes) {
            nodes_in_cluster = config->number_of_nodes - nodes_count;
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes in Cluster (updated):" << nodes_in_cluster;
        }

        int start_pos = *clusters_pos.end();
        // start position of the next cluster
        clusters_pos.push_back(start_pos + nodes_in_cluster);
        LOG(INFO) << "[TOPOLOGY_BULD] " << "AA";

        /**************************************************************
        **************            BUILD CLUSTER          **************
        **************************************************************/
        for (int i = 0; i < nodes_in_cluster; i++) {
            // LOG(INFO) << "[TOPOLOGY_BULD] " << "BB";
            // nodes[start_pos + i] = (network::node::network_node*)malloc(sizeof(network::node::network_node));
            // Segmentation fault is happening here
            nodes[start_pos + i] = new network::node::network_node(++uuid, new network::node::cache::no_cache);
            // LOG(INFO) << "[TOPOLOGY_BULD] " << "CC";
            // LOG(INFO) << "[TOPOLOGY_BULD] " << "DD";
            // LOG(INFO) << "[TOPOLOGY_BULD] " << "EE";
            nodes_count++;

            LOG(INFO) << "[TOPOLOGY_BULD] " << "Created Node ID:" << uuid;
        }

        LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Cluster Nodes";

        /*************************************************************
        **************   LINK MAIN NODE TO ALL CHILDREN   *************
        *************************************************************/
        for (int i = 1; i < nodes_in_cluster; i++) {
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Node " << nodes[start_pos]->id()   << " to Node " << nodes[start_pos+i]->id();
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Node " << nodes[start_pos+i]->id() << " to Node " << nodes[start_pos]->id();
            nodes[start_pos]->register_forwarding_node(nodes[start_pos+i]);
            nodes[start_pos+i]->register_forwarding_node(nodes[start_pos]);
        }

        LOG(INFO) << "[TOPOLOGY_BULD] " << "Nodes Counter:" << nodes_count;

    } while (nodes_count < config->number_of_nodes);

    LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Clusters";

    for (int i = 0; i < clusters_pos.size(); i++){
        int number_of_edges = 1 + (std::rand() % 2);

        for (int j = 1; j <= number_of_edges; j++) {
            int cluster_start = clusters_pos.at(i);
            int target_cluster = 0;

            if (i == *clusters_pos.end()) {
                // target cluster should be the cluster in position j
                target_cluster = clusters_pos.at(j - 1);
            } else {
                // else, get current plus j
                target_cluster = clusters_pos.at(i + j);
            }

            nodes[cluster_start]->register_forwarding_node(nodes[target_cluster]);
            LOG(INFO) << "[TOPOLOGY_BULD] " << "Connecting Node " << nodes[cluster_start]->id() << " to Node " << nodes[target_cluster]->id();
        }
    }

    LOG(INFO) << "[TOPOLOGY_BULD] " << "Topology Generated";

    return nodes;
}