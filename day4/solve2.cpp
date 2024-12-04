#include "solve2.h"
bool process2(matrix& m, int col, int line);
int solve2(matrix& m)
{
    auto max_lines = m.size();
    auto max_col = m[0].size();

    int cc = 0;
    
    for (auto line = 0; line < max_lines; line++) {
        for (auto col = 0; col < max_col; col++) {
            cc += process2(m, col, line);
        }
    }
    
    return cc;
}

bool process2(matrix& m, int col, int line)
{
    char current = m[line][col];
    if (current != 'A') return false;
    
    // a.b
    // .X.
    // c.d
    char a = ' ', d = ' ', b = ' ', c = ' ';
    access(m, col - 1, line - 1, &a);
    access(m, col + 1, line + 1, &d);

    access(m, col + 1, line - 1, &b);
    access(m, col - 1, line + 1, &c);
    
    return (
        ((a == 'M' && d == 'S') || (a == 'S' && d == 'M'))
          &&
        ((b == 'M' && c == 'S') || (b == 'S' && c == 'M'))
    );
}