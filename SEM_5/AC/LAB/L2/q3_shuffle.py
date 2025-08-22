import random
import string

alpha = list(string.ascii_lowercase)

shuffled = alpha.copy()
random.shuffle(shuffled)

print("Substitution Cipher Key:")
for og, sub in zip(alpha, shuffled):
    print(f"{og} -> {sub}")
