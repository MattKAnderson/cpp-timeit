#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>


namespace timeIt {

    template <typename T, typename... Args>
    static double sample(const T& func, Args&&... args) {

        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();   

        return std::chrono::duration<double, std::milli>(end-start).count();   
    }

    template <typename T, typename... Args>
    void print(const T& func, Args&&... args) {

        double time = sample(func, std::forward<Args>(args)...);

        std::string unitname = "ms";
        if (time > 1000.0) {
            time /= 1000.0;
            unitname = "s";
        }

        std::cout << "Elapased time: " << std::to_string(time) << " " << unitname << std::endl;
    }

    template <typename T, typename... Args>
    std::unordered_map<std::string, double> stats(int n_samples, const T& func, Args&&... args) {
        
        std::vector<double> samples;
        std::unordered_map<std::string, double> statistics;
        
        if (n_samples < 1) { 
            return statistics;
        }
        samples.reserve(n_samples);

        for (int i = 0; i < n_samples; i++) {
            samples.push_back(sample(func, std::forward<Args>(args)...));
        }
        std::sort(samples.begin(), samples.end());

        statistics["n_samples"] = n_samples;
        statistics["max"] = samples.back();
        statistics["min"] = samples[0];
        statistics["mean"] = std::accumulate(samples.begin(), samples.end(), 0.0) / n_samples;
        statistics["center"] = samples[samples.size() / 2];

        return statistics;
    }  
};