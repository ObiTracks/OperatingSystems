# Assignment 4 - Memory Allocation Simulation

---

# Summary
This assignment is designed to simulate the processes that pertain to memory allocation in operating systems. It simulates a pool of available memory from which memory can be assigned to and released from different processes.
---

# Make File

---

The make file provides a striaghtforward way to compile and run the program for this assignment using the necessary flags  and command line arguments

# Screenshots

---

# Individual Contribution

---

100% of the assignment was done by myself, Obi Ihej. I had no partner to help me on any of the assignments.

# Features

---

1. Request memory for processes from an available pool of 1mb:
    1. Here is the command line syntax:
        
        → <base command> <process number> <size> <allocation algorithm>
        
    
    b. Where these parameters have these options:
    
    - <base command> : RQ, RL, C, Status, Exit
    - <process number> : Any integer from 0 - 100
    - <size> : Any integer less than 1000000bytes
    - <allocation algorithm> : F (First Fit), B (Best Fit), W (Worst Fit)
2. Release memory from processes
3. Compact memory from available holes
4. Check the status of used memory in the system.

# Test Cases

---

# Use Examples

---

# About Developers

# Liscence to Use Code
    MIT Liscence
