# OOP Project - SFML Game

This is a simple 2D game built for practicing object-oriented programming (OOP) principles. The game is developed in C++ using the SFML (Simple and Fast Multimedia Library). 

The game involves spawning enemies of different types, which the player can interact with by clicking on them to gain points. The game ends when the player's health reaches zero.


## Features

- **Game Engine**: Custom game engine implemented in C++.
- **Enemy Spawning**: Enemies of different sizes and colors spawn randomly.
- **Mouse Interaction**: Click on enemies to gain points.
- **Health System**: Lose health when enemies pass the bottom of the screen.
- **UI**: Displays points and health in real-time.

## Project Structure

- **`src/`**: Contains the source code for the game.
- **`resources/fonts/`**: Includes font files used in the game.
- **`.vscode/`**: Configuration files for Visual Studio Code.
- **`bin/`**: Output directory for the compiled binary.

## How to build and run

1. Clone de repository
```bash
git clone https://github.com/fernandodonea/oop-project-game1
cd oop-project-game1
```
2.Build the project using the provided Makefile:
```bash
make
```
3. Run the game:
```bash
./bin/app
```

