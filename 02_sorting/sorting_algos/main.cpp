//
// Created by keret on 2026. 02. 15..
//

#include "sort_algorithms.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    std::unique_ptr<SortStrategy<int>> strategy = std::make_unique<InsertionSort<int>>();
    SortExecutor<int> executor(std::move(strategy));
    executor.execute(inputFilename, outputFilename);

    return 0;
}
