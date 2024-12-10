#include "vector"
#include "iostream"
#include "string"
#include "cstdio"
#include "solve1.hpp"
#include "solve2.hpp"

typedef std::vector<std::string> matrix;

int main()
{
    freopen("./input.txt", "r", stdin);
    matrix m;
    
    std::string buffer;
    while (std::getline(std::cin, buffer))
    {
        if (!buffer.empty())
        {
            m.push_back(buffer);
        }
    }
    
    std::cout << solve1(m) << '\n' << solve2(m);
}
