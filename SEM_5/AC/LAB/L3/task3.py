import secrets
import time
import platform

# Method 1: /dev/random
s1 = time.time()
with open('/dev/random', 'rb') as f:
    keys1 = [f.read(128) for _ in range(20)]
e1 = time.time()
print("=== dev/random ===")
print("20 keys generated in", e1 - s1, "seconds")

# Method 2: /dev/urandom
s2 = time.time()
with open('/dev/urandom', 'rb') as f:
    keys2 = [f.read(128) for _ in range(20)]
e2 = time.time()
print("=== dev/urandom ===")
print("20 keys generated in", e2 - s2, "seconds")

# Method 3: Python secrets module
s3 = time.time()
keys3 = [secrets.token_bytes(128) for _ in range(20)]
e3 = time.time()
print("=== secrets module ===")
print("20 keys generated in", e3 - s3, "seconds")
