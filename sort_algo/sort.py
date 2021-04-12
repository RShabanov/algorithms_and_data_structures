#!/usr/bin/python3

from smoothsort import smoothsort
import matplotlib.pyplot as plt
from random import shuffle
from time import time


# Основная процедура
def main():
    smoothsort_times = []
    data_sizes = list(range(1, 21))
    for i in data_sizes:
        data = list(range(i))
        shuffle(data)
        start_time = time()
        smoothsort(data)
        smoothsort_times.append(time() - start_time)
    
    plot(data_sizes, smoothsort_times, "Smoothsort");
    

def plot(x, y, title):
    plt.title(title)
    plt.bar(x, y)
    plt.xlabel("Data size")
    plt.ylabel("Time")
    plt.show()


main()
