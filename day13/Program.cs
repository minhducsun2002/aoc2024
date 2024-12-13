using System.Text.RegularExpressions;

var f = File.ReadAllText("./input.txt");
var pieces = f.Split("\n\n");

long sum = 0;
long sum2 = 0;

foreach (var piece in pieces)
{
    var lines = piece.Split("\n").Select(a => a.Trim()).Where(a => a.Length > 0).ToArray();
    var aButton = ParseNums(lines[0]);
    var bButton = ParseNums(lines[1]);
    var prize = ParseNums(lines[2]);
    
    var res = Solve1(aButton, bButton, prize);
    if (res != -1)
    {
        sum += res;
    }

    const long diff = 10000000000000L;
    var res2 = Solve2(aButton, bButton, (prize.Item1 + diff, prize.Item2 + diff));
    if (res2 != -1)
    {
        sum2 += res2;
    }
}
Console.WriteLine(sum);
Console.WriteLine(sum2);
return;

long Solve1((long x, long y) a, (long x, long y) b, (long targetX, long targetY) prize)
{
    long min = 10000;
    for (var aCount = 0; aCount <= 100; aCount++)
    {
        for (var bCount = 0; bCount <= 100; bCount++)
        {
               var finalX = a.x * aCount + b.x * bCount;
               var finalY = a.y * aCount + b.y * bCount;
               
               if (finalX == prize.targetX && finalY == prize.targetY)
               {
                   var cost = Cost(aCount, bCount);
                   min = Math.Min(min, cost);
               }
        }
    }

    return min == 10000 ? -1 : min;
}

long Solve2((long x, long y) a, (long x, long y) b, (long targetX, long targetY) prize)
{
    // a.x_a + b.x_b = targetX
    // a.y_a + b.y_b = targetY

    // a.x_a.y_a + b.x_b.y_a = targetX.y_a
    // a.y_a.x_a + b.y_b.x_a = targetY.x_a

    // b.(x_b.y_a - y_b.x_a) = targetX.y_a - targetY.x_a
    // a = (targetX - b.x_b) / x_a

    var d1 = checked(prize.targetX * a.y) - checked(prize.targetY * a.x); // targetX.y_a - targetY.x_a
    var d2 = checked(b.x * a.y) - checked(b.y * a.x); // x_b.y_a - y_b.x_a
    
    // ensure a & b are integrals
    if (d1 % d2 != 0)
    {
        return -1;
    }
    var bCount = d1 / d2;
    
    if ((prize.targetX - checked(bCount * b.x)) % a.x != 0)
    {
        return -1;
    }
    var aCount = (prize.targetX - checked(bCount * b.x)) / a.x;
    
    // ensure a & b are positive (you can't press a button negative times!)
    if (bCount >= 0 & aCount >= 0)
    {
        return Cost(aCount, bCount);
    }
    
    return -1;
}

long Cost(long aCount, long bCount)
{
    return aCount * 3 + bCount;
}

(long, long) ParseNums(string line)
{
    var r = new Regex("(\\d+)");
    var matches = r.Matches(line);
    return (long.Parse(matches[0].Value), long.Parse(matches[1].Value));
}