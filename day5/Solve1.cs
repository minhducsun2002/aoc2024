namespace Day5
{
    public static class Solve1
    {
        private const int Ignore = -1;

        public static (HashSet<int> before, HashSet<int> after) GetMatchingRules(List<(int, int)> rules, int query)
        {
            var before = new HashSet<int>();
            var after = new HashSet<int>();
            foreach (var (fi, se) in rules)
            {
                if (fi == query)
                {
                    after.Add(se);
                }

                if (se == query)
                {
                    before.Add(fi);
                }
            }
            
            return (before, after);
        }

        public static bool Conformant(List<(int, int)> rules, int[] query, out int middle)
        {
            for (var i = 0; i < query.Length; i++)
            {
                var current = query[i];
                var previous = query.ElementAtOrDefault(i - 1) == 0 ? Ignore : query[i - 1];
                var next = query.ElementAtOrDefault(i + 1) == 0 ? Ignore : query[i + 1];

                var (before, after) = GetMatchingRules(rules, current);
                
                if (previous != Ignore)
                {
                    if (before.Count != 0 && !before.Contains(previous))
                    {
                        middle = 0;
                        return false;
                    }
                }

                if (next != Ignore)
                {
                    if (after.Count != 0 && !after.Contains(next))
                    {
                        middle = 0;
                        return false;
                    }
                }
            }

            middle = query[query.Length / 2];
            return true;
        }

        public static void Solve(List<(int, int)> rules, List<int[]> queries)
        {
            var sum = 0; 
            foreach (var q in queries)
            {
                if (Conformant(rules, q, out var middle))
                {
                    sum += middle;
                }
            }
            
            Console.WriteLine(sum);
        }
    }
}