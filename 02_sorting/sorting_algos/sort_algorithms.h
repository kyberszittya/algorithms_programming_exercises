//
// Created by keret on 2026. 02. 15..
//

#ifndef ALGORITHMS_PROGRAMMING_EXERCISES_SORT_ALGORITHMS_H
#define ALGORITHMS_PROGRAMMING_EXERCISES_SORT_ALGORITHMS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

template <typename T>
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<T>& arr) = 0;
    virtual std::string getName() const = 0;
};

template <typename T>
class InsertionSort : public SortStrategy<T> {
public:
    void sort(std::vector<T>& arr) override;
    std::string getName() const override { return "Insertion Sort"; }
};

template <typename T>
class SortExecutor {
public:
    SortExecutor(std::unique_ptr<SortStrategy<T>> strategy) : strategy_(std::move(strategy)) {}

    void execute(const std::string& inputFilename, const std::string& outputFilename);

private:
    std::unique_ptr<SortStrategy<T>> strategy_;

    std::vector<T> readData(const std::string& filename);
    double measureSortTime(std::vector<T>& data);
    void writeOutput(const std::string& filename, size_t size, double elapsed, const std::string& outputFilename);
};

#endif //ALGORITHMS_PROGRAMMING_EXERCISES_SORT_ALGORITHMS_H