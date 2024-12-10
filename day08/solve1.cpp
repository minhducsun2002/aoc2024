#include <bitset>
#include <numeric>
#include "solve1.hpp"
#include "unordered_map"
#include "vector"
#include "string"

typedef std::vector<std::string> matrix;
typedef std::pair<int, int> location;

inline bool is_antenna(char c)
{
    return std::isdigit(c) || std::isalnum(c);
}

inline bool in_range(const matrix& m, int row, int col)
{
    auto r = m.size();
    auto c = m[0].size();
    return row >= 0 && row < r && col >= 0 && col < c;
}

std::unordered_map<char, std::vector<location>> parse(const matrix& m)
{
    std::unordered_map<char, std::vector<location>> loc;
    for (auto row = 0; row < m.size(); row++)
    {
        for (auto col = 0; col < m[row].size(); col++)
        {
            auto c = m[row][col];
            if (is_antenna(c))
            {
                loc[c].emplace_back(row, col);
            }
        }
    }
    
    return loc;
}

void calculate(const location& p1, const location& p2, std::vector<location>& push)
{
    auto d_row = p2.first - p1.first;
    auto d_col = p2.second - p1.second;
    
    push.emplace_back(p2.first + d_row, p2.second + d_col);
    push.emplace_back(p1.first - d_row, p1.second - d_col);
}

std::vector<location> analyze(const std::vector<location>& loc)
{
    std::vector<location> out;
    auto size = loc.size();
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            if (i != k)
            {
                auto p1 = loc[i];
                auto p2 = loc[k];
                calculate(p1, p2, out);
            }
        }
    }
    
    return out;
}

int solve1(const matrix& m)
{
    std::unordered_map<char, std::vector<location>> loc = parse(m);
    
    auto map = std::vector<std::bitset<10000>>(m.size());
    for (const auto& p: loc)
    {
        auto l = p.second;
        for (const auto& out: analyze(l)) {
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