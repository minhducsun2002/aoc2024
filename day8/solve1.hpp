#ifndef DAY8_SOLVE1_HPP
#define DAY8_SOLVE1_HPP

#include <unordered_map>
#include "vector"
#include "string"
typedef std::pair<int, int> location;

typedef std::vector<std::string> matrix;
inline bool in_range(const matrix& m, int row, int col);
std::unordered_map<char, std::vector<location>> parse(const matrix& m);
int solve1(const matrix& m);

#endif //DAY8_SOLVE1_HPP
