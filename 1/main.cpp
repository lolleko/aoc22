#include <fstream>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <array>

uint64_t part1(std::ifstream &file, std::string& line_buffer) {
    uint64_t max = 0;
    uint64_t sum = 0;
    while (std::getline(file, line_buffer)) {
        if (line_buffer.empty()) {
            sum = 0;
            continue;
        }
        sum += std::stoi(line_buffer);
        max = std::max(max, sum);
    }

    return max;
}

template<uint64_t N>
uint64_t part2(std::ifstream &file, std::string& line_buffer) {
    std::array<uint64_t, N> max = {0};
    uint64_t sum = 0;

    while (std::getline(file, line_buffer)) {
        if (line_buffer.empty()) {
            sum = 0;
            continue;
        }
        sum += std::stoi(line_buffer);

        for (int i = 0; i < N; ++i) {
            if (sum > max[i]) {
                for (int j = N - 1; j > i; --j) {
                    max[j] = max[j - 1];
                }
                max[i] = sum;
                break;
            }
        }
    }

    return std::accumulate(max.begin(), max.end(), 0);
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    
    std::string line_buffer;

    // 64bit unsigned integer has at most 20 digits + line terminator
    line_buffer.reserve(20 + 2);

    std::cout << part1(file, line_buffer) << "\n";

    file.clear();
    file.seekg(0);

    std::cout << part2<3>(file, line_buffer) << "\n";
}
