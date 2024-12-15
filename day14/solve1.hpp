#ifndef DAY14_SOLVE1_HPP
#define DAY14_SOLVE1_HPP

#include <vector>
#include "tuple"
typedef std::pair<int, int> position;
typedef std::pair<position, position> bot;
int solve1(const std::vector<bot> &bots, int wide, int tall);
position calculate(position base, position velocity, int steps, int wide, int tall);

#endif //DAY14_SOLVE1_HPP
