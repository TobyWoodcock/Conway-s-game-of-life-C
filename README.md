# Conway's game of life in C
Conway's game of life in C was my chosen final project for the second year programming in C module at the University of Exeter. A simple piece of code, it simulates Conway's famous [game of life](https://www.wikiwand.com/en/Conway%27s_Game_of_Life),
a cellular automata with a simple set of four rules that determines whether a given cell lives, dies, or proliferates. It is text based, using ASCII characters to model cells, and runs from an executable file. 

It simulates the game of life from a set of initial conditions based upon user input, including
- the dimension of the board on which the game is run
- the number of generations for which it is run
- and the setup of the board, allowing the user to choose
  - from a set of predefined patterns with interesting behaviour
  - or to create their own on a board with their chosen dimensions

![Menu](https://github.com/TobyWoodcock/Conway-s-game-of-life-C/assets/160004842/b06fb37c-23fd-4f17-a536-76bdf62084dd)

The latter is done via text input, with the user being able to choose how many cells they'd like to change from an empty board. After a cell is changed, the new board is displayed, 
allowing the user to see the changes they've made.


![running](https://github.com/TobyWoodcock/Conway-s-game-of-life-C/assets/160004842/f156b34f-1f02-48f1-bad0-eb7bb83b3d38)

