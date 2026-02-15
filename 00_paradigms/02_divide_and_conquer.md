# Divide and Conquer

## Overview
Divide and Conquer is an algorithmic paradigm that solves a problem by breaking it down into smaller, more manageable subproblems, solving them recursively, and then combining their solutions to solve the original problem.

## The Three Steps
Given an input, a recursively executable function, and an output:

1.  **Divide**: Break the original problem into smaller, independent subproblems that are similar to the original but smaller in size.
2.  **Conquer**: Solve the subproblems recursively. If the subproblems are small enough (base case), solve them directly.
3.  **Combine**: Merge the solutions of the subproblems to create the solution for the original problem.

```mermaid
graph TD
    P[Problem] --> SP1[Subproblem 1]
    P --> SP2[Subproblem 2]
    SP1 --> SSP1[Sub-subproblem 1.1]
    SP1 --> SSP2[Sub-subproblem 1.2]
    SP2 --> SSP3[Sub-subproblem 2.1]
    SP2 --> SSP4[Sub-subproblem 2.2]
    SSP1 --> Sol1[Sol 1.1]
    SSP2 --> Sol2[Sol 1.2]
    SSP3 --> Sol3[Sol 2.1]
    SSP4 --> Sol4[Sol 2.2]
    Sol1 --> Comb1[Combined 1]
    Sol2 --> Comb1
    Sol3 --> Comb2[Combined 2]
    Sol4 --> Comb2
    Comb1 --> Final[Final Solution]
    Comb2 --> Final
```

## Examples

### Merge Sort
Recursively divides the array into two halves, sorts them, and then merges the sorted halves.
```mermaid
graph TD
    A[8, 3, 2, 9] --> B[8, 3]
    A --> C[2, 9]
    B --> D[8]
    B --> E[3]
    C --> F[2]
    C --> G[9]
    D --> H[3, 8]
    E --> H
    F --> I[2, 9]
    G --> I
    H --> J[2, 3, 8, 9]
    I --> J
```

### Quicksort
Picks a 'pivot' element and partitions the array into sub-arrays of elements smaller and larger than the pivot.
```mermaid
graph TD
    A[5, 2, 9, 1, 6] -- Pivot: 5 --> B[2, 1]
    A -- Pivot: 5 --> C[9, 6]
    B -- Pivot: 2 --> D[1]
    B -- Pivot: 2 --> E[Empty]
    C -- Pivot: 9 --> F[6]
    C -- Pivot: 9 --> G[Empty]
    D --> H[1, 2]
    E --> H
    F --> I[6, 9]
    G --> I
    H --> J[1, 2, 5, 6, 9]
    I --> J
```

### Binary Search
Finds the position of a target value within a sorted array by repeatedly dividing the search interval in half.
```mermaid
graph TD
    A[Search 7 in 1..10] -- Mid: 5 < 7 --> B[Search 7 in 6..10]
    B -- Mid: 8 > 7 --> C[Search 7 in 6..7]
    C -- Mid: 6 < 7 --> D[Search 7 in 7..7]
    D -- Mid: 7 == 7 --> E[Found Index]
```

### Strassen Matrix Multiplication
A faster algorithm for matrix multiplication that uses fewer scalar multiplications than the standard method.
```mermaid
graph TD
    A[Matrix A] --> C[Submatrices]
    B[Matrix B] --> C
    C --> D[7 Recursive Multiplications]
    D --> E[Combine Results]
```

### Karatsuba Algorithm
A fast multiplication algorithm for large numbers that reduces the complexity from O(n^2) to O(n^log3).
```mermaid
graph TD
    A[Number X] --> C[Split High/Low]
    B[Number Y] --> C
    C --> D[3 Recursive Multiplications]
    D --> E[Combine with Shifts/Adds]
```

### Closest Pair of Points
Finds the pair of points with the smallest distance between them in a set of points in O(n log n) time.
```mermaid
graph TD
    A[Set of Points] --> B[Split by X-coordinate]
    B --> C[Left Subset]
    B --> D[Right Subset]
    C --> E[Min Dist Left]
    D --> F[Min Dist Right]
    E --> G[Check Strip Across Split]
    F --> G
    G --> H[Global Min Distance]
```

### Fast Fourier Transform (FFT)
Computes the discrete Fourier transform (DFT) of a sequence, reducing complexity from O(n^2) to O(n log n).
```mermaid
graph TD
    A[Time Domain Signal] --> B[Split Even/Odd Indices]
    B --> C[FFT of Even]
    B --> D[FFT of Odd]
    C --> E[Combine with Twiddle Factors]
    D --> E
    E --> F[Frequency Domain]
```

### Tower of Hanoi
A mathematical puzzle where the objective is to move a stack of disks from one rod to another, following specific rules.
```mermaid
graph TD
    A[Move 3 Disks A->C] --> B[Move 2 Disks A->B]
    A --> C[Move Disk 3 A->C]
    A --> D[Move 2 Disks B->C]
    B --> E[Move 1 Disk A->C]
    B --> F[Move Disk 2 A->B]
    B --> G[Move 1 Disk C->B]
    D --> H[Move 1 Disk B->A]
    D --> I[Move Disk 2 B->C]
    D --> J[Move 1 Disk A->C]
```