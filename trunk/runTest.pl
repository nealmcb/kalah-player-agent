#!perl

@times  = (0.01, ,0.02, 0.05, 0.1, 1);
@boards = (4, 5, 6, 7);
@stones = (1, 2, 3, 4, 5, 6, 7);

for $time(@times)
{
    for $board(@boards)
    {
        for $stone(@stones)
        {
                system("KalahPlayer.exe -time $time -size $board -stones $stone");
        }
    }
}
