import hashlib

SIZE = 2


def getHash(x):
    hash_obj = hashlib.sha1(x.encode())
    result = hash_obj.hexdigest()[: SIZE]
    return result


def floyd(f, x0):
    # Main phase of algorithm: finding a repetition x_i = x_2i.
    # The hare moves twice as quickly as the tortoise and
    # the distance between them increases by 1 at each step.
    # Eventually they will both be inside the cycle and then,
    # at some point, the distance between them will be
    # divisible by the period λ.
    tortoise = f(f(x0))  # f(x0) is the element/node next to x0.
    hare = f(f(f(f(x0))))
    print("tortoise, hare: {},{}\n".format(tortoise, hare))
    c = 0
    while tortoise != hare:
        tortoise = f(f(tortoise))
        hare = f(f(f(f(hare))))
        print("tortoise, hare: {},{}\n".format(tortoise, hare))
        c += 1
    return
    # At this point the tortoise position, ν, which is also equal
    # to the distance between hare and tortoise, is divisible by
    # the period λ. So hare moving in circle one step at a time,
    # and tortoise (reset to x0) moving towards the circle, will
    # intersect at the beginning of the circle. Because the
    # distance between them is constant at 2ν, a multiple of λ,
    # they will agree as soon as the tortoise reaches index μ.

    # Find the position μ of first repetition.
    mu = 0
    tortoise = x0
    while tortoise != hare:
        tortoise = f(f(tortoise))
        hare = f(f(hare))   # Hare and tortoise move at same speed
        print("tortoise, hare: {},{}".format(tortoise, hare))
        mu += 1
    print("Index: {}, {}".format(c, mu))

    # Find the length of the shortest cycle starting from x_μ
    # The hare moves one step at a time while tortoise is still.
    # lam is incremented until λ is found.
#      lam = 1
    #  hare = f(tortoise)
    #  while tortoise != hare:
    #  hare = f(hare)
    #  lam += 1
#
    #  return lam, mu
#


print(floyd(getHash, "A"))
