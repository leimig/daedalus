# Daedalus
Daedalus is an ICN Cache Simulator.

Daedalus has two basic building blocks. The first block is `network::node::network_node` class. It simulates the workings of a network node that implements the ICN protocols. This node is monitored and used to collect the results of the simulation. The second block is `network::network_simulator` which works as a proxy of the entire network for the node being tested. The entire simulation is coordinated through this proxy.

## How to build

Daedalus does not depends on any external library, the only library it uses is already available at `lib/`.

In order to build `daedalus`, you need to execute the following command

```
make
```

then copy the executable generated at `bin/` called `daedalus`.

## Policies

There are a limited number of available policies, however, it should be easy to implement your own.

### Available Policies

- NO_CACHE
- FIFO
- LRU
- CLIMB

### How to create a new Policy

Creating a new Policy should be easy enough.

- Create the `*.hpp` and `*.cpp` files that contains the implementation of your Policy at `src/network/node/cache`. Use the existing ones as base.
- Modify policy.cpp to instantiate your new policy when its id is used.
- Contribute it back.

## Help

```
OVERVIEW: Daedalus is an Information Centric Network simulator.

USAGE: daedalus [options]

OPTIONS:
-of <arg>   Output file.
-p  <arg>   Policy name.
-cs <arg>   Cache size. How many packets can be stored by the Content Store.
-ts <arg>   Number of nodes in the network three under the target node.
-np <arg>   Number of unique packets.
-rs <arg>   Round duration. How many packets represent a round.
-ws <arg>   Number of packets used during warm up.
-za <arg>   Zipf's Alpha. Alpha parameter in Zipf distribution.

LOGGING OPTIONS:
--v=<arg>   Verbosity Level. Default: 0. Possible options: 0 (GENERAL), 1 (INFO), 2 (WARNING), 9 (DEBUG)
```

## Author

Daedalus is a project by [Higgor Leimig](https://github.com/leimig).

## License

This project is under the MIT license and can be use in commercial or personal projects without restrictions. Just consider contributing your improvements back.

## References

##### Network Named Content
```
\@inproceedings{NetworkingNamedContent,
    title={Networking named content},
    author={Jacobson, Van and Smetters, Diana K and Thornton, James D and Plass, Michael F and Briggs, Nicholas H and Braynard, Rebecca L},
    booktitle={Proceedings of the 5th international conference on Emerging networking experiments and technologies},
    pages={1--12},
    year={2009},
    organization={ACM}
}
```