#include <iostream>
#include "solve1.hpp"
#include "cstring"

int normalize(int x, int cap);

position calculate(position base, position velocity, int steps, int wide, int tall);

int solve1(const std::vector<bot> &bots, int wide, int tall)
{
    int maps[2][2];
    memset(maps, 0, sizeof maps);

    int matrix[wide][tall];
    memset(matrix, 0, sizeof matrix);

    for (const auto &bot: bots)
    {
        auto pos = bot.first;
        auto v = bot.second;

        auto npos = calculate(pos, v, 100, wide, tall);

        auto middle_x = wide / 2;
        auto middle_y = tall / 2;

        int hor = npos.first < middle_x;
        int ver = npos.second < middle_y;

        if (npos.first != middle_x && npos.second != middle_y)
        {
            matrix[npos.first][npos.second]++;
            maps[hor][ver]++;
        }
    }

    return maps[0][0] * maps[0][1] * maps[1][0] * maps[1][1];
}

position calculate(position base, position velocity, int steps, int wide, int tall)
{
    auto rx = base.first + steps * velocity.first;
    auto ry = base.second + steps * velocity.second;
    return std::make_pair(
        normalize(rx, wide),
        normalize(ry, tall)
    );
}

int normalize(int x, int cap)
{
    if (x >= 0)
    {
        return x % cap;
    }

    auto flip = -x;
    flip = flip % cap;
    flip = -flip + cap;
    return flip % cap;
}

