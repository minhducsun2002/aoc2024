using System.Text.RegularExpressions;

var raw = File.ReadAllText("./input.txt");
var lines = raw.Split(Environment.NewLine);

var rules = new List<(int, int)>();
var queries = new List<int[]>();

var q = false;
foreach (var line in lines)
{
    if (line.Trim().Length == 0)
    {
        q = true;
        continue;
    }

    if (!q)
    {
        var d = line.Split("|");
        rules.Add(
            (int.Parse(d[0]), int.Parse(d[1]))
        );
    }
    else
    {
        var d  = line.Split(",").Select(int.Parse).ToArray();
        queries.Add(d);
    }
}

Day5.Solve1.Solve(rules, queries);
Day5.Solve2.Solve(rules, queries);