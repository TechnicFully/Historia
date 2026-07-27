#include "../historia.hpp"

#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>


int num_pushes = 1000000;
int num_runs = 100;

auto run_test()
{
    Historia<int> history;


    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < num_pushes; i ++) {
        history.push(0);
    }
    auto end = std::chrono::high_resolution_clock::now();


    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

int main()
{
    std::cout << "Running " << num_runs << " tests with a total of " << num_pushes << " pushes per run" << std::endl;


    std::vector<std::chrono::microseconds> test_results_times;
    for (auto i = 0; i < num_runs; i++) {
        test_results_times.push_back(run_test());
    }

    long long total_us = std::accumulate(
        test_results_times.begin(), test_results_times.end(), 0LL,
        [](long long sum, std::chrono::microseconds d) {
            return sum + d.count();
    });

    auto avg_us = std::chrono::microseconds(total_us / test_results_times.size());

    
    std::cout << "Average run time: " << avg_us.count() << " microseconds\n" << std::endl;
    
    return 0;
}