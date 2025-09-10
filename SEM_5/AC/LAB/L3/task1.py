import random
import time

def generate_key():
    ts = int(time.time())
    random.seed(ts)   
    key_bytes = [random.randint(0, 255) for _ in range(16)]
    key_hex = ''.join(f'{b:02x}' for b in key_bytes)
    print(f"Current Timestamp: {ts}")
    print(f"Generated Key in hex: {key_hex}\n")

generate_key()
 
