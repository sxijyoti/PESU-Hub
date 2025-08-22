// Given a string s containing only digits, 
// return the lexicographically smallest string that can be obtained after swapping adjacent digits with the same parity at most once.
// Digits are considered to have the same parity if both are even or both are odd. 
// For example, '2' and '4' are both even and have the same parity, while '2' and '3' have different parity.
// Input: "45320" Output: "43520"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to get the lexicographically smallest string by swapping adjacent digits
void lexicographically_smallest_string(char *s) {
//Write your code here
    int i,n =strlen(s);
    for(i = 0; i < n-1; i++)
    {
        int a=s[i]-'0';
        int b=s[i+1]-'0';
        if(a%2==b%2)
        {
            if(a>b)
            {
                char temp = s[i];
                s[i]=s[i+1];
                s[i+1]=temp;
                break;
}}}}

int main() {
   char s[100];
   // Read the input string
   scanf("%s", s);
   // Process the string
   lexicographically_smallest_string(s);
   // Print the result
   printf("%s\n", s);
   return 0;
}