cipher_key = {
    'a': 'p', 'b': 'x', 'c': 'f', 'd': 'r', 'e': 'm', 'f': 'v', 'g': 'w',
    'h': 'a', 'i': 'y', 'j': 'o', 'k': 'd', 'l': 'i', 'm': 'u', 'n': 'e',
    'o': 'g', 'p': 'q', 'q': 's', 'r': 'c', 's': 'k', 't': 'h', 'u': 'z',
    'v': 'l', 'w': 't', 'x': 'j', 'y': 'b', 'z': 'n'
}

def encrypt(plaintext, key):
    plaintext = plaintext.lower()
    ciphertext = ""
    for char in plaintext:
        if char in key:
            ciphertext += key[char]
        else:
            ciphertext += char 
    return ciphertext

plaintext = input("Enter the plaintext: ")

ciphertext = encrypt(plaintext, cipher_key)

print("Plaintext:", plaintext)
print("Ciphertext:", ciphertext)
