# Program 3- Koch curve

### Program Designed to create a Koch Snowflake with recursive Fractal Calls using C++ and Postscript graphical language.

## Instructions

This program has the ability to not only make a singular, recursive koch curve, but also
the entire koch snowflake. It will take in command line arguments for the starting and ending
points of an original line, and will then recursively generate bumps on teh line based on 
another given  "levels" input, which translates to the number of recursive iterations it will go 
through. The c++ file will output Postscript drawing commands, which will then be shown through opening that
Postscript output through a Ghostscrip application. This will show the output of the program 
with the given inputs.

## How it works
The program initially takes the command line inputs for starting point and ending point of the line. It will then 
calculate a third point to make the line into a perfect, equilateral triange, similar to how a bump in the line is calculated.
From here, It will parse through a vector with several points using iterators and make a bump on every singular line segment, until
the recursive calls equal the given levels input. It will then go through the vector and cout the calculated points in terms of Postscript
commands, which can be translated to a Postscript file by the user. This file can then be opened with Ghostscript, a seperate application
designed for viewing Postscript files.
