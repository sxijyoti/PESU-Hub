import numpy as np
# Matrix A 
A = np.array([[1, 2, 3], [2, 4, 6], [4, 8, 12]])
B = np.array([5,7,9]) # Row B

print("Length of A:", len(A))  # Number of rows of A

C = np.vstack([A, B])  # A,B to create C
print("Matrix C:\n", C)

# Create D from rows 2, 3, 4 and columns 3, 4 of C
D = C[1:4, 1:3]  
print("Matrix D:\n", D)

# Transpose D to create E
E = D.T
print("Matrix E:\n", E)

# Check the size of E
print("Size of E:", E.shape)

# Equally spaced vectors
v = np.linspace(1, 10, 5)  
print("Equally spaced vector:", v)

# max and min in each column of A
print("Max in each column of A:", np.max(A, axis=0))
print("Min in each column of A:", np.min(A, axis=0))

# max and min in each row of A
print("Max in each row of A:", np.max(A, axis=1))
print("Min in each row of A:", np.min(A, axis=1))

# mean and sum in each column and row of A
print("Mean of each column in A:", np.mean(A, axis=0))
print("Sum of each row in A:", np.sum(A, axis=1))

# random matrices F and G
F = np.random.randint(1, 100, (3, 3))
print("Matrix F:\n", F)

G = np.random.randint(1, 100, (3, 3))
print("Matrix G:\n", G)

# perform scalar multiplication, addition, subtraction, and element-wise multiplication
print("F * 2:\n", F * 2)  # Scalar multiplication
print("F + G:\n", F + G)  # Matrix addition
print("F - G:\n", F - G)  # Matrix subtraction
print("Element-wise multiplication\n", np.multiply(F, G))

# size of F and A, then perform matrix multiplication if compatible
if F.shape[1] == A.shape[0]:  
    print("Matrix Multiplication:\n", np.dot(F, A))

# special matrices
identity_matrix = np.eye(3)  # 3x3 identity matrix
print("Identity Matrix:\n", identity_matrix)

zero_matrix = np.zeros((5, 3))  # 5x3 zero matrix
print("Zero Matrix:\n", zero_matrix)

one_matrix = np.ones((4, 2))  # 4x2 matrix of ones
print("One Matrix:\n", one_matrix)

diagonal_matrix = np.diag([1, 2, 7])  # Diagonal matrix
print("Diagonal Matrix:\n", diagonal_matrix)

random_matrix = np.random.randint(10, 100, (6, 6))  # 6x6 random matrix
extracted_diagonal = np.diag(random_matrix)  # Extract diagonal elements
print("Extracted Diagonal Elements:\n", extracted_diagonal)

sparse_diag_matrix = np.diag([1, 2, 3, 4])  # Sparse diagonal matrix
dense_matrix = sparse_diag_matrix.astype(float)  
print("Dense Matrix:\n", dense_matrix)
