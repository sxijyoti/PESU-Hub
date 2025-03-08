import numpy as np

# Big 12 College Football Teams (2016-2017 Season)
teams = [
    "Texas", "Kansas State", "Oklahoma", "Baylor",
    "Iowa State", "Texas Tech", "TCU", "West Virginia",
    "Oklahoma State", "Kansas"
]

# Coefficient Matrix A 
A = np.array([
    [10, -1, -1, -1, 0, 0, -1, 0, 0, 0],  # Texas
    [-1, 10, -1, 0, -1, 0, 0, 0, -1, 0],  # Kansas State
    [-1, -1, 10, 0, 0, 0, 0, -1, -1, 0],  # Oklahoma
    [-1, 0, 0, 10, -1, 0, -1, 0, 0, 0],  # Baylor
    [0, -1, 0, -1, 10, -1, 0, 0, 0, -1],  # Iowa State
    [0, 0, 0, 0, -1, 10, -1, -1, 0, -1],  # Texas Tech
    [-1, 0, 0, -1, 0, -1, 10, 0, 0, 0],  # TCU
    [0, 0, -1, 0, 0, -1, 0, 10, -1, 0],  # West Virginia
    [0, -1, -1, 0, 0, 0, 0, -1, 10, -1],  # Oklahoma State
    [0, 0, 0, 0, -1, -1, 0, 0, -1, 10]   # Kansas
], dtype=float)

# Result Vector b
b = np.array([3, 6, 10, 4, 1, 2, 5, 7, 8, 0], dtype=float)  

# Gaussian Elimination
def gaussian_elimination(A, b):
    n = len(b)
    
    # Forward Elimination
    for i in range(n):
        max_row = i + np.argmax(np.abs(A[i:n, i]))
        A[[i, max_row]] = A[[max_row, i]]
        b[[i, max_row]] = b[[max_row, i]]

        # pivot 1
        pivot = A[i, i]
        A[i] = A[i] / pivot
        b[i] = b[i] / pivot

        # eliminate values below pivot
        for j in range(i + 1, n):
            factor = A[j, i]
            A[j] -= factor * A[i]
            b[j] -= factor * b[i]

    # Back Substitution
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = b[i] - np.dot(A[i, i + 1:], x[i + 1:])

    return x

# Ax = b using GEM
rankings = gaussian_elimination(A.copy(), b.copy())

# Ranking
sorted_indices = np.argsort(rankings)[::-1]  # Sort in descending order
sorted_teams = [(teams[i], rankings[i]) for i in sorted_indices]

#Final Rankings
print("Big 12 College Football Rankings (2016-2017)")
for rank, (team, score) in enumerate(sorted_teams, 1):
    print(f"{rank}. {team}: {score:.2f}")
