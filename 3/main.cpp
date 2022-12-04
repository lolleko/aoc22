#include <fstream>
#include <cstdint>
#include <iostream>
#include <array>

uint64_t char_to_prio(const char c)
{
    return c > 'Z' ? c - 'a' + 1 : c - 'A' + 27;
}

constexpr uint64_t FIRST_BIT = 1;

uint64_t encode_string(const std::string_view &str)
{

    uint64_t result = 0;
    for (auto &&c : str)
    {
        const auto n = char_to_prio(c);

        result |= (FIRST_BIT << n);
    }

    return result;
}

uint64_t part1(std::ifstream &file)
{
    uint64_t sum = 0;

    std::string line;

    while (std::getline(file, line))
    {
        const auto first = std::string_view(line).substr(0, line.size() / 2);
        const auto second = std::string_view(line).substr(line.size() / 2, line.size() / 2);

        assert(first.size() == second.size());

        uint64_t first_encoded = encode_string(first);

        for (auto &&c : second)
        {
            const auto n = char_to_prio(c);

            if ((first_encoded & (FIRST_BIT << n)) != 0)
            {
                sum += n;

                break;
            }
        }
    }

    return sum;
}

uint64_t part2(std::ifstream &file)
{
    uint64_t sum = 0;

    std::string line1;
    std::string line2;
    std::string line3;

    while (std::getline(file, line1))
    {
        std::getline(file, line2);
        std::getline(file, line3);

        uint64_t first_encoded = encode_string(line1);
        uint64_t second_encoded = encode_string(line2);

        for (auto &&c : line3)
        {
            const auto n = char_to_prio(c);

            if ((first_encoded & (FIRST_BIT << n)) != 0 && (second_encoded & (FIRST_BIT << n)) != 0)
            {
                sum += n;

                break;
            }
        }
    }

    return sum;
}

int main(int argc, char *argv[])
{
    std::ifstream file(argv[1]);

    std::cout << part1(file) << "\n";

    file.clear();
    file.seekg(0);

    std::cout << part2(file) << "\n";
}
