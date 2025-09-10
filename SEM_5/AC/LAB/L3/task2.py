import numpy as np
from datetime import datetime, timezone

# Step 1: Define the 2-hour search window in UTC

start_str = "2025-09-01 21:08:49"
end_str   = "2025-09-01 23:08:49"

start_dt = datetime.strptime(start_str, "%Y-%m-%d %H:%M:%S").replace(tzinfo=timezone.utc)
end_dt   = datetime.strptime(end_str, "%Y-%m-%d %H:%M:%S").replace(tzinfo=timezone.utc)

start_epoch = int(start_dt.timestamp())
end_epoch   = int(end_dt.timestamp())

# Step 2: Define known plaintext and target ciphertext

plaintext_hex  = "255044462d312e360a25d0d4c5d80a35"
ciphertext_hex = "1a4fffc708dfcdf68e66c262859010f8"

plaintext_bytes  = bytes.fromhex(plaintext_hex)
ciphertext_bytes = bytes.fromhex(ciphertext_hex)

# Step 3: Brute force seeds in time range

for seed in range(start_epoch, end_epoch + 1):
    bitgen = np.random.MT19937(seed)
    rng = np.random.Generator(bitgen)
    keybytes = rng.integers(0, 256, size=len(plaintext_bytes), dtype=np.uint8).tobytes()
    candidate = bytes([p ^ k for p, k in zip(plaintext_bytes, keybytes)])
    if candidate == ciphertext_bytes:
        print(f"Key={keybytes.hex()}")
        print(f"Timestamp={datetime.fromtimestamp(seed, tz=timezone.utc)}")
        break
