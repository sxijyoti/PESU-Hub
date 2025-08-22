cipher_key = {
    'a': 'p', 'b': 'x', 'c': 'f', 'd': 'r', 'e': 'm', 'f': 'v', 'g': 'w',
    'h': 'a', 'i': 'y', 'j': 'o', 'k': 'd', 'l': 'i', 'm': 'u', 'n': 'e',
    'o': 'g', 'p': 'q', 'q': 's', 'r': 'c', 's': 'k', 't': 'h', 'u': 'z',
    'v': 'l', 'w': 't', 'x': 'j', 'y': 'b', 'z': 'n'
}

reversekey = {v: k for k, v in cipher_key.items()}

def decrypt(ciphertext, key):
    plaintext = ""
    for char in ciphertext:
        if char in key:
            plaintext += key[char]
        else:
            plaintext += char 
    return plaintext

ciphertext = input("Enter the ciphertext: ")

decrypted_text = decrypt(ciphertext, reversekey)

print("Ciphertext:", ciphertext)
print("Decrypted Text:", decrypted_text)
