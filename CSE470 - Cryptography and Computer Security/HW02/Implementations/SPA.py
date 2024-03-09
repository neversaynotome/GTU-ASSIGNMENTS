import struct
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

# SPARKLE-256 constants
ROUND_CONSTANTS = [
    0x06, 0x0B, 0x0F, 0x0D, 0x05, 0x08, 0x03, 0x0C,
    0x0E, 0x07, 0x01, 0x09, 0x00, 0x02, 0x0A, 0x04
]
ROTATION_CONSTANTS = [
    16, 12, 8, 7, 16, 12, 8, 7, 16, 12, 8, 7, 16, 12, 8, 7
]

# SPARKLE-256 permutation function
def sparkle256(state):
    for i in range(16):
        x, y = state[i % 12], state[(i + 16) % 12]  # Use modulo to cycle through the state
        x ^= ROUND_CONSTANTS[i]
        y = (y + x) & 0xFFFFFFFF
        y = ((y << ROTATION_CONSTANTS[i]) | (y >> (32 - ROTATION_CONSTANTS[i]))) & 0xFFFFFFFF
        x ^= y
        x = (x - y) & 0xFFFFFFFF
        state[i % 12], state[(i + 16) % 12] = x, y

# SPARKLE-256 permutation function with key and nonce absorption
def sparkle256_permute(key, nonce, block):
    # Ensure the block is 32 bytes for unpacking
    if len(block) < 32:
        block += b'\x00' * (32 - len(block))

    # Adjust the key, nonce, and block sizes to fit the state requirements
    key_nonce = key + nonce
    key_nonce_padded = key_nonce + b'\x00' * (96 - len(key_nonce))  # Padding to 96 bytes

    # Initialize the state with the key and nonce
    state = list(struct.unpack('<12Q', key_nonce_padded))

    # Absorb plaintext
    state[:4] = struct.unpack('<4Q', block)

    sparkle256(state)

    # Squeeze ciphertext
    return struct.pack('<12Q', *state)[:32]  # Return only the first 32 bytes

# SPARKLE-256 encryption with CBC mode
def sparkle256_cbc_encrypt(key, iv, plaintext):
    ciphertext = b""
    previous_block = iv

    for i in range(0, len(plaintext), 32):
        block = plaintext[i:i+32]
        if len(block) < 32:
            block = pad(block, 32)  # Padding the last block if needed
        block = bytes(x ^ y for x, y in zip(block, previous_block))

        # Applying SPARKLE permutation
        block = sparkle256_permute(key, iv, block)
        ciphertext += block
        previous_block = block

    return ciphertext


# SPARKLE-256 encryption with OFB mode
def sparkle256_ofb_encrypt(key, iv, plaintext):
    keystream = iv
    ciphertext = b""

    for i in range(0, len(plaintext), 32):
        block = plaintext[i:i+32]
        if len(block) < 32:
            block = pad(block, 32)
        keystream = sparkle256_permute(key, iv, keystream)
        ciphertext += bytes(x ^ y for x, y in zip(block, keystream))

    return ciphertext

def sparkle256_decrypt(key, nonce, ciphertext, mode):
    plaintext = b""

    if mode == 'CBC':
        previous_block = nonce
        for i in range(0, len(ciphertext), 32):
            block = ciphertext[i:i+32]
            decrypted_block = sparkle256_permute(key, nonce, block)
            plaintext_block = bytes(x ^ y for x, y in zip(decrypted_block, previous_block))
            plaintext += plaintext_block
            previous_block = block

    elif mode == 'OFB':
        keystream = nonce
        for i in range(0, len(ciphertext), 32):
            block = ciphertext[i:i+32]
            keystream = sparkle256_permute(key, nonce, keystream)
            plaintext_block = bytes(x ^ y for x, y in zip(block, keystream))
            plaintext += plaintext_block

    return plaintext

def sparkle256_encrypt_and_decrypt_demo(mode, key, nonce, plaintext):
    if mode == 'CBC':
        ciphertext = sparkle256_cbc_encrypt(key, nonce, plaintext)
        decrypted_plaintext = sparkle256_decrypt(key, nonce, ciphertext, mode)
    elif mode == 'OFB':
        ciphertext = sparkle256_ofb_encrypt(key, nonce, plaintext)
        decrypted_plaintext = sparkle256_decrypt(key, nonce, ciphertext, mode)
    else:
        raise ValueError("Invalid mode")

    print(f"SPARKLE in {mode} mode")
    print("Plaintext:", plaintext.decode('utf-8', 'replace'))  # Display as UTF-8, replace non-printable characters
    print("Key:", key.hex())
    print("Nonce:", nonce.hex())
    print("Ciphertext:", ciphertext.hex())
    print("Decrypted Plaintext:", decrypted_plaintext.decode('utf-8', 'replace'))  # Display as UTF-8, replace non-printable characters

# Example usage
key_sparkle = get_random_bytes(32)
nonce_sparkle = get_random_bytes(16)
plaintext_sparkle = b'Hello, SPARKLE!'


sparkle256_encrypt_and_decrypt_demo('CBC', key_sparkle, nonce_sparkle, plaintext_sparkle)
print(" ")
sparkle256_encrypt_and_decrypt_demo('OFB', key_sparkle, nonce_sparkle, plaintext_sparkle)