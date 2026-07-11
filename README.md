# Billionaire Database Search & Analysis (Project 2 - Group 5)

## Table of Contents
- [Project Overview](#project-overview)
- [Data Source](#data-source)
- [Features & Algorithms](#features--algorithms)
- [Requirements](#requirements)
- [Build Instructions](#build-instructions)
- [Authors](#authors)
- [Running the Code](#running-the-code)
  
## Project Overview
This C++ data project compares binary tree search algorithms performances. It parses a text file entries into a Binary Search Tree sorted by net worth and contrasts Depth-First Search and Breadth-First Search execution times.

## Data Source
The application utilizes a public billionaire database from CORGIS website. The dataset (`billionaires_flat.txt`) contains detailed records of billionaires, including their name, rank, active year, company, sector, age, and net worth.

## Features & Algorithms
* **Custom Data Parser:** Reads flat text files and handles malformed rows or missing data fields.
* **Binary Search Tree (BST):** Maps `Billionaire` object nodes sorted by their `netWorth`.
* **Depth-First Search (DFS):** Recursively traverses the tree to find exact net worth matches.
* **Breadth-First Search (BFS):** Level-order traversal mapping billionaire nodes to specific tree depths.

## Requirements
* **C++ Standard:** C++17 or higher
* **Build System:** CMake 3.20+
* **Compiler:** MinGW (for Windows/CLion users) or standard GCC/Clang

## Build Instructions
The project uses CMake for cross-platform compilation. 

## Running the Code
To run this code locally using CLion, follow these steps:

1. **Open the Project:** Launch CLion and click **Open**. Select the `Project_2_Group_5` folder and choose **Open as Project**.
2. **Configure the Working Directory:** Make sure the `Project_2_Group_5` folder is showing in the executable on the top right of CLion, if not click **Edit Configurations** and find the executable.
3. **Compile and Execute:** Click the green **Play** button. The console will output the tree loading status and the search algorithm results.

## Authors
* Kian Nezamoddini-Kachouie (KianNez-K)
* Leonardo Rodrigues Fabbro (Leorf567)
* Reda Tibel (refloow-0)

