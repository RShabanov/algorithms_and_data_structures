#!/bin/python3

def my_hash(key, n_bits):
    return hash(key) % (1 << n_bits)


def open_file(path):
    with open(path, 'r') as file:
        return file.read().split('\n')
    

def get_collision_amount(path, n_bits):
    data = open_file(path)    
    collisions = 0
    keys = {} #  hash for hash
    for key in data:
        hash_key = my_hash(key, n_bits)
        if hash_key in keys:
            collisions += 1
        else:
            keys[hash_key] = 1
    return collisions


n_bits = None

try:
    n_bits = int(input("Enter bit amount: "))
except:
    print("Bad input - input must be an integer")
    exit()
    



print("Collision amount:", get_collision_amount('endict.txt', n_bits))
