#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "solve1.h"
#include "solve2.h"

typedef std::vector<std::string> matrix;
    
int main()
{
    freopen("./input.txt", "r", stdin);
    matrix vectors;
    
    std::string buffer;
    
    while (std::getline(std::cin, buffer))
    {
        if (!buffer.empty())
        {
            vectors.push_back(buffer);
        }
    }
    
    std::cout << solve1(vectors) << '\n' << solve2(vectors);
}