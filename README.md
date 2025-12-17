# Snake Byte 

## Project Overview
Snake Byte is a classic arcade-inspired Snake game developed as part of the
Structured Programming for Problem Solving (SPPS) course. The game is implemented
using the C programming language in a terminal-based environment. It focuses on
strengthening logical thinking, problem-solving skills, and structured programming
concepts through interactive gameplay.

## Objective
The objective of the game is to control a snake that grows in length as it consumes
food appearing at random positions. The game ends when the snake collides with the
wall or with its own body.

## Features
- Continuous snake movement using keyboard inputs
- Random food generation
- Score tracking as the snake consumes food
- Collision detection with walls and self
- Real-time input handling
- Modular and structured code design
- Console-based visual representation

## Technologies Used
- Programming Language: C
- Compiler: GCC / Clang
- Operating System: macOS
- Development Environment: Terminal, VS Code
- Libraries Used:
  - stdio.h
  - stdlib.h
  - time.h
  - unistd.h
  - termios.h

## System Design
The game is developed using structured programming principles:
- Game initialization and setup
- Drawing the game board and boundaries
- Real-time keyboard input handling
- Game logic for movement and collision detection
- Continuous game loop until game-over condition

Each functionality is implemented as a separate module to ensure clarity,
readability, and maintainability.

## How to Run the Project
1. Compile the program:
gcc snake_byte.c -o snake_byte
2. Run the game:
./snake_byte

## Controls
- W / A / S / D or Arrow Keys: Control snake movement
- The snake grows after consuming food
- Avoid collisions with walls and the snake’s body

## Team Members
- Sushmitha Barla (1602-24-737-185)
- Vaishnavi Medicharla (1602-24-737-187)

## Institution
Vasavi College of Engineering (Autonomous)  
Department of Information Technology  

## Conclusion
Snake Byte successfully demonstrates the application of structured programming
concepts in developing an interactive game using C. The project reinforces
modularity, logical flow control, real-time input handling, and collision detection,
making it an effective and educational software prototype.
