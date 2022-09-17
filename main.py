from random import randrange
import numpy as np
import os

numbers_min = 0
numbers_max = 9
row_min = 5
row_max = 7+1
nmbr = 10000000
file_name = "data.txt"


def rnd():
    return randrange(row_min, row_max)


def create_data(amount=nmbr):
    # A[m,n] B[n, k]
    # колличество столбцов в матрице А должно совпадать с колличество строк в матрице В
    def create_matrix(m=None, n=None) -> np.ndarray:
        if m is None:
            m = rnd()
        if n is None:
            n = rnd()
        return np.random.randint(numbers_min, numbers_max, (m, n))

    if (os.path.exists(file_name)):
        return 0
    with open(file_name, "w") as file:
        j = rnd()
        for i in range(0, amount):
            mtrx = create_matrix(m=j)
            k, j = mtrx.shape
            file.write(f"{k} {j}\n")
            for a in range(k):
                for b in range(j):
                    file.write(f'{mtrx[a][b]} ')
            file.write("\n")


def run():
    print("Компиляция")
    os.system("clang simple/main.c -o main")
    print("Конец компиляции")

    print("Запуск")
    os.system("time ./main")
    print("Конец запуска")


if __name__ == '__main__':
    create_data()
    run()
