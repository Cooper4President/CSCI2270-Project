# CSCI2270 Final Project
Centrality: A utility library for node graph centrality analysis.

## Project summary:
Summary will be updated as development progresses. Project is under development and not feature-complete.

  This library is intended to provide tools for quantifying centrality in node graphs/networks. Centrality is a measure of the 'importance' of a node within a given network. Node graph centrality algorithms are used in many applications, such as social network analytics, and Google's PageRank algorithm. The core feature of this library is to build node graphs from adjacency matrices and calculate the centrality 'scores' of each node. Functionality is included to output a network (names and connections) to a text file, in the form of an adjacency matrix. The library is also able to load data from these files. The user is able to view names and scores of all nodes in the network from within the program, as well as manually add new nodes and connections/edges. Currently implemented centrality algorithms are Eigenvector Centrality, and Degree Centrality.

TODO: Add functionality for loading in adjacency matrices from text files, and automatically building nodegraphs from the matrices.

## How to run:

Download all .cpp and .h files from "Centrality" folder, and compile. You can also download the "exampleNetwork.txt" file from the same location to aid in testing the program. CodeBlocks(with default GCC compiler) is not required, but does simplify the build process.

The recommended (easy) way to build the code is to create a new CodeBlocks 'console' project and add all the downloaded h and cpp files to it. The "main.cpp" file contains the main() entrypoint method for the program. Make sure to build the project with the 'C++11 Standard' flag enabled in compiler settings.
When the program is running, try loading the "exampleNetwork.txt" (enter name without quotes) file to test it out.

If using a different IDE and/or compiler, make sure to enable C++11 support, and take note of the information in "System Requirements" below.

## Dependencies:

No external dependencies.

## System Requirements:

No special hardware/OS requirements. Code written to be platform-neutral and should run on most modern x86/x86-64 hardware within Windows, Mac OSX, and most Linux distros.

Compiler MUST support and be set to use C++11 standard, code will not compile without it.

Project is compiled and tested with Microsoft Visual Studio compiler (in Windows 8.1) and GNU GCC compiler (in Windows 8.1 and Xubuntu Linux). Recommended to build with MSVS on Windows, and GCC on Mac & Linux. Code not tested with other compilers and may or may not build with them.

## Group Members:

Cooper Matous

## Contributors:

None at this time.

## Open issues/bugs:

None at this time.

## Ideas for new features:

- Make destructor method of NodeGraph delete all stored nodes/data/etc and free memory.
- Implement more, different algorithms for centrality calculation techniques. Algorithms already implemented: 'Eigenvector' & 'Degree'
- Add functionality to manually erase individual nodes/edges from the active network
