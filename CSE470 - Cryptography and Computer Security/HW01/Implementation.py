import tkinter as tk
from tkinter import ttk, messagebox
import time
import random
from math import isqrt

def is_positive_integer(value):
    try:
        num = int(value)
        return num > 0
    except ValueError:
        return False

def miller_rabin(n, k=1000):
    if n == 1:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def sieve_eratosthenes(limit):
    primes = []
    is_prime = [True] * (limit + 1)
    for num in range(2, isqrt(limit) + 1):
        if is_prime[num]:
            primes.append(num)
            for multiple in range(num * num, limit + 1, num):
                is_prime[multiple] = False
    for num in range(isqrt(limit) + 1, limit + 1):
        if is_prime[num]:
            primes.append(num)
    return primes

def sieve_atkin(limit):
    is_prime = [False] * (limit + 1)
    sqrt_limit = int(isqrt(limit)) + 1

    for x in range(1, sqrt_limit):
        for y in range(1, sqrt_limit):
            n = 4 * x**2 + y**2
            if n <= limit and (n % 12 == 1 or n % 12 == 5):
                is_prime[n] = not is_prime[n]

            n = 3 * x**2 + y**2
            if n <= limit and n % 12 == 7:
                is_prime[n] = not is_prime[n]

            n = 3 * x**2 - y**2
            if x > y and n <= limit and n % 12 == 11:
                is_prime[n] = not is_prime[n]

    for i in range(5, sqrt_limit):
        if is_prime[i]:
            for j in range(i**2, limit + 1, i**2):
                is_prime[j] = False

    primes = [2, 3]
    for num in range(5, limit + 1):
        if is_prime[num]:
            primes.append(num)

    return primes

def test_primality():
    algorithm = algorithm_var.get()
    number = entry.get()

    if not is_positive_integer(number):
        messagebox.showerror("Error", "Please enter a valid positive integer.")
        return

    number = int(number)

    start_time = time.time()

    if algorithm == "Miller-Rabin":
        result = miller_rabin(number)
    elif algorithm == "Sieve of Eratosthenes":
        result = number in sieve_eratosthenes(number)
    elif algorithm == "Sieve of Atkin":
        result = number in sieve_atkin(number)
    else:
        messagebox.showerror("Error", "Invalid algorithm selected.")
        return

    elapsed_time = time.time() - start_time

    result_text = (
        f"Primality Test Results:\nAlgorithm: {algorithm}\nNumber: {number}\n"
        f"Is Prime: {result}\nElapsed Time: {elapsed_time:.6f} seconds"
    )
    messagebox.showinfo("Primality Test", result_text)

# GUI setup
root = tk.Tk()
root.title("Primality Test")

# Configure row and column weights for scaling
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)

frame = ttk.Frame(root, padding="10")
frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

# Configure row and column weights for scaling within the frame
frame.grid_rowconfigure(0, weight=1)
frame.grid_rowconfigure(1, weight=1)
frame.grid_rowconfigure(2, weight=1)
frame.grid_columnconfigure(0, weight=1)
frame.grid_columnconfigure(1, weight=1)

label_algorithm = ttk.Label(frame, text="Select Algorithm:")
label_algorithm.grid(row=0, column=0, sticky=tk.W, pady=5)

algorithm_options = ["Miller-Rabin", "Sieve of Eratosthenes", "Sieve of Atkin"]
algorithm_var = tk.StringVar(value=algorithm_options[0])

algorithm_menu = ttk.Combobox(frame, textvariable=algorithm_var, values=algorithm_options, state="readonly")
algorithm_menu.grid(row=0, column=1, sticky=(tk.W, tk.E), pady=5)

label_number = ttk.Label(frame, text="Enter a number:")
label_number.grid(row=1, column=0, sticky=tk.W, pady=5)

entry = ttk.Entry(frame)
entry.grid(row=1, column=1, sticky=(tk.W, tk.E), pady=5)

label_credentials = ttk.Label(frame, text="Siyar Tarik Ozcaner\n200104004021")
label_credentials.grid(row=2, column=0, columnspan=2, pady=5)

button = ttk.Button(frame, text="Test Primality", command=test_primality)
button.grid(row=3, column=0, columnspan=2, pady=10)

root.mainloop()
