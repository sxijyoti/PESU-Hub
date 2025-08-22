def key_mat(key):
    key = key.upper().replace("J", "I")
    mat = []
    for char in key:
        if char not in mat and char.isalpha():
            mat.append(char)
    for char in "ABCDEFGHIKLMNOPQRSTUVWXYZ":
        if char not in mat:
            mat.append(char)
    result = [mat[i:i + 5] for i in range(0, 25, 5)]
    return result


def prepare_text(plaint):
    plaint = plaint.upper().replace("J", "I").replace(" ", "")
    prepared = ""
    i = 0
    while i < len(plaint):
        if plaint[i].isalpha():
            if i + 1 < len(plaint) and plaint[i] == plaint[i + 1]:
                prepared += plaint[i] + "X"
                i += 1
            else:
                prepared += plaint[i]
        i += 1
    if len(prepared) % 2 != 0:
        prepared += "X"
    return prepared


def find_position(mat, char):
    for r, row in enumerate(mat):
        for c, val in enumerate(row):
            if val == char:
                return r, c
    return None, None


def encrypt_pair(a, b, mat):
    r1, c1 = find_position(mat, a)
    r2, c2 = find_position(mat, b)

    if r1 == r2:
        return mat[r1][(c1 + 1) % 5] + mat[r2][(c2 + 1) % 5]
    elif c1 == c2:
        return mat[(r1 + 1) % 5][c1] + mat[(r2 + 1) % 5][c2]
    else:
        return mat[r1][c2] + mat[r2][c1]


def decrypt_pair(a, b, mat):
    r1, c1 = find_position(mat, a)
    r2, c2 = find_position(mat, b)

    if r1 == r2:
        return mat[r1][(c1 - 1) % 5] + mat[r2][(c2 - 1) % 5]
    elif c1 == c2:
        return mat[(r1 - 1) % 5][c1] + mat[(r2 - 1) % 5][c2]
    else:
        return mat[r1][c2] + mat[r2][c1]


def encrypt(plaint, key):
    mat = key_mat(key)
    text = prepare_text(plaint)
    ciphert = ""
    for i in range(0, len(text), 2):
        ciphert += encrypt_pair(text[i], text[i + 1], mat)
    return ciphert, mat


def decrypt(ciphert, key):
    mat = key_mat(key)
    plaint = ""
    for i in range(0, len(ciphert), 2):
        plaint += decrypt_pair(ciphert[i], ciphert[i + 1], mat)
    return plaint


text = input("Enter the plaintext: ")
key = input("Enter the key: ")

cipher, mat = encrypt(text, key)

print("Key matrix:")
for row in mat:
    print(row)
print("Ciphertext:", cipher)

plaint = decrypt(cipher, key)
print("Decrypted text:", plaint)