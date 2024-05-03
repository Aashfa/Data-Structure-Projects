# Data-Structure-Projects
**Car Maze Game**

**Description:**

This project implements a console-based maze game in C++ that offers an engaging experience for users. The game leverages graph theory to generate mazes dynamically and challenges players to navigate through the maze while avoiding obstacles and collecting power-ups.

**Introduction:**

The provided code is for a maze game implemented in C++. The game involves navigating a player character ('C') through a maze to reach the exit ('E') while avoiding obstacles ('!') and collecting power-ups ('+'). The maze is generated using a graph-based approach with nodes representing different parts of the maze.

**Code Structure:**

The code is organized into several classes to manage different aspects of the game:

- **Graph Class:** Represents the maze as a 2D grid of nodes and uses the Binary Tree Algorithm for maze generation.
- **Queue Class:** Manages a queue of obstacles with their positions and generates obstacles based on the selected difficulty level.
- **Coins Class:** Represents power-ups (coins) and manages their collection using a linked list structure.
- **Node Class:** Represents a node in the maze graph with connections for maze generation.

**Main Functions:**

- **CheckMovement(int &Score):** Handles player movement and collision detection with obstacles and power-ups.
- **StartGame(string name):** Initiates the game by creating the maze, obstacles, and power-ups.
- **MainMenu():** Displays the main menu for the user to play the game, view the leaderboard, or exit the game.

**Features:**

1. **Maze Generation:** Utilizes the Binary Tree Algorithm to generate mazes dynamically.
2. **Obstacles and Power-ups:** Obstacles ('!') are generated based on the selected difficulty level, while power-ups ('+') are randomly generated on the maze.
3. **Player Movement:** Allows the player to move ('W', 'A', 'S', 'D') within the maze and updates the player's score based on collected power-ups and penalties for hitting obstacles.
4. **Leaderboard:** Saves player names and scores to a file ('LeadersBoard.txt') after completing the game, which can be viewed from the main menu.

**User Interaction:**

- The game is navigated through the console.
- Users can input their name and select the difficulty level to play the game.
- Controls are provided to move the player character within the maze.

**Conclusion:**

- The code provides a functional maze game with features such as maze generation, player movement, obstacles, power-ups, and leaderboard tracking.
- The implementation demonstrates the use of classes, linked lists, file handling, and basic console-based user interaction.
- Further enhancements can be made to improve code readability, add features, and handle edge cases.

**Instructions:**

To run the game:
1. Compile the code using a C++ compiler.
2. Execute the compiled program.
3. Follow the on-screen instructions to navigate through the main menu, play the game, view the leaderboard, or exit.

