This is a C++ implementation of the game Connect 4. It manages and manipulates a game board, and is specifically tailored for games involving grid-like structures and disk dropping mechanics.

Features:
- Initialization (InitBoard): Initializes the game board with empty slots.
- Disk Dropping (DropDiskToBoard): Allows for dropping a disk into a specified column of the board.
- Diagonal Check Helpers (LeftDiagHelper, RightDiagHelper): Assist in checking for winning conditions along diagonal lines.
- Vertical Check Helper (VertHelper): Assists in checking for vertical winning conditions.
- Winning Condition Check (SearchForWinner): Searches for winning conditions in specified directions.
- Overall Winner Check (CheckForWinner): Determines if there is a winner based on the current board state.
- Board Boundaries Check (BoardLocationInBounds): Verifies if a given board location is within valid boundaries.
- Board to String Conversion (BoardToStr): Converts the current state of the board to a string representation.
- String Centering (CenterStr): Centers a given string within a specified column width, useful for display formatting.
