# For the given input, perform Caesar cipher encryption and decryption.
# Plain text: “CRYPTOGRAPHY”
# Key: 10

def encryption(plaint,key):
    ciphert = ""
    for p in plaint:
        if p.isalpha():
            shift = (ord(p) - ord('A') + key) % 26
            ciphert += chr(ord('A') + shift)
        elif p.islower():
            shift = (ord(p) - ord('a') + key) % 26
            ciphert += chr(ord('a') + shift)
    return ciphert

def decryption(ciphert,key):
    plaint=""
    for c in ciphert:
        if c.isalpha():
            shift = (ord(c)-ord('A') - key) % 26
            plaint += chr(ord('A') + shift)
        elif c.islower():
            shift = (ord(c) - ord('a') - key) % 26
            plaint += chr(ord('a') + shift)
    return plaint

plaintext = input("Enter the plain text: ")
key = int(input("Enter the key: "))
ciphertext = encryption(plaintext, key)
print("Caesar Cipher text:", ciphertext)
decryptedtext = decryption(ciphertext, key)
print("Caesar Decrypted text after encryption:", decryptedtext)