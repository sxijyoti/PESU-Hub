/*
1. 

ComparisonCountingSort(A[0...n-1]):

for i <- 0 to n-1 do count[i] <- 0
for i <- 0 to n-1 do
    for j <- 0 to n-2 do
        if A[i] < A[j]:
            count[j] <- count[j] + 1
        else:
            count[i] <- count[i] + 1

for i <- 0 to n-1 do
    S[count[i]] <- A[i]
return S

*/