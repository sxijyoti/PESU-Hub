import numpy as np
from scipy.io import loadmat

file_path = "L5/Scores.mat"
data = loadmat(file_path)

# Extract A 
A = np.array(data['Scores'], dtype=float)  

# Define b 
b = np.sum(A, axis=1)  

# Big 12 College Football Teams
teams = [
    "Texas", "Kansas State", "Oklahoma", "Baylor",
    "Iowa State", "Texas Tech", "TCU", "West Virginia",
    "Oklahoma State", "Kansas"
]

# Gaussian Elimination Function
def gaussian_elimination(A, b):
    n = len(b)

    for i in range(n):
        max_row = i + np.argmax(np.abs(A[i:n, i]))
        A[[i, max_row]] = A[[max_row, i]]
        b[[i, max_row]] = b[[max_row, i]]

        pivot = A[i, i]
        A[i] /= pivot
        b[i] /= pivot

        for j in range(i + 1, n):
            factor = A[j, i]
            A[j] -= factor * A[i]
            b[j] -= factor * b[i]

    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = b[i] - np.dot(A[i, i + 1:], x[i + 1:])

    return x

# Solve Ax = b using GEM
rankings = gaussian_elimination(A.copy(), b.copy())

# Sort Rankings
sorted_indices = np.argsort(rankings)[::-1]
sorted_teams = [(teams[i], rankings[i]) for i in sorted_indices]

# Final Rankings
print("\nBig 12 College Football Rankings (2016-2017) ")
for rank, (team, score) in enumerate(sorted_teams, 1):
    print(f"{rank}. {team}: {score:.2f}")
