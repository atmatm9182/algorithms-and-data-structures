var ints = Solve(100000);
foreach (var sub in ints)
{
    Console.WriteLine(string.Join(", ", sub));
}

bool IsPrime(int x)
{
    var sq = Math.Sqrt(x);

    for (int i = 2; i < sq; i++)
    {
        if (x % i == 0)
            return false;
    }

    return true;
}

int[] GenerateNums(int n)
{
    int[] ints = new int[n / 2];

    for (int i = 3; i < n; i += 2)
    {
        var idx = (i - 3) / 2;
        var val = IsPrime(i) ? i : 0;
        ints[idx] = val;
    }

    return ints;
}

IEnumerable<int[]> Solve(int n)
{
    var ints = GenerateNums(n);
    for (int i = 0; i < ints.Length - 5; i++)
    {
        if (
            ints[i + 2] == 0
            && ints[i] != 0
            && ints[i + 1] != 0
            && ints[i + 3] != 0
            && ints[i + 4] != 0
        )
        {
            yield return new int[] { ints[i], ints[i + 1], ints[i + 3], ints[i + 4] };
        }
    }
}
