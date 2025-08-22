import numpy as np

def text_to_numbers(t):
    return [ord(char.upper()) - ord('A') for char in t if char.isalpha()]

def numbers_to_text(num):
    return ''.join([chr(n + ord('A')) for n in num])

plaintext = input("Enter plaintext: ")

key_input = input("Enter 2x2 key matrix: ")
key_numbers = list(map(int, key_input.strip().split()))
key = np.array(key_numbers).reshape(2,2)

plainnum = text_to_numbers(plaintext)

if len(plainnum) % 2 != 0:
    plainnum.append(ord('X') - ord('A'))

ciphernum = []
for i in range(0, len(plainnum), 2):
    block = np.array(plainnum[i:i+2])
    encrypted = np.dot(key, block) % 26
    ciphernum.extend(encrypted)

ciphertext = numbers_to_text(ciphernum)
print("Ciphertext:", ciphertext)
