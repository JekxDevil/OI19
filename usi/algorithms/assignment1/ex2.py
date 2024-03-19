'''
GENERAL:
worst case input: 
    all negative numbers in already sorted list because the resulting
    squared list will have to sort all elements in the list
    [-4, -3, -2, -1]

best case input: 
    all positive numbers in already sorted list because the resulting
    squared list will have already all the elements sorted so the inner while
    loop won't be triggered
    [1, 2, 3, 4]


average case input: 
    a mid way between the two cases above
    [-3, -1, 2, 7]
'''


def algox(A):
    """ ALGO-X(A) algorithm provided by exercise 2 pseudo-code.

    :param A: list[int] incresingly ordered list of numbers in Z set
    :return: ordered list
    """
    B = []
    n = len(A)

    for i in range(n):
        B.append(A[i]*A[i])

    for i in range(1, n):
        j = i - 1
        v = B[i]
        while j >= 0 and B[j] > v:
            B[j + 1] = B[j]
            j = j - 1
        B[j + 1] = v

    return B


def better_algox(A: list) -> int:
    """ 
    Sort the square of an already incresingly sorted list of numbers in Z
    :param A: list[int] incresingly ordered list of numbers in Z set
    :return: ordered list
    """
    # get squared elements in list -> O(n)
    length = len(A)
    for i in range(length):
        A[i] = A[i] ** 2

    # calculate where's the minimum element and its index -> O(n)
    # since they were ordered, just find the last decreasing number in the sequence
    orderedlist = []
    k = 1
    min_index = 0
    min_el = A[min_index]
    while min_el > A[k]:
        if A[k] < min_el:
            min_el = A[k]
            min_index = k
        k += 1

    # append all elements in incresing order -> O(n)
    tot_el = 0
    k = min_index
    j = min_index + 1
    while tot_el < length:
        if A[k] < A[j]:
            orderedlist.append(A[k])
            k = (k-1) % length
        else:
            orderedlist.append(A[j])
            j = (j+1) % length
        tot_el += 1

    return orderedlist


#'''
my1 = [-25, -16, -9, -4, 1, 4, 9, 25, 49]
my2 = [1, 4, 4, 9, 9, 16, 25, 25, 49]
my3 = [-5, -4, -3, -2, -1, 2, 3, 5, 7]
print(better_algox(my1))
print(better_algox(my2))
print(better_algox(my3))
#'''
