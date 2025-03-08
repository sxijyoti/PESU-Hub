import numpy as np

A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b = np.array([5, 7, 9])

# method 1

x = np.linalg.solve(A, b)
print(x)

r = np.dot(A, x) - b
print("\nResidual vector(r):")
print(r)

# method 2

import scipy.linalg

P,L, U = scipy.linalg.lu(A)
x1 = np.linalg.solve(A,b)
err1 = np.dot(A,x1) - b

print("\nPermutation Matrix P:")
print(P)
print("\nLower Triangular Matrix L:")
print(L)    
print("\nUpper Triangular Matrix U:")   
print(U)
print("\nSolution x:")
print(x1)
print("Error through A=PLU:")
print(err1)

# method 3
y =np.linalg.lstsq(A,b,rcond=None)[0]
print("\nSolution y:")
print(y)

# method 4

A_inv = np.linalg.inv(A)
x2 = np.dot(A_inv, b)
r2 = np.dot(A, x2) - b
err2 = x - x2

print("\nSolution vector x2 using inverse:")
print(x2)
print("\nResidual vector r2:")
print(r2)
print("\nError through inverse:")
print(err2)

# method 5

def rref(A):
    A = A.astype(float)
    m,n = A.shape
    lead = 0
    for r in range(m):
        if lead >= n:
            break
        if A[r,lead] == 0:
            for i in range(r+1,m):
                if A[i,lead] != 0:
                    A[[r,i]] = A[[i,r]]
                    break
        if A[r,lead] != 0:
            A[r] = A[r] / A[r,lead]
        for i in range(m):
            if i != r:
                A[i] = A[i] - A[i,lead] * A[r]
        lead += 1
    return A

print(A)
print(b)
C=np.hstack((A,b.reshape(-1,1)))
print("\n[A:b] vector",C)
R=rref(C)
x3 = R[:,-1]
r3=np.dot(A,x3)-b
err3=x-x3   
print("\nSolution vector x3 using rref:")
print(x3)
print("\nResidual vector r3:")
print(r3)
print("\nError through rref:")
print(err3)