# Recursion in Algorithms

## Overview
Recursion is a programming technique where a function calls itself to solve a problem. It breaks down a complex problem into smaller, self-similar subproblems.

A recursive function typically consists of two main parts:
1.  **Base Case**: A condition that stops the recursion. It provides a direct answer for the simplest instance of the problem, preventing infinite loops.
2.  **Recursive Step**: The part where the function calls itself with a modified argument, moving the problem closer to the base case.

```mermaid
graph TD
    Start[Function Call] --> Check{Base Case Met?}
    Check -- Yes --> Return[Return Result]
    Check -- No --> Recurse[Recursive Call]
    Recurse --> Start
```

## Typical Problems Solved with Recursion

### Factorial Calculation
Computes the product of all positive integers up to `n`.
*   **Base Case**: `n = 0` or `n = 1` (return 1)
*   **Recursive Step**: `n * factorial(n - 1)`

```mermaid
graph TD
    F5[fact 5] --> F4[fact 4]
    F4 --> F3[fact 3]
    F3 --> F2[fact 2]
    F2 --> F1[fact 1]
    F1 -- returns 1 --> F2
    F2 -- returns 2 --> F3
    F3 -- returns 6 --> F4
    F4 -- returns 24 --> F5
    F5 -- returns 120 --> Result
```

### Fibonacci Sequence
Generates the `n`-th number in the Fibonacci sequence, where each number is the sum of the two preceding ones.
*   **Base Case**: `n = 0` (return 0) or `n = 1` (return 1)
*   **Recursive Step**: `fib(n - 1) + fib(n - 2)`

```mermaid
graph TD
    Fib4[fib 4] --> Fib3[fib 3]
    Fib4 --> Fib2a[fib 2]
    Fib3 --> Fib2b[fib 2]
    Fib3 --> Fib1a[fib 1]
    Fib2a --> Fib1b[fib 1]
    Fib2a --> Fib0a[fib 0]
    Fib2b --> Fib1c[fib 1]
    Fib2b --> Fib0b[fib 0]
```

### Tree Traversal (DFS)
Visiting all nodes in a tree data structure (Pre-order, In-order, Post-order).
*   **Base Case**: Node is `null` (return)
*   **Recursive Step**: Visit node, then recursively visit left and right children.

```mermaid
graph TD
    Root((Root)) --> L((Left))
    Root --> R((Right))
    L --> LL((L.Left))
    L --> LR((L.Right))
    R --> RL((R.Left))
    R --> RR((R.Right))
```

### Tower of Hanoi
Moving a stack of disks from one rod to another, following specific rules.
*   **Base Case**: Move 1 disk directly.
*   **Recursive Step**: Move `n-1` disks to auxiliary rod, move largest disk to target, move `n-1` disks from auxiliary to target.

### Permutations of a String
Generating all possible arrangements of characters in a string.
*   **Base Case**: String is empty or length 1 (return string).
*   **Recursive Step**: Fix one character and recursively permute the rest.

### Flood Fill Algorithm
Used in graphics to determine the area connected to a given node in a multi-dimensional array (like the "bucket" tool in paint programs).
*   **Base Case**: Pixel is out of bounds or not the target color.
*   **Recursive Step**: Change color, then recurse on 4 neighboring pixels (up, down, left, right).
