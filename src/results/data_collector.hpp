#ifndef DATA_COLLECTOR_HPP
#define DATA_COLLECTOR_HPP

namespace results {
    class data_collector {
        static data_collector* s_data_collector;

        int m_cache_lookups = 0;
        int m_cache_hits = 0;
        int m_cache_misses = 0;

        data_collector() {}

    public:
        static data_collector* instance() {
            if (!s_data_collector)
                s_data_collector = new results::data_collector;

            return s_data_collector;
        }

        int cache_lookups() { return this-> m_cache_lookups; }
        int cache_hits() { return this-> m_cache_hits; }
        int cache_misses() { return this-> m_cache_misses; }

        void cache_hit();
        void cache_miss();
    };
}

#endif