'''
EXERCISE 1
Given n points, each identified by its coordinates, representing the locations visited. 
Determine how many locations were visited four or more times. 
Specifically, in source file ex1.py write a Python function count_four_visits(X,Y)
taking 2 arrays: X, Y  of n numbers, each representing the x and y coordinates. 
Point Pi has coordinates (Xi, Yi). 
The function returns the number of distinct points visited four or more times. 
As a source-code comment, analyze the complexity describing a worst-case input. 
The function may not modify the input arrays X and Y [IMMUTABLE].
Hint: in Python you can define a tuple (x,y) for any two values x and y. 
A tuple is similar to an array, you can access each element by their position.
A tuple can also be compared: 
    (1,2)==(1,2) is true; 
    (1,2)==(1,3) is false; 
    and in fact (1,2)<(1,3) is true.

INPUT:
n = points
(X0, Y0), (X1, Y1), ... , (Xn-1, Yn-1) = coordinates

STRATEGY:
check same coords >= 4
steps:
    - create a new list of points
    - sort the list (mergesort)
    - count different points appearing more or equal than 4 times

COMPLEXITY: 
O(n log n) - most demanding function is the sorting, 
that in general requires n log n complexity with n being the length of the list

WORST CASE: 
In order to create the new list containing points, it will always require n time.
Also, mergesort will always require n log n complexity as all the vector,
regardless of any element being already aligned, needs to:
be split in as many sublist until 1-element sublists

OUTPUT:
r = number of places with ALGO condition
'''

def count_four_visits(X: list, Y: list) -> int:
    """
    Count points visited 4 or more times
    :param X: list[int] containing x of a point
    :param Y: list[int] containing y of a point
    :return: number of different points visited
    """
    COUNT_CONDITION = 4
    points = 0
    visited = []

    # create list of points structure (tuples)
    for i in range(len(X)):
        visited.append((X[i], Y[i]))

    # sort with merge sort implementation
    visited = mergesort(visited)
    times = 1
    previous = visited[0]

    # count different points appearing more or equal than 4 times
    # Note: counted set to false to not break Bohm Jacopini's Theorem
    counted = False
    for i in range(1, len(visited)):
        if previous == visited[i]:
            times += 1
        else:
            times = 1
            counted = False

        # count only different points
        if times >= COUNT_CONDITION and not counted:
            points += 1
            times = 0
            counted = True

        previous = visited[i]

    return points


def mergesort(l: list) -> list:
    """
    mergesort sorting algorithm function - recursive implementation
    :param l: list[int]
    :return: ordered list
    """
    # fire condition - base case recursion: partition of one single element
    if len(l) <= 1:
        return l

    # splitting list in 2 equal mid-size lists
    middle = len(l) // 2
    left = l[:middle]
    right = l[middle:]
    # get as many sublist as 1 sublists elements depth are reached
    left = mergesort(left)
    right = mergesort(right)

    # remerge the lists in an ordered way
    i = j = 0
    len_left, len_right = len(left), len(right)
    merged = []

    # from both lists, append in increasing order
    while i < len_left and j < len_right:
        if(left[i] < right[j]):
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # since one list could still have some elements:
    # if any elements from the left list are still left, append
    while i < len_left:
        merged.append(left[i])
        i += 1

    # as before, but for right list
    while j < len_right:
        merged.append(right[j])
        j += 1

    return merged


#''' TESTS
mylist = [i for i in range(1, 20) for j in range(i)]                # output: 16
myx = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 5, 5, 5]     # output: 5 times 4, result = 1
myy = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 4, 5, 6]
print(count_four_visits(myx, myy))
print(count_four_visits(mylist, mylist))
# '''
