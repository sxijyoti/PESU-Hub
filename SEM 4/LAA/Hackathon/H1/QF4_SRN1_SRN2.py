"""
1. Gauss-Jordan Inverse Calculation
Problem Statement
Given a square matrix A, apply the Gauss-Jordan elimination method to transform it into an augmented matrix [U∣C], where:
U is the row echelon form of A.
C is the identity matrix transformed alongside A.
Tasks:
Apply Gauss-Jordan elimination to transform A into RREF (Row-Reduced Echelon Form).
Extract the transformed identity matrix as A^{-1}.
Print U, C, and A^{-1} explicitly.
 Note: The input matrix is always invertible (rank(A)=n), so A^{-1} always exists.

Concepts Used
Gauss-Jordan Elimination
Augmented Matrices
Matrix Inversion

Input Format
The first line contains one integer n, representing the size of the square matrix A (i.e., n×n).
The next n lines contain n space-separated numbers, representing the elements of matrix A.
 Note: The matrix is always invertible, so an inverse exists.

Output Format
First, print "U =" followed by the row echelon form of A.
Then, print "C =" followed by the transformed identity matrix.
Finally, print "A^-1 =" followed by the inverse of A.

Constraints
2≤n≤100(A is always square)
−1000≤A[i][j]≤1000
A is always invertible (full-rank, no singular matrices).

Sample Test Case 1 (Basic 2×2 Inversion)
Input

2
2 -1
1 3

Expected Output
U =
1.0 0.0
0.0 1.0

C =
0.4 0.1
-0.1 0.3

A^-1 =
0.4 0.1
-0.1 0.3

Explanation
The inverse exists because rank(A)=2.
The row echelon form is computed via Gauss-Jordan elimination.
C is transformed from the identity matrix.

Sample Test Case 2 (Larger 3×3 System)
Input

3
3 1 2
4 2 1
1 2 3

Expected Output

U =
1.0 0.0 0.0
0.0 1.0 0.0
0.0 0.0 1.0

C =
0.3 0.1 -0.2
-0.8 0.5 0.4
0.5 -0.4 0.2

A^-1 =
0.3 0.1 -0.2
-0.8 0.5 0.4
0.5 -0.4 0.2

Explanation
A is non-singular, so an inverse exists.
The row echelon form is the identity matrix, confirming correctness.
C is transformed into A^{-1}


Python Code
"""
import numpy as np

def gauss_jordan_inverse(A):
    """
    Perform Gauss-Jordan elimination on A to compute its inverse.

    Args:
        A (numpy.ndarray): A square matrix of size n x n.

    Returns:
        tuple: (U, C, A_inv) where:
               U is the row echelon form of A.
               C is the transformed identity matrix.
               A_inv is the computed inverse of A.
    """
    n = A.shape[0]
    
    # Create augmented matrix [A|I]
    # Combine A with identity matrix
    augmented = np.hstack((A.astype(float), np.eye(n)))
    
    # perform gaussian elimination
    for i in range(n):
        # find pivot
        max_element = abs(augmented[i:, i]).argmax() + i
        
        # swap rows when necessary
        if max_element != i:
            augmented[[i, max_element]] = augmented[[max_element, i]]
        
        # make pivot = 1
        pivot = augmented[i, i]
        augmented[i] /= pivot
        
        # eliminate other rows
        for j in range(n):
            if i != j:
                factor = augmented[j, i]
                augmented[j] -= factor * augmented[i]
    
    # split augmented matrix
    U = augmented[:, :n]  # first n cols
    C = augmented[:, n:]  # last n cols
    A_inv = C  # Inverse
    
    return U, C, A_inv

# Boilerplate code to handle input and output
def main():
    # Read input
    n = int(input().strip())  # Read matrix size
    A = np.array([list(map(float, input().split())) for _ in range(n)])  # Read matrix

    # Perform Gauss-Jordan elimination
    U, C, A_inv = gauss_jordan_inverse(A)

    # Print results
    print("U =")
    for row in U:
        print(" ".join(f"{x:.1f}" for x in row))

    print("\nC =")
    for row in C:
        print(" ".join(f"{x:.1f}" for x in row))

    print("\nA^-1 =")
    for row in A_inv:
        print(" ".join(f"{x:.1f}" for x in row))

if __name__ == "__main__":
    main()



