'''
Problem Title: The Lost Signal Reconstruction

Problem Description:
You work for a space agency that receives degraded signals from a distant spacecraft. Due to transmission limitations, only certain components of the original n-dimensional signals can be reliably recovered. Your task is to reconstruct the best possible approximation of the original signal using the available information.
The spacecraft engineers have provided k special direction vectors that characterize the recoverable subspace of the signal. You need to:

    1. Process these direction vectors to create an optimal reference frame.
    2. Use this reference frame to reconstruct the best possible approximation of the original signal.
    3. Report the reconstructed signal's coordinates.

    
Input Format:
-- The first line contains two integers n and k (1 ≤ k ≤ n ≤ 100), where n is the dimension of the signal space and k is the number of direction vectors.

-- The next k lines each contain n space-separated floating-point numbers, representing the k direction vectors.

-- The last line contains n space-separated floating-point numbers, representing the received noisy signal.


Output Format:
-- Print n space-separated floating-point numbers, representing the best possible reconstructed signal based on the given direction vectors. Display each value with 6 decimal places.


Constraints:
-- The direction vectors may not be perpendicular to each other or have unit length.

-- Some direction vectors may be redundant (providing no additional information).

-- All vector components are in the range [-1000, 1000].


Sample Test Case 1
Input

2 2
1 0
0 1
1 1

Output
1.000000 1.000000

** Explanation-
The direction vectors [1,0] and [0,1] allow for perfect reconstruction of any signal in the 2D space. The received signal [1,1] can be fully reconstructed.


Sample Test Case 2
Input

3 2
1 1 0
2 2 0
1 2 3

Output

1.500000 1.500000 0.000000

** Explanation-
The direction vectors [1,1,0] and [2,2,0] provide identical information (the second is a scaled version of the first). This means we can only reconstruct signals along a single direction in the xy-plane. The best approximation of [1,2,3] given this constraint is [1.5,1.5,0].)


Notes for Students
This problem tests your understanding of:

    1. Vector spaces and reconstruction techniques
    2. Handling redundant information
    3. Creating optimal representations of vector data
    4. Numerical computation with floating-point numbers

Your solution should efficiently process the direction vectors to create the optimal reference frame for signal reconstruction.
** Hint: An efficient approach to this problem involves creating mutually perpendicular reference vectors through a sequential process, where each new reference vector is made perpendicular to all previously constructed ones.

** Important Note **
Changes to the boilerplate code will strictly lead to zero marks. Do not modify any part of the provided function signatures, imports, or main function. Write your code only in the designated functions where "Write your code here" is indicated. Any modifications outside these designated areas will result in disqualification.
'''

import numpy as np

def create_orthogonal_basis(basis):
    """Write your code here"""
    if not basis:
        return []
    
    basis = [np.array(v) for v in basis]
    
    ortho_basis = []
    
    for v in basis:
        u = np.copy(v)
        
        for w in ortho_basis:
            
            norm_squa_w = np.dot(w, w)
            if norm_squa_w > 1e-10:  
                proj = np.dot(v, w) / norm_squa_w
                u = u - proj * w
        
        if np.linalg.norm(u) > 1e-10:
            ortho_basis.append(u)
    
    return ortho_basis
    

def compute_signal_projection(basis, signal):
    """Write your code here"""
    ortho_basis = create_orthogonal_basis(basis)
    
    reconstr_signal = np.zeros_like(signal, dtype=float)
    
    for basis_vec in ortho_basis:
        basis_norm_squa = np.dot(basis_vec, basis_vec)
        if basis_norm_squa > 1e-10:  
            proj_coeff = np.dot(signal, basis_vec) / basis_norm_squa
            reconstr_signal += proj_coeff * basis_vec
    
    return reconstr_signal
    

def main():
    n, k = map(int, input().split())
    
    basis = []
    for _ in range(k):
        vec = np.array(list(map(float, input().split())))
        basis.append(vec)
    
    signal = np.array(list(map(float, input().split())))
    
    projection = compute_signal_projection(basis, signal)
    print(' '.join([f"{x:.6f}" for x in projection]))

if __name__ == "__main__":
    main()