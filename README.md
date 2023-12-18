# Overview

The Boggle Solver is a program that finds all valid words on a Boggle board. 
The Boggle board is a 4x4 grid with 16 dice, each displaying a letter. Players 
form words by connecting adjacent letters horizontally, vertically, or 
diagonally. This repository includes a Dictionary class, implemented as a 
prefix tree, to store and look up words efficiently. Additionally, there is 
a Boggle Solver that uses recursive backtracking to find all words on a given 
Boggle board.

> **Boggle Game:** https://www.youtube.com/watch?v=BJAdXnGAb7k

This project is broken into two parts. The first part of the program will 
be creating a dictionary that can be used to store and look up words.  This 
dictionary implementation will use a special tree called a prefix tree.

# Part A: Dictionary
### **Basic_Dictionary.cpp**
The Basic_Dictionary.cpp file contains the implementation of the Dictionary
class. This class uses a prefix tree (Trie) to store and retrieve
words efficiently.
### **Dictionary Structure**
* Each node in the Trie has 26 pointers corresponding to letters ('a' to 'z').
* Each node has a boolean flag, isWord, indicating whether the path from the 
root to that node forms a valid word.
* The Dictionary class includes essential functions like the default 
constructor, copy constructor, assignment operator, destructor, and methods
for loading and saving the dictionary from/to a file.
### **How to Use the Dictionary**
* The Dictionary class can be used to store words efficiently and check if
  a given string is a valid word or prefix.
> **Trie visualization:** https://www.cs.usfca.edu/~galles/visualization/Trie.html
# Part B: Boggle Solver
### **solve_boggle.cpp**
The Basic_Boggle_Solver.cpp file provides a basic Boggle Solver framework 
to test and develop the Boggle solving algorithm.
### **Boggle Solver Class**
* The Boggle class uses the Dictionary to solve Boggle boards.
* The default constructor initializes the dictionary with words from dictionary.txt.
* The SetBoard function sets the Boggle board.
* The PrintBoard function prints the Boggle board with proper formatting.
* The SolveBoard function finds all words on the board using recursive backtracking.
* The SaveSolve function saves the found words to a file
### **Recursion Strategy**
* The Boggle Solver uses recursive backtracking to explore all possible paths on the Boggle board.
* The SolveBoard function serves as a wrapper for the recursive SolveBoardHelper function.
* The algorithm checks each position on the board and explores all paths starting from that position.
