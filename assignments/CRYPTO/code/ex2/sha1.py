import hashlib
import time
import random

SIZE = 10


def getHash(x):
    hash_obj = hashlib.sha1(x.encode())
    result = hash_obj.hexdigest()[: SIZE]
    return result


def floyd(f, x0):
    tortoise = f(x0)  # f(x0) is the element/node next to x0.
    hare = f(f(x0))
    c = 0
    while tortoise != hare:
        tortoise = f(tortoise)
        hare = f(f(hare))
        c += 1
    tortoise = x0
    while tortoise != hare:
        last_x = tortoise
        last_y = hare
        tortoise = f(tortoise)
        hare = f(hare)   # Hare and tortoise move at same speed
    return last_x, last_y, f(last_x)


start = time.time()
print(floyd(getHash, str(random.random())))
end = time.time()
print("Time taken: {}".format(end - start))
