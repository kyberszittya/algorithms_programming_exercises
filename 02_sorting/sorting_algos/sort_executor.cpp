//
// Created by keret on 2026. 02. 15..
//

#include "sort_algorithms.h"
#include <fstream>
#include <iostream>
#include <chrono>

template <typename T>
void SortExecutor<T>::execute(const std::string& inputFilename, const std::string& outputFilename) {
    std::vector<T> data = readData(inputFilename);
    if (data.empty()) {
        return;
    }

    double elapsed = measureSortTime(data);
    writeOutput(inputFilename, data.size(), elapsed, outputFilename);
}

template <typename T>
std::vector<T> SortExecutor<T>::readData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    std::string line;
    std::vector<T> vecs;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        try {
            vecs.push_back(std::stoi(line));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid arguments\n";
        }
    }
    file.close();
    return vecs;
}

template <typename T>
double SortExecutor<T>::measureSortTime(std::vector<T>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    strategy_->sort(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken: " << elapsed.count() << "s" << std::endl;
    return elapsed.count();
}

template <typename T>
void SortExecutor<T>::writeOutput(const std::string& filename, size_t size, double elapsed, const std::string& outputFilename) {
    std::ofstream outfile(outputFilename, std::ios::app);
    if (outfile.is_open()) {
        outfile << "Algorithm: " << strategy_->getName() << ", File: " << filename << ", Size: " << size << ", Time: " << elapsed << "s" << std::endl;
        outfile.close();
    } else {
        std::cerr << "Unable to open output file: " << outputFilename << std::endl;
    }
}

// Explicit instantiation for int
template class SortExecutor<int>;