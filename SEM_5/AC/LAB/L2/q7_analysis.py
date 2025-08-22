from collections import Counter
import string

# === Ciphertext ===
ciphertext = """BFPXTRWTOW CEN BRTEWTA JNFVU E NJLNWFWJWFGV BFPXTR CXTRT TEBX QTWWTR MEPN WG  
EVGWXTR VGWFBT WXT PEWWTRV GZ WXT CGRAN WXT BGMMGV QTWWTRN GZ WXT TVUQFNX  
EQPXELTW XTQP FV ATBGAFVU E NMEQQ UJTNN EW ZFRNW WTNWFVU WXTM FV WXT WTOW  
EVA WXT RTNJQW LTBGMTN BQTERTR WXT PRGBTNN RTDTEQN WXT NTBRTW GZ WXT BGAT GVBT  
WXT MEPPFVU FN BGRRTBW WXT MTNNEUT XFAATV FN WXEW NJLNWFWJWFGV BFPXTRN ERT  
NFMPQT LJW ZRTIJTVBK EVEQKNFN MESTN WXTM CTES"""

# === Step 1: Frequency Analysis ===
clean_text = "".join(ch for ch in ciphertext.upper() if ch in string.ascii_uppercase)
letter_counts = Counter(clean_text)
total_letters = sum(letter_counts.values())

print(f"Total letters: {total_letters}\n")
print(f"{'Letter':<6}{'Count':<8}{'Frequency (%)'}")
print("-" * 30)
for letter in string.ascii_uppercase:
    count = letter_counts.get(letter, 0)
    freq = (count / total_letters * 100) if total_letters > 0 else 0
    print(f"{letter:<6}{count:<8}{freq:>6.2f}")

# === Step 2: Substitution mapping (cipher → plain) ===
substitution = {
    'A': 'd', 'B': 'c', 'C': 'w', 'D': 'v', 'E': 'a', 'F': 'i',
    'G': 'o', 'H': 'j', 'I': 'q', 'J': 'u', 'K': 'y', 'L': 'b', 'M': 'm',
    'N': 's', 'O': 'x', 'P': 'p', 'Q': 'l', 'R': 'r', 'S': 'k', 'T': 'e',
    'U': 'g', 'V': 'n', 'W': 't', 'X': 'h', 'Y': 'z', 'Z': 'f'
}

# === Step 3: Decryption function ===
def decrypt(text, mapping):
    result = ""
    for char in text:
        if char.upper() in mapping:
            plain = mapping[char.upper()]
            # Preserve case
            if char.islower():
                result += plain.lower()
            else:
                result += plain.upper()
        else:
            result += char
    return result

# === Step 4: Decrypt and print ===
plaintext = decrypt(ciphertext, substitution)

print("\n" + "="*60)
print("Decrypted Plaintext:\n")
print(plaintext)
print("="*60)
