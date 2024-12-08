#include <numeric>
#include <unordered_map>
#include <bitset>
#include "solve2.hpp"
#include "solve1.hpp"


void calculate2(const matrix& m, const location& p1, const location& p2, std::vector<location>& push)
{
    auto d_row = p2.first - p1.first;
    auto d_col = p2.second - p1.second;

    auto div = std::gcd(d_row, d_col);
    d_row /= div;
    d_col /= div;

    std::pair<int, int> start;
    start = std::make_pair(p1.first, p1.second);
    while (in_range(m, start.first, start.second))
    {
        push.emplace_back(start);
        start.first -= d_row;
        start.second -= d_col;
    }

    start = std::make_pair(p1.first, p1.second);
    while (in_range(m, start.first, start.second))
    {
        push.emplace_back(start);
        start.first += d_row;
        start.second += d_col;
    }
}

std::vector<location> analyze2(const matrix& m, const std::vector<location>& loc)
{
    std::vector<location> out;
    auto size = loc.size();
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            if (i != k)
            {
                auto p1 = loc[i];
                auto p2 = loc[k];
                calculate2(m, p1, p2, out);
            }
        }
    }

    return out;
}

int solve2(const matrix& m)
{
    std::unordered_map<char, std::vector<location>> loc = parse(m);
    auto map = std::vector<std::bitset<10000>>(m.size());
    for (const auto& p: loc)
    {
        auto l = p.second;
        for (const auto& out: analyze2(m, l)) {
            auto row = out.first;
            auto col = out.second;

            if (in_range(m, row, col))
            {
                map[row][col] = true;
            }
        }
    }

    auto result = std::accumulate(
        map.begin(), map.end(),
        0, [](const auto& curr, const auto& row) {
            return curr + row.count();
        }
    );
    
    return result;
}