
# Dots and Boxes

A two-player console-based Dots and Boxes game written in C.

## Game Overview

- The game is played by two players: A and B.
- The board contains 4 rows and 5 columns of boxes.
- Players take turns connecting adjacent dots.
- A player who completes a box earns one point and gets another turn.
- The game ends when all boxes have been claimed.
- The player with the highest score wins.

## How to Play

Enter each move using four integers:

`r1 c1 r2 c2`

These represent the row and column coordinates of the two dots you want to connect.

Coordinates start at 0.

## Project Structure

```text
.
├── include/
│   ├── board.h
│   ├── display.h
│   ├── game.h
│   └── input.h
├── src/
│   ├── board.c
│   ├── display.c
│   ├── game.c
│   ├── input.c
│   └── main.c
├── Makefile
└── README.md
```

## Requirements

- GCC compiler
- Make

## Build and Run

```bash
make
./dots_and_boxes
```

## Team

Dots and Boxes

### Team members:

Mohamad Katergi

Martin Ghazal

## Evidence

### Alpine Machines

The images of the running machines and the successful process are found in /evidence_images, a folder for each team member.

### GDB and Valgrind logs

Found in docs/debugging we immediately catted the contents of gdb and valgrind commands to txt files.
