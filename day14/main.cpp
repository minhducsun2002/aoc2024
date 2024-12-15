#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "cstdio"
#include "solve1.hpp"
#include "solve2.hpp"

bot parse(std::string input);

const int wide = 101;
const int tall = 103;

int main()
{
    freopen("./input.txt", "r", stdin);

    std::vector<bot> bots;

    std::string buffer;
    while (std::getline(std::cin, buffer))
    {
        if (!buffer.empty())
        {
            bots.push_back(parse(buffer));
        }
    }

    std::cout << solve1(bots, wide, tall) << '\n' << solve2(bots, wide, tall);
}

bot parse(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), [](char c) {
        if (!isdigit(c) && c != '-') {
            return ' ';
        }
        return c;
    });

    int px, py, dx, dy;
    std::stringstream ss (input);
    ss >> px;
    ss >> py;
    ss >> dx;
    ss >> dy;
    return std::make_pair(
        std::make_pair(px, py),
        std::make_pair(dx, dy)
    );
}

