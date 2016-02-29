# kalah-player-agent

This repository was originally automatically exported from code.google.com/p/kalah-player-agent
It has code from Omer Levy and Mark Lukoyanichev which appears to be in response to a homework assignment in the spring of 2008 by "Mr.Hellmaker".

There is a framework to play the game of Kalah, an AlphaBeta pruning AI implementation, and three heuristics for assessing a game position.  The "simple" heuristic just counts the stone difference between the players.  The 1st and 2nd heuristics are more involved.

To build, use the "make command".

The KalahGame command runs the AlphaBeta implementation ten times, starting with each player, of one heuristic against the other, and reports on how many times each approach won or drew.

Usage:

 KalahGame [-size board-size] [-stones stones] [-time time-limit]
         -size <board size> (default: 3)
         -stones <initial stones in each house> (default: 3)
         -time <time limit per move, in seconds> (default: 0.1)

The runTest.pl script runs the framework using the AI implementations with various parameters.
It takes about 5 hours to run them all on a modern laptop.