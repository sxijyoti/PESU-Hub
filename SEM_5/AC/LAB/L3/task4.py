import math
from collections import Counter
import secrets

def calculate_entropy(data):
    counts = Counter(data)
    length = len(data)
    probs = [count / length for count in counts.values()]
    return -sum(p * math.log2(p) for p in probs)

# Test sources
test_data = {
    'dev_random': open('/dev/random', 'rb').read(100000),
    'dev_urandom': open('/dev/urandom', 'rb').read(100000),
    'secrets': secrets.token_bytes(100000),
    'Pattern': bytes(range(64)) * (100000 // 64) + bytes(range(100000 % 64)),
    'zeros': b'\x00' * 100000
}

# Compare entropies
for name, data in test_data.items():
    entropy = calculate_entropy(data)
    print(f"{name}: Entropy = {entropy:.4f} bits/byte")
