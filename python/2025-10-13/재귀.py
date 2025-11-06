def f(n):
    if n == 0:
        return 1
    else:
        result = n * f(n - 1)
    return result
print(f(5))


def fibo(n):
    a = 1
    b = 1
    if n == 1 or n == 2:
        return 1
    for i in range(1, n):
        a, b = b, b + a

    return a


print(fibo(10))