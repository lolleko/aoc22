#include <fstream>
#include <cstdint>
#include <iostream>
#include <array>

using lookup_array = std::array<std::array<uint64_t, 3>, 3>;

uint64_t part1And2(std::ifstream &file, const lookup_array& lookup) {
    uint64_t sum = 0;

    uint64_t opponent;
    uint64_t me_or_epected_result;

    while (file) {
        opponent = file.get() - 'A';

        // space
        file.ignore(1);

        me_or_epected_result = file.get() - 'X';

        // new line (check ahead at most 2 in case of CRLF)
        file.ignore(2, '\n');

        sum += lookup[opponent][me_or_epected_result];
    }

    return sum;
}

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);

    constexpr auto win_score = 6;
    constexpr auto draw_score = 3;
    constexpr auto rock_score = 1;
    constexpr auto paper_score = 2;
    constexpr auto scissors_score = 3;

    // TODO find numerical mapping function? does solution exist?
    // if it exists lookup is probably still faster
    constexpr lookup_array opponent_to_me_to_score = {
        {
            // rock
            // rock draw, paper win, scissors loss
            {rock_score + draw_score, paper_score + win_score, draw_score},
            // paper
            // rock loose, paper draw, scissors win
            {rock_score, paper_score + draw_score, scissors_score + win_score},
            // scissors
            // rock win, paper loss, scissors draw
            {rock_score + win_score, paper_score, scissors_score + draw_score}
        }
    };

    std::cout << part1And2(file, opponent_to_me_to_score) << "\n";

    file.clear();
    file.seekg(0);

    // TODO numerical mapping function?
    constexpr lookup_array opononent_to_expected_to_score = {
        {
            // rock
            // loose with scissors, draw with rock, win with paper
            {scissors_score, rock_score + draw_score, paper_score + win_score},
            // paper
            // loose with rock, draw with paper, win with scissors
            {rock_score, paper_score + draw_score, scissors_score + win_score},
            // scissors
            // loose with paper, draw with scissors, win with rock
            {paper_score, scissors_score + draw_score, rock_score + win_score}
        }
    };
    std::cout << part1And2(file, opononent_to_expected_to_score) << "\n";
}
