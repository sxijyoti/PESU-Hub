"""
3. Traffic Congestion Analysis Using RREF and Rank-Nullity
Problem Statement
A city has 4 junctions and 6 roads, where the traffic flow is modeled by a system of linear equations.
Your task is to:
Represent the system as an augmented matrix where each row represents a junction equation.
Convert the matrix to Row-Reduced Echelon Form (RREF) to analyze traffic flow.
Compute the Rank and Nullity to determine if the system is underdetermined (i.e., multiple solutions exist).
Suggest modifications if the system is underdetermined to ensure better flow management.

Concepts Used
Row-Reduced Echelon Form (RREF)
Rank-Nullity Theorem
Solving Linear Systems

Input Format
The first line contains two integers m and n, representing the dimensions of the traffic flow matrix A.
The next m lines contain n space-separated numbers, representing the elements of matrix A.
 Note: The matrix is always full-rank (rank(A)=n), meaning no singular cases occur.
Constraints
2≤n≤100(A is a square matrix)
−1000≤A[i][j],b[i]≤1000
A is always non-singular (rank(A)=n) ensuring a unique solution exist

Output Format
First, print "RREF =" followed by the row-reduced echelon form of A.
Then, print "Rank =" followed by the rank of A.
Finally, print "Nullity =" followed by the nullity of A.

Sample Test Case 1 (Underdetermined System)
Input

3 4
1 -1 0 0
0 1 -1 0
0 0 1 -1

Expected Output
RREF =
1.0 0.0 0.0 -1.0
0.0 1.0 0.0 -1.0
0.0 0.0 1.0 -1.0

Rank = 3
Nullity = 1

Explanation
The system has 2 independent equations and 4 variables, meaning the nullity = 4 - 2 = 2.
Since nullity > 0, multiple solutions exist, meaning traffic flow is underdetermined (some roads have variable traffic).

Sample Test Case 2 (Full-Rank System)
Input

3 3
1 2 3
4 5 6
7 8 10

Expected Output

RREF =
1.0 0.0 0.0
0.0 1.0 0.0
0.0 0.0 1.0

Rank = 3
Nullity = 0

Explanation
Since rank = number of columns, the nullity = 0, meaning the system has a unique solution (fixed traffic flow).

"""
import numpy as np
from sympy import Matrix

def analyze_traffic(A):
    """
    Analyze traffic flow by computing RREF and Rank-Nullity.

    Args:
        A (numpy.ndarray): Traffic flow matrix of size m x n.

    Returns:
        tuple: (RREF, rank, nullity) where:
               RREF is the row-reduced echelon form of A.
               rank is the rank of A.
               nullity is the nullity of A.
    """
    sympy_matrix = Matrix(A)
    
    # compute row reduced echelon
    rref_matrix, pivot_columns = sympy_matrix.rref()
    
    # compute rank/pivot columns
    rank = len(pivot_columns)
    
    # compute nullity = columns - rank
    nullity = A.shape[1] - rank
    
    return np.array(rref_matrix.tolist()), rank, nullity

# Boilerplate code to handle input and output
def main():
    
    A = []
    rows, cols = map(int, input().split())  # Read dimensions of A

    for _ in range(rows):
        A.append(list(map(float, input().split())))

    A = np.array(A)

    # Perform Traffic Analysis
    RREF, rank, nullity = analyze_traffic(A)

    # Print results
    print("RREF =")
    for row in RREF:
        print(" ".join(f"{x:.1f}" for x in row))

    print("\nRank =", rank)
    print("Nullity =", nullity)

if __name__ == "__main__":
    main()


