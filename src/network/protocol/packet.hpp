#ifndef PACKET_HPP
#define PACKET_HPP

namespace network {
    namespace protocol {
        class packet {
        public:
            virtual std::string const& id() = 0;
        };
    }
}

#endif