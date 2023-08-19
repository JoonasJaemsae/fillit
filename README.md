# fillit

This project was originally made on an iMac and should work right out of the box in that environment. If you're on Windows, look into being able to run commands such as `gcc` and `make` in order to be able to compile the program. One tool to achieve this on Windows is the MinGW GNU.

## What it does

The program will try to find the smallest square that can fit all of the tetriminos that are supplied to it by way of having the program take a file containing the tetrimino pieces as an argument. Each tetrimino piece should be composed of 4 interconnected smaller pieces.

## Compiling the project

Navigate to the project directory and run the command `make` in the terminal.

## Running the project

Type the command `./fillit` that takes a file name for an argument, and supplement it with one. See the file `example` in the project directory to get an idea of how information in the file should be composed in order to be considered a valid file for the argument. The program will display `error` in the terminal if the file is not valid.

The `example` file can also be used to test the working of the program. In order to do that, run the command `./fillit example` in the terminal.
