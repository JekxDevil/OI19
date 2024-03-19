# binary search
def bs(ar: list, x: int):
    left = 0
    right = len(ar) - 1
    while left <= right:
        mid = (left + right) // 2
        if ar[mid] == x:
            return True
        elif ar[mid] < x:
            left = mid + 1
        else:
            right = mid - 1
    return False


# get_median
def get_median(a):
    return k_smallest(a, len(a)//2)


def k_smallest(a, k):
    v = a[(len(a)-1)//2]
    al = []
    av = []
    ar = []
    for el in a:
        if el < v:
            al.append(el)
        elif v == el:
            av.append(el)
        else:
            ar.append(el)
    if k < len(al):
        return k_smallest(al, k)
    elif k > len(al) + len(av):
        return k_smallest(ar, k-len(al)-len(av))
    return v


# mergesort
def mergesort(a):
    if len(a) == 1:
        return a
    left = mergesort(a[:len(a)//2])
    right = mergesort(a[len(a)//2:])
    i = 0 
    j = 0
    result = []
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
        
    while i < len(left):
        result.append(left[i])
        i += 1
        
    while j < len(right):
        result.append(right[j])
        j += 1
        
    return result


def quicksort(A, l=None, r=None):
    if l is None and r is None:
        l = 0
        r = len(A) - 1

    if l is not None and r is not None and l < r:
        q = partition(A, l, r)
        quicksort(A, l, q - 1)
        quicksort(A, q + 1, r)
    return A


def partition(A, l, r) -> int:
    pivot = A[r]
    for i in range(l, r):
        if A[i] <= pivot:
            A[i], A[l] = A[l], A[i]
            l += 1
    A[r], A[l] = A[l], A[r]
    return l


# 255
def cuso(ar):
    i = 0
    while i < len(ar) - 1:
        j = i + 1
        while j < len(ar):
            if ar[i] == ar[j]:
                i += 1
                ar[i], ar[j] = ar[j], ar[i]
            j += 1
        i += 1
    return ar


def simpleselectionsort(A):
    for i in range(len(A)):
        for j in range(i, len(A)):
            if A[j] < A[i]:
                A[i], A[j] = A[j], A[i]
    return A


def insertionsort(A):
    for i in range(1, len(A)):
        j = i - 1
        value = A[i]
        while j >= 0 and A[j] > value:
            A[j], A[j + 1] = A[j + 1], A[j]
            j -= 1
    return A


import math
from io import StringIO
#source https://bit.ly/38HXSoU
def show_tree(tree, total_width=60, fill=' '):
    """Pretty-print a tree.
    total_width depends on your input size"""
    output = StringIO()
    last_row = -1
    for i, n in enumerate(tree):
        if i:
            row = int(math.floor(math.log(i+1, 2)))
        else:
            row = 0
        if row != last_row:
            output.write('\n')
        columns = 2**row
        col_width = int(math.floor((total_width * 1.0) / columns))
        output.write(str(n).center(col_width, fill))
        last_row = row
    print (output.getvalue())
    print ('-' * total_width)
    return


def build_min_heap(A):
    heap = []
    for el in A:
        show_tree(heap_insert(heap, el))
        print(check_minheap(heap), heap)
    return heap


def heap_insert(A, el):
    index = len(A)
    A.append(el)
    parent = (index - 1) // 2
    while index > 0 and A[index] < A[parent]:
        A[parent], A[index] = A[index], A[parent]
        index = parent
        parent = (index - 1) // 2
    return A


def extract_min(A):
    if len(A) == 0:
        return None

    min = A[0]
    A[0] = A[len(A) - 1]
    A.pop()
    min_heapify(A)
    print(check_minheap(A), A)
    show_tree(A)
    return A


def min_heapify(A):
    index = 0
    lc = index * 2 + 1
    rc = index * 2 + 2
    while index < len(A) and lc < len(A) and rc < len(A):
        if A[index] > A[lc] or A[index] > A[rc]:
            if A[lc] < A[rc]:
                A[index], A[lc] = A[lc], A[index]
                index = lc
            else:
                A[index], A[rc] = A[rc], A[index]
                index = rc
            lc = index * 2 + 1
            rc = index * 2 + 2
        else:
            return A
    return A


def check_minheap(A, index=0):
    LIMIT = len(A)
    lc = index * 2 + 1
    rc = index * 2 + 2
    if lc < LIMIT:
        if A[lc] < A[index]:
            return False
        else:
            return True and check_minheap(A, lc)
    if rc < LIMIT:
        if A[rc] < A[index]:
            return False
        else:
            return True and check_minheap(A, rc)
    return True


class MyMinHeap:
    def __init__(self):
        self.heap = []
        self.length = len(self.heap)

    def __str__(self):
        return str(self.heap)

    # interface
    @staticmethod
    def get_parent(child):
        if child <= 0: return 0
        return (child - 1) // 2

    @staticmethod
    def get_lchild(parent):
        return parent * 2 + 1

    @staticmethod
    def get_rchild(parent):
        return parent * 2 + 2

    # general usage
    @staticmethod
    def build_heap(ar):
        heap = MyMinHeap()
        for el in ar:
            heap.insert(el)
        return heap

    def insert(self, el):
        index = self.length
        self.length += 1
        self.heap.append(el)
        parent = MyMinHeap.get_parent(index)
        while self.heap[index] < self.heap[parent]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            index = parent
            parent = MyMinHeap.get_parent(index)

    def extract(self):
        if self.is_empty():
            raise "error"
        self.length -= 1
        self.heap[0], self.heap[-1] = self.heap[-1], self.heap[0]
        self.heapify()
        return self.heap.pop()

    def heapify(self, i=0):
        lc = MyMinHeap.get_lchild(i)
        rc = MyMinHeap.get_rchild(i)
        if lc < self.length and self.heap[lc] < self.heap[i]:
            minidx = lc
        else:
            minidx = i
        if rc < self.length and self.heap[rc] < self.heap[minidx]:
            minidx = rc

        if not minidx == i:
            self.heap[i], self.heap[minidx] = self.heap[minidx], self.heap[i]
            self.heapify(minidx)

    def is_empty(self):
        return len(self.heap) == 0

    def print(self):
        show_tree(self.heap)

    @staticmethod
    def check_minheap(h, index=0):
        LIMIT = h.length
        lc = MyMinHeap.get_lchild(index)
        rc = MyMinHeap.get_rchild(index)

        if lc < LIMIT:
            if h.heap[index] < h.heap[lc]:
                return True and MyMinHeap.check_minheap(h, lc)
            else:
                return False

        if rc < LIMIT:
            if h[index] < h[rc]:
                return True and MyMinHeap.check_minheap(h, rc)
            else:
                return False
        return True


class MyStack:
    def __init__(self):
        self.stack = []

    def is_empty(self):
        return len(self.stack) == 0

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        if not self.is_empty():
            return self.stack.pop()


class MyQueue:
    def __init__(self, size=10):
        self.queue = [0] * size
        self.size = size
        self.head = 0
        self.tail = 0
        self.elements = 0

    def __str__(self):
        i = self.head
        j = (self.tail - 1) % self.size
        ar = []
        while not i == j:
            ar.append(self.queue[i])
            i = (i + 1) % self.size
        ar.append(self.queue[i])
        return str(ar)

    def enqueue(self, el):
        if self.elements == self.size:
            raise "overflow"

        self.queue[self.tail] = el
        self.tail = (self.tail + 1) % self.size
        self.elements += 1

    def dequeue(self):
        if self.elements == 0:
            raise "underflow"

        element = self.queue[self.head]
        self.head = (self.head + 1) % self.size
        self.elements -= 1
        return element


class MyDoubleLinkedList:
    class Node:
        def __init__(self, key=None, prv=None, nxt=None):
            if key is None:
                self.prev = self
                self.next = self
            else:
                self.prev = prv
                self.next = nxt
            self.key = key

    def __init__(self):
        self.sentinel = self.Node()

    def __str__(self):
        ar = []
        node = self.sentinel.next
        while node != self.sentinel:
            ar.append(node.key)
            node = node.next
        return str(ar)

    # interface
    def insert(self, el):
        last = self.sentinel.prev
        el.next = self.sentinel
        el.prev = last
        last.next = el
        self.sentinel.prev = el

    def delete(self, el):
        """ Accept only already created and in-list nodes """
        if el == self.sentinel:
            return False

        bef = el.prev
        aft = el.next
        bef.next = aft
        aft.prev = bef
        return True

    def search(self, el):
        node = self.sentinel.next
        while node != self.sentinel:
            if node.key == el.key:
                return node
            node = node.next
        return None


if __name__ == '__main__':
    # print(bs([1, 2, 3, 4, 5, 6, 7, 8], 7))
    # print(get_median([1, 2, 3, 4, 5, 6, 7, 8]))
    # print(mergesort([6,5,4,3,2,1,0]))
    # print(quicksort([6, 5, 4, 3, 2, 1, 0], 0, 6))
    # print(quicksort([6, 5, 4, 1, 100, 200]))
    # print(insertionsort([6, 5, 400, 3, 2, 1, 0]))
    # print(cuso([el for el in "antoniocarzaniga"]))
    '''
    print(
        extract_min(
            extract_min(
                build_min_heap([6, 2, 5, 3, 4, 10, 20, 30, 40, 1, 0, 50, 60, 70, 80, 90, 100])
            )
        )
    )
    
    stack = MyStack()
    stack.push(3)
    stack.push(5)
    print(stack.pop() == 5)
    myheap = MyMinHeap()
    myheap.insert(50)
    print(MyMinHeap.check_minheap(myheap))
    myheap.insert(10)
    print(MyMinHeap.check_minheap(myheap))
    myheap.insert(3)
    print(MyMinHeap.check_minheap(myheap))
    myheap.insert(1)
    print(MyMinHeap.check_minheap(myheap))
    myheap.print()
    myheap.extract()
    myheap.print()
    print(MyMinHeap.check_minheap(myheap))
    myheap2 = MyMinHeap.build_heap([6, 2, 5, 3, 4, 10, 20, 30, 40, 1, 0, 50, 60, 70, 80, 90, 100])
    myheap2.print()
    print(MyMinHeap.check_minheap(myheap2))
    myqueue = MyQueue(3)
    myqueue.enqueue(5)
    myqueue.enqueue(7)
    myqueue.enqueue(2)
    print(myqueue)
    myqueue.dequeue()
    print(myqueue)
    myqueue.dequeue()
    print(myqueue)
    ll = MyDoubleLinkedList()
    ll.insert(MyDoubleLinkedList.Node(3))
    print(ll)
    ll.insert(MyDoubleLinkedList.Node(5))
    print(ll)
    ll.delete(MyDoubleLinkedList.Node(3))
    print(ll)
    ll.delete(MyDoubleLinkedList.Node(5))
    print(ll)
    '''
