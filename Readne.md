
### My name is Ansuman Pal 
and this is my DSA project from cipher schools 
So we made a dice game using classes and methods in cpp 
It's made to be played in the terminal with a history feature 

So i made two dice games the original one being the direct one given by our teacher 

And the second one is my own version of the game where i tried to improve on the base game:

        Added a comprehensive history for the games that are being played 
        Added a recent menu to show recent game details 
        Added a way to add the history of a game to a txt file
        {
            the way random num generation works the results are very limited with the limited set of options being 6 even with two dice being only 12 
            so the result feels too close most times multiplicative way of calculation with 36 total units may feel better with more variables in this game, but this is the end result for me.
        }
        {
            More things can be added such as computer playing against human which will be the same ofc given the nature of the game so, no point in adding it i guess.
            Also tournaments could be added with achivements and save / load functionalities but they seem unnessary given the scope of the game, and the project mainly focusing on dsa.
        }
        {
            Data structures used: Vector for dynamic storage of players and game history, Struct for lightweight roll/round data containers, Pair for linking player names with rolls.
            Chosen for O(1) access, cache efficiency, and simple memory management. Time complexity: O(1) for adding rolls, O(n) for stats, O(p log p) for sorting standings.
        }
