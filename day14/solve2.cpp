#include <cstring>
#include "cstdio"
#include "solve2.hpp"
#include "solve1.hpp"

int count_overlap(const std::vector<bot>& bots, int wide, int tall);

/**
 * Minimum overlapping bots
 */
int solve2(const std::vector<bot>& bots, int wide, int tall)
{
    int c = 10000; // a big number
    int min_time = 0;
    for (auto time = 0; time <= 10000; time++)
    {
        std::vector<bot> next;
        for (auto& bot: bots)
        {
            auto pos = bot.first;
            auto v = bot.second;
            auto npos = calculate(pos, v, time, wide, tall);

            next.emplace_back(npos, v);
        }

        auto nc = count_overlap(next, wide, tall);
        if (nc < c)
        {
            c = nc;
            min_time = time;
        }
    }

    return min_time;
}

int count_overlap(const std::vector<bot>& bots, int wide, int tall)
{
    std::vector<std::vector<int>> matrix(wide, std::vector<int>(tall, 0));

    int overlap = 0;

    for (const auto& bot: bots)
    {
        auto pos = bot.first;
        matrix[pos.first][pos.second] += 1;
        if (matrix[pos.first][pos.second] > 1)
        {
            overlap++;
        }
    }

    printf("found %d overlap\n", overlap);
    return overlap;
}