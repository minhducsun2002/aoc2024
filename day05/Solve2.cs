namespace Day5
{
    public static class Solve2
    {
        private class CustomComparer(Dictionary<int, (HashSet<int> before, HashSet<int> after)> map) : IComparer<int>
        {
            public int Compare(int x, int y)
            {
                if (map.TryGetValue(x, out var set))
                {
                    var (before, after) = set;
                    if (after.Contains(y))
                    {
                        return -1;
                    }

                    if (before.Contains(y))
                    {
                        return 1;
                    }
                }
                
                if (map.TryGetValue(y, out var set2))
                {
                    var (before, after) = set2;
                    if (before.Contains(x))
                    {
                        return -1;
                    }

                    if (after.Contains(y))
                    {
                        return 1;
                    }
                }

                return 0;
            }
        }
        
        private static int SolveConformance(List<(int, int)> rules, int[] input)
        {
            var r = input.ToDictionary(r => r, r => Solve1.GetMatchingRules(rules, r));
            var sorted = input.OrderBy(i => i, new CustomComparer(r)).ToArray();
            return sorted[sorted.Length / 2];
        }
        
        public static void Solve(List<(int, int)> rules, List<int[]> queries)
        {
            var invalid = queries.Where(q => !Solve1.Conformant(rules, q, out _)).ToList();
            var sum = invalid.Select(q => SolveConformance(rules, q)).Sum();
            Console.WriteLine(sum);
        }
    }
}