# Snake-Xenia
A Snake Xenia game in c, intended for project submission.

# Proof of work
The upload date and time is the proof of the uniqueness.

# Project logic
Dominant items in game to make it work are `Head of snake`, `Direction of movement` and `Fruit generation`.
`Character mattrix` has been used to formate the board with snake, fruit and walls.
Initialising step has snake in the center of board with length 2, and direction by default upward.
The `updatehead()` changes the position of head according to direction and with a recursive logic of previous segment to current, this way it ensures correct coordination of head with body and direction.
`system('cls')` is used for clear the previous output for proper formating and desired animation.
`Sleep(int time)` does the delay in loop for transition and proper visibility.
`rand%k` is used for generation of fruit's coordinate with validation that it not get formed at the borders or in the snake body.
For saving scores file handeling has been used, with `struct` paramenters namely `name` and `score` for proper bindings, to display.
`kbhit()` is a function from conio.h lib which is used to detect keytaps, it returns `1` when it detects key hit where we get the input by getc().
This entire thing works in loop, which makes cli-game clean for view and play.
Rest comments are present in code for further informations.

