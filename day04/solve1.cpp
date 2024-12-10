#include "solve1.h"
typedef std::vector<std::string> matrix;
std::string mark = "XMAS";
std::vector<std::pair<int, int>> dx_dy = std::vector<std::pair<int, int>>
    {
        std::make_pair(1, 1),
        std::make_pair(0, 1),
        std::make_pair(-1, 1),

        std::make_pair(1, -1),
        std::make_pair(0, -1),
        std::make_pair(-1, -1),

        std::make_pair(1, 0),
        std::make_pair(-1, 0),
    };

int process(matrix const& m, int col, int line);
bool dig(matrix const& m, int col, int line, int markIndex);

int process(matrix const& m, int col, int line)
{
    int cc = 0;
    for (const auto& direction: dx_dy)
    {
        auto len = mark.size();

        int ic = col, il = line;
        bool rr = true;

        for (auto i = 0 ; i < len ; i++) {
            auto res = dig(m, ic, il, i);
            rr = rr && res;
            if (!rr) break;

            ic += direction.first;
            il += direction.second;
        }
        cc += rr;
    }

    return cc;
}

bool dig(matrix const& m, int col, int line, int markIndex)
{
    char c;
    if (!access(m, col, line, &c)) {
        return false;
    }

    return c == mark[markIndex];
}

bool access(matrix const& matrix1, int col, int line, char* out)
{
    auto max_lines = matrix1.size();
    auto max_col = matrix1[0].size();

    if (line < 0 || line >= max_lines) return false;
    if (col < 0 || col >= max_col) return false;

    *out = matrix1[line][col];
    return true;
}

int solve1(matrix& vectors)
{
    auto max_lines = vectors.size();
    auto max_col = vectors[0].size();

    int cc = 0;

    for (auto line = 0; line < max_lines; line++) {
        for (auto col = 0; col < max_col; col++) {
            cc += process(vectors, col, line);
        }
    }
    
    return cc;
}
