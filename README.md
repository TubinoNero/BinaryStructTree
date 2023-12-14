# BinaryStructTree

This is my 2020 college assignment for a subject called "Algorithms and Data Structures".

The project allows a user to create and serialize a basic family tree using the CLI. This tree is a binary tree, but unlike the examples of a standard binary tree shown on the internet, this tree is capable of storing entire structures (people in this case), not just numbers. It can serialize the data in **a human-readable text format** as well.

I thought it might be useful for other computer science students, because it's quite unique and it's hard to find anything like this on the internet. Compile at your own risk, as the program has not been tested since 2020. This is the type of content that is surely educational, but hardly fun - just like my college years.

## User features

- Print the whole family tree (obviously)

- Add people to the family tree (implicitly ancestors without any siblings) by typing their name, surname, date of birth and gender

- Modify the data of an existing person in the family tree

- Remove a person from the tree

- View the person's parents

- Load and save the tree for later

- Return a path to a person in the tree (starting from the youngest person)

- Delete the whole tree

## Features of the code

- Stores C++ structs in a binary tree

- Traverses the tree using preorder traversal

- Relatively safely deletes a node from the tree by recurrent deletion of all connected "ancestor" nodes

- Writes the tree to a readable text file by recursively writing people line by line, starting at the root of the tree - we're saving the stuff the smart and inefficient way - without any XMLs or fancy binaries!

- Reads the data from the text file by turning it into an ordered list of nodes (people) and converting it to a tree structure using BFS (breadth-first search)

- Uses destructors, so you can sleep relatively safely knowing that you have the ability to create a very large number of binary trees in one run without running out of memory

- Shows that at the 2020, I had little knowledge of object-oriented programming - the code still looks much more readable than the average Java programmer's work despite the lack of comments

- BARELY ANY EXCEPTIONS IN THE CODE! If something goes unplanned, well... Have fun!
