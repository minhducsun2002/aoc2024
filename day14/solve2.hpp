#ifndef DAY14_SOLVE2_HPP
#define DAY14_SOLVE2_HPP

#include <vector>
#include "tuple"
typedef std::pair<int, int> position;
typedef std::pair<position, position> bot;
int solve2(const std::vector<bot>& bots, int wide, int tall);

#endif //DAY14_SOLVE2_HPP
