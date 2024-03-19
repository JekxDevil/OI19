'''
A visitor can START anywhere but must proceed from each attraction to the next along the tour,
*possibly* getting back to the START and repeating some or all attractions any number of times. [CIRCLE %]
Function total_expenditure(A,x):
    - A = array with costs of all the attractions in the tour (in order of the tour)
    - x = total expenditure
O(n) time returns true only if it is possible to spend exactly x.
Ex. if the costs are A = [10, 2, 3], then it's possible to spend 5, 20, 25, but not 24. 
total_expenditure([10,2,3], 25) == True
total_expenditure([10,2,3], 24) == False

library numpy used only for testing purposes - to verify complexity
at the end of the page there are tests.
'''
import numpy as np


def total_expenditure(A: list, x: int) -> bool:
    """ 
    States if its possible to spend exactly 'x' by going through the attractions in the order
    given by the amusement park, with the possibility to start and redo the same attraction
    in order all the times we want
    :param A: list[int] list of costs of all the attractions (in order of the tour)
    :param x: total expenditure
    :return: bool whether it is possible or not to spend exactly x
    """
    # fire condition - impossible 'x' value
    if x < 0:
        return False

    result = False
    sum_list = 0
    for i in range(len(A)):
        sum_list += A[i]

    if sum_list == 0 and x != 0:
        return False

    # cut out unnecessary cycles
    sum_tofind = x * (sum_list/x) if x > sum_list else 0
    # find the start
    i = j = 0
    while i < len(A):
        sum_tofind += A[j]

        if sum_tofind > x:
            sum_tofind -= A[i]
            i += 1

        j = (j+1) % len(A)

        if sum_tofind == x and i != j and i != len(A):
            return True

    return False


# ''' TESTS:w
Z = [0, 0, 0]
A = [1, 2, 3, 4, 5]
C = [1, 5, 7, 9, 15]
B = [7, 8]
# randlist = np.random.randint(50, 100, 1000000)
print(f'f -> {total_expenditure(C, 33)}')      # f
print(f'f -> {total_expenditure(A, -1)}')     # f
print(f't -> {total_expenditure(A, 5)}')      # t
print(f't -> {total_expenditure(A, 20)}')     # t
print(f't -> {total_expenditure(A, 8)}')      # t
print(f'f -> {total_expenditure(B, 9)}')      # f
# print(total_expenditure(randlist, 100000000))
print(f't -> {total_expenditure([0, 0, 1], 25000)}') # t

# prof's tests
print(f't -> {total_expenditure([10, 2, 3], 5)}')     # t
print(f't -> {total_expenditure([10, 2, 3], 20)}')    # t
print(f't -> {total_expenditure([10, 2, 3], 25)}')    # t
print(f'f -> {total_expenditure([10, 2, 3], 24)}')    # f
print(f'f -> {total_expenditure(Z, 1)}')
print(f'f -> {total_expenditure(A, 0)}')
# '''
