cipher_key = {
    'a': 'p', 'b': 'x', 'c': 'f', 'd': 'r', 'e': 'm', 'f': 'v', 'g': 'w',
    'h': 'a', 'i': 'y', 'j': 'o', 'k': 'd', 'l': 'i', 'm': 'u', 'n': 'e',
    'o': 'g', 'p': 'q', 'q': 's', 'r': 'c', 's': 'k', 't': 'h', 'u': 'z',
    'v': 'l', 'w': 't', 'x': 'j', 'y': 'b', 'z': 'n'
}

def encrypt(text, key):
    text = text.lower()
    ciphertext = ""
    for c in text:
        if c in key:
            ciphertext += key[c]
        else:
            ciphertext += c
    return ciphertext

with open("input.txt", "r") as f:
    t = f.read()

ciphertext = encrypt(t, cipher_key)
print(ciphertext)