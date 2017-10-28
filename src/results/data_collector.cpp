#include "data_collector.hpp"

results::data_collector *results::data_collector::s_data_collector = 0;

void results::data_collector::reset() {
    delete results::data_collector::s_data_collector;
    results::data_collector::s_data_collector = 0;
}

void results::data_collector::cache_hit() {
    this->m_cache_lookups++;
    this->m_cache_hits++;
}

void results::data_collector::cache_miss() {
    this->m_cache_lookups++;
    this->m_cache_misses++;
}