#include <fstream>
#include <cstdint>
#include <iostream>

struct intervall_t
{
    uint64_t start;
    uint64_t end;
};

struct result_t
{
    uint64_t part1;
    uint64_t part2;
};

result_t part1And2(std::ifstream &file)
{
    constexpr auto num_size = 21 + 1;
    char curr_num[num_size];

    intervall_t first = {};
    intervall_t second = {};

    result_t result = {0};

    while (file && file.peek() != EOF)
    {
        file.get(curr_num, num_size, '-');
        file.ignore(1);
        first.start = std::stoull(curr_num);

        file.get(curr_num, num_size, ',');
        file.ignore(1);
        first.end = std::stoull(curr_num);

        file.get(curr_num, num_size, '-');
        file.ignore(1);
        second.start = std::stoull(curr_num);

        // +1 incase of clrf
        file.get(curr_num, num_size + 1, '\n');
        file.ignore(1);
        second.end = std::stoull(curr_num);

        if (first.start <= second.end && second.start <= first.end)
        {
            result.part2++;

            if ((first.start >= second.start && first.end <= second.end) || (second.start >= first.start && second.end <= first.end))
            {
                result.part1++;
            }
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    std::ifstream file(argv[1]);

    const auto result = part1And2(file);
    std::cout << result.part1 << "\n";
    std::cout << result.part2 << "\n";
}
