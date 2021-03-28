#ifndef CA_GENERATOR_H
#define CA_GENERATOR_H

#include <iostream>
#include <bitset>
#include <ctime>

inline static constexpr size_t CA_bit_length = 1023;
inline static constexpr size_t nav_bit_length = 128;
inline static constexpr size_t rcode_bit_length = CA_bit_length + nav_bit_length;


class CAGenerator {
public:
    using CA_code = std::bitset<CA_bit_length>;

    CAGenerator(size_t);
    ~CAGenerator() = default;

    CA_code operator()();

    void set_satellite(size_t);

private:
    CA_code code;
    size_t PRN_id : 7;
    bool was_generated : 1;
    inline static const size_t PRN_id_size = 32;

    void G1_generator(CA_code&);
    void G2_generator(CA_code&);

    static inline constexpr std::pair<size_t, size_t> PRN_ids[PRN_id_size] {
            {2, 6}, {3, 7}, {4, 8}, {5, 9}, {1, 9}, {2, 10}, {1, 8}, {2, 9},
            {3, 10}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10},
            {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 9}, {1, 3}, {4, 6},
            {5, 7}, {6, 8}, {7, 9}, {8, 10}, {1, 6}, {2, 7}, {3, 8}, {4, 9}
    };
};

std::bitset<nav_bit_length> generate_nav();

#endif