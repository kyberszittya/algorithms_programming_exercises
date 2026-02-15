//
// Created by keret on 2026. 02. 15..
//

#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <fstream>

struct RandomGenerator {
    std::mt19937_64 sampler;
    std::vector<unsigned int> available_numbers;

    RandomGenerator(unsigned int seed, unsigned int max_val): sampler(seed) {
        available_numbers.resize(max_val);
        std::iota(available_numbers.begin(), available_numbers.end(), 0);
    }

    unsigned int sample_non_repeatable() {
        if (available_numbers.empty()) {
            throw std::runtime_error("No more numbers to sample");
        }

        std::uniform_int_distribution<size_t> dist(0, available_numbers.size() - 1);
        size_t index = dist(sampler);

        unsigned int result = available_numbers[index];

        // Swap with the last element and pop back for O(1) removal
        std::swap(available_numbers[index], available_numbers.back());
        available_numbers.pop_back();

        return result;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <max_value> <count> <output_file>" << std::endl;
        return 1;
    }

    unsigned int max_val = std::stoi(argv[1]);
    unsigned int count = std::stoi(argv[2]);
    std::string output_file = argv[3];

    if (count > max_val) {
        std::cerr << "Error: count cannot be greater than max_value" << std::endl;
        return 1;
    }

    std::ofstream out(output_file);
    if (!out.is_open()) {
        std::cerr << "Error: could not open file " << output_file << std::endl;
        return 1;
    }

    RandomGenerator gen(12345, max_val);
    for(unsigned int i=0; i<count; ++i) {
        out << gen.sample_non_repeatable() << std::endl;
    }
    out << std::endl;

    out.close();
    return 0;
}