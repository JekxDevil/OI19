import queue


def ex100(l: list):
    tuples = []
    for i in range(0, len(l), 2):
        tuples.append((l[i], l[i+1]))
    print(f"append -> {tuples}")
    tuples.sort()
    print(f"sorted -> {tuples}")
    result = [tuples[0]]
    k = 0
    for j in range(1, len(tuples)):
        if result[k][1] >= tuples[j][0]:
            a = result[k][0]
            b = result[k][1] if result[k][1] >= tuples[j][1] else tuples[j][1]
            result.pop()
            result.append((a, b))
        else:
            result.append((tuples[j]))
            k += 1

    return result
#//////////////////////////////////////////////////////////////////////////////////////


def ex102(myl, k):
    # remove an element from list in On^2 , now On
    swap = False
    for i in range(len(myl)):
        if myl[i] == k:
            swap = True

        if swap and i < len(myl)-1:
            myl[i] = myl[i+1]
    return myl[:-1]
#//////////////////////////////////////////////////////////////////////////////////////

def insertionsort(l):
    # purposely not in place
    A = l.copy()
    for i in range(len(A)):
        j = i - 1
        while j >= 0 and A[j] > A[j+1]:
            A[j], A[j+1] = A[j+1], A[j]
            j -= 1
    return A
#//////////////////////////////////////////////////////////////////////////////////////


def mergesort(l):
    if len(l) <= 1:
        return l

    middle = len(l) // 2
    left = l[:middle]
    right = l[middle:]
    left = mergesort(left)
    right = mergesort(right)

    i = j = 0
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
#//////////////////////////////////////////////////////////////////////////////////////


def binarysearch(myl, k):
    start = 0
    end = len(myl) - 1
    while start <= end:
        middle = (start + end) // 2
        if myl[middle] == k:
            return True
        elif myl[middle] < k:
            start = middle + 1
        else:
            end = middle - 1
    return False
#//////////////////////////////////////////////////////////////////////////////////////


def ex103(myl):
    index = 0
    for i in range(10):
        for j in range(len(myl)):
            if myl[j] % 10 == i:
                myl[index], myl[j] = myl[j], myl[index]
                index += 1

    return myl
#//////////////////////////////////////////////////////////////////////////////////////


def ex114(A):
    minx = A[0][0]
    maxx = A[0][0]
    miny = A[0][1]
    maxy = A[0][1]
    for i in range(len(A)):
        if minx > A[i][0]:
            minx = A[i][0]
        if maxx < A[i][0]:
            maxx = A[i][0]
        if miny > A[i][1]:
            miny = A[i][1]
        if maxy < A[i][1]:
            maxy = A[i][1]

    return (minx, miny), (maxx, maxy)


'''def ex115(A, x):
    mymax = 0
    for i in range(len(A)):
        counter = 0
        for j in range(i, len(A)):
            if (abs(A[i][0] - A[j][0]) <= x and abs(A[i][1] - A[j][1])
                and abs(A[i][0] - A[j][1]) <= x and abs(A[][] - A[]) ):
                counter += 2
        if mymax < counter:
            mymax = counter

    return mymax'''


def ex116(A):
    maxl = A[0]
    for i in range(len(A)):
        if maxl < A[i]:
            maxl = A[i]
    return maxl


def twowaymerge(A, B):
    i = 0
    j = 0
    result = []
    while i < len(A) and j < len(B):
        if A[i] < B[j]:
            result.append(A[i])
            i += 1
        else:
            result.append(B[j])
            j += 1

    while i < len(A):
        result.append(A[i])
        i += 1

    while j < len(B):
        result.append(B[j])
        j += 1
    return result


def threewaymerge(A, B, C):
    ab = twowaymerge(A, B)
    return twowaymerge(ab, C)


def ex117sort(myl):
    if len(myl) <= 2:
        return myl

    pivot = len(myl) // 3
    first = myl[:pivot]
    second = myl[pivot: pivot*2]
    third = myl[pivot*2:]
    first = ex117sort(first)
    second = ex117sort(second)
    third = ex117sort(third)
    return threewaymerge(first, second, third)


def direction_abc(a: list, b: list, c: list):
    d = (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])
    if d > 0:
        return -1
    elif d == 0:
        return 0
    else:
        return 1


def ex118(points):
    '''
    segments = []
    for i in range(len(points)-1):
        segments.append(((points[i]), (points[i+1])))

    if direction(segments[i][0], segments[i][1])
    add modulus'''
    for i in range(0, len(points) - 1):
        for j in range(0, len(points) - 1):
            if ((direction_abc(points[i], points[i+1], points[j]) == 1
                 and direction_abc(points[i], points[i+1], points[j+1]) == -1)
                    or (direction_abc(points[i], points[i + 1], points[j]) == -1
                        and direction_abc(points[i], points[i + 1], points[j+1]) == 1)):
                return False
    return True


def ex214(myl):
    result = []
    min1 = myl[0]
    for i in range(len(myl)):
        if min > myl[i]:
            min = myl[i]


    return result


class BST:
    class Node:
        def __init__(self, key, parent=None, left=None, right=None):
            self.parent = parent
            self.key = key
            self.left = left
            self.right = right

        def __str__(self):
            return f'{self.key}'

    def __init__(self):
        self.root = None

    def insert_all(self, values):
        for x in values:
            self.insert(x)

    def insert(self, x):
        newnode = BST.Node(x)
        parent = None
        node = self.root
        while node is not None:
            parent = node
            if newnode.key <= node.key:
                node = node.left
            else:
                node = node.right
        newnode.parent = parent
        if parent is None:
            self.root = newnode
        else:
            if newnode.key <= parent.key:
                parent.left = newnode
            else:
                parent.right = newnode

    def delete(self, x):
        parent = x.parent

        # root deletion
        if parent is None:
            self.root = None
            return

        # leaf deletion
        if x.left is None and x.right is None:
            if parent.left == x:
                parent.left = None
            else:
                parent.right = None

        # 2 children deletion - find successor, copy key and delete successor recursively which must have only 1 child
        if x.left is not None and x.right is not None:
            suc = BST.successor(x)
            val = suc.key
            self.delete(suc)
            x.key = val
            return

        # 1 child deletion
        if x.left is not None:
            # only left child
            x.left.parent = parent
            if parent.left == x:
                parent.left = x.left
            else:
                parent.right = x.left
            return
        else:
            # only right child
            x.right.parent = parent
            if parent.left == x:
                parent.left = x.right
            else:
                parent.right = x.right
            return

    def search(self, x):
        node = self.root
        while node is not None:
            if x == node.key:
                return node

            if x < node.key:
                node = node.left
            else:
                node = node.right
        return node

    @staticmethod
    def successor(x):
        if x.right is not None:
            x = x.right
            x = BST.min(x)
            return x
        else:
            it = x.parent
            while not it.left == x and it is not None:
                x = it
                it = x.parent
            return it

    @staticmethod
    def predecessor(x):
        original = x
        if x.left is not None:
            x = x.left
            x = BST.max(x)
            return x
        else:
            it = x.parent
            while not it.right == x and it is not None:
                x = it
                it = x.parent
            return it

    def increasing_walk(self, node=None):
        if node is None:
            node = self.root
            print('[', end='')

        if node.left is not None:
            self.increasing_walk(node.left)

        print(f'{node.key} ', end='')

        if node.right is not None:
            self.increasing_walk(node.right)

        if node == self.root:
            print(']')

    @staticmethod
    def min(node):
        """ O(n), OHM(logn) """
        while node.left is not None:
            node = node.left
        return node if node is not None else None

    @staticmethod
    def max(node):
        """ O(n) , OHM(logn)"""
        while node.right is not None:
            node = node.right
        return node if node is not None else None

    @staticmethod
    def rrotate(node):
        l = node.left
        node.left = l.right
        if l.right is not None:
            l.right.parent = node
        l.right = node
        l.parent = node.parent
        if l.parent is not None:
            if l.parent.left.key == node.key:
                l.parent.left = l
            else:
                l.parent.right = l
        node.parent = l
        return l

    @staticmethod
    def lrotate(node):
        r = node.right
        node.right = r.left
        if r.left is not None:
            r.left.parent = node
        r.left = node
        r.parent = node.parent
        if r.parent is not None:
            if r.parent.left.key == node.key:
                r.parent.left = r
            else:
                r.parent.right = r
        node.parent = r
        return r

    def root_insert(self, key):
        self.root = BST.root_insertion(self.root, key)

    @staticmethod
    def root_insertion(tree, key, parent=None):
        if tree is None:
            node = BST.Node(key, parent)
            if parent is not None:
                if key <= parent.key:
                    parent.left = node
                else:
                    parent.right = node
            return node

        if key <= tree.key:
            tree.left = BST.root_insertion(tree.left, key, tree)
            return BST.rrotate(tree)
        else:
            tree.right = BST.root_insertion(tree.right, key, tree)
            return BST.lrotate(tree)


class MyRBTree:
    class Node:
        def __init__(self, key=None, parent=None, left=None, right=None, color=False):
            # sentinel has no key, no parent, no left, no right, and its color is black (False)
            self.key = key
            self.parent = parent
            self.left = left
            self.right = right
            self.color = color

        def is_sentinel(self):
            return (self.key is None
                    and self.parent is None
                    and self.left is None
                    and self.right is None
                    and self.color is False)

        def is_root(self):
            return self.parent.is_sentinel() or self.root == self.nil

        def is_leaf(self):
            return self.right.is_sentinel() and self.left.is_sentinel()

    def __init__(self):
        self.nil = MyRBTree.Node()
        self.root = self.nil

    def __str__(self):
        # bfs
        tree_string = ''
        node = self.root
        if node == self.nil:
            return tree_string

        q = queue.Queue()
        q.put(node)
        while not q.empty():
            if not node.left.is_sentinel():
                tree_string += f'{node.key} -> {node.left.key}\n'
                q.put(node.left)
            if not node.right.is_sentinel():
                tree_string += f'{node.key} -> {node.right.key}\n'
                q.put(node.right)
            node = q.get()
        return tree_string

    @staticmethod
    def bh(node):
        leaves = []
        q = queue.Queue()
        if not node.is_sentinel():
            q.put(node)

        # bfs(|V| + |E|)
        while not q.empty():
            n = q.get()
            if n.is_leaf():
                leaves.append(n)

            if not n.left.is_sentinel():
                q.put(n.left)
            if not n.right.is_sentinel:
                q.put(n.right)

        # count black correspondence - up scaling, particular dfs
        blacks = set()
        for l in leaves:
            sum = 0
            while not l.is_root():
                if not l.color:
                    sum += 1
                l = l.parent
            if sum not in blacks:
                blacks.add(sum)

        return blacks.pop() if len(blacks) == 1 else None

    def insert(self, key):
        node = self.root
        parent = self.nil
        while not node == self.nil:
            parent = node
            if key <= node:
                node = node.left
            else:
                node = node.right
        newnode = MyRBTree.Node(key=key, parent=parent)
        if parent == self.nil:
            self.root = newnode
        elif newnode.key <= parent.key:
            parent.left = newnode
        else:
            parent.right = newnode
        newnode.left = self.nil
        newnode.right = self.nil
        newnode.color = True
        self.insert_correct(newnode)

    def insert_correct(self, z):
        while z.parent.color:
            # is node parent a left child?
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right   # get uncle
                if y.color:
                    z.parent.color = False
                    y.color = False
                    z.parent.parent.color = True
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        MyRBTree.lrotate(z)
                    z.parent.color = False
                    z.parent.parent.color = True
                    MyRBTree.rrotate(z.parent.parent)
            else:
                y = z.parent.parent.left # get uncle
                if y.color:
                    z.parent.color = False
                    y.color = False
                    z.parent.parent.color = True
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        z = z.parent
                        MyRBTree.rrotate(z)
                    z.parent.color = False
                    z.parent.parent.color = True
                    MyRBTree.lrotate(z.parent.parent)

        self.root.color = False     # keep 1 rule

    @staticmethod
    def lrotate(rbt, x):
        r = x.right                     # 1
        x.right = r.left                # 2
        if not x.right.is_sentinel():   # 3
            x.right.parent = x          # 4
        r.left = x                      # 11
        r.parent = x.parent             # 5
        x.parent = r                    # 12
        if x.parent.is_sentinel():      # 6
            rbt.root = r                # 7
        elif r.parent.left == x:        # 8
            r.parent.left = r           # 9
        else:                           # 10
            r.parent.right = r          # 10

    @staticmethod
    def rrotate(rbt, x):
        l = x.left
        x.left = l.right
        if not l.right.is_sentinel():
            l.right.parent = x
        l.parent = x.parent
        if x.parent.is_sentinel():
            rbt.root = l
        elif x == x.parent.left:
            x.parent.left = l
        else:
            x.parent.right = l
        l.right = x
        x.parent = l

    def search(self, key):
        node = self.root
        while not node == self.nil:
            if node.key == key:
                return node

            if key < node.key:
                node = node.left
            else:
                node.right
        return None


def topological_sort(graph: list, map_name: dict):
    mystack = []
    discovery = [-1] * len(graph)
    finish = [-1] * len(graph)
    time = 0
    for i in range(len(graph)):
        if discovery[i] == -1:
            dfs(graph, map_name, i, discovery, finish, mystack, time)

    return [map_name[mystack.pop()] for i in range(len(mystack))]


def dfs(graph: list, map_name: dict, node: int, discovery: list, finish: list, mystack: list, time: int):
    discovery[node] = time
    time += 1
    for i in graph[node]:
        if discovery[i] == -1:
            dfs(graph, map_name, i, discovery, finish, mystack, time)

    finish[node] = time
    time += 1
    mystack.append(node)


def MST_Kruskal(graph: list, weights: list):
    T = []
    sets = []
    # MAKE-SET: create a set foreach vertex in the graph
    for i in range(len(graph)):
        s = set()
        s.add(i)
        sets.append(s)
    # sort edges
    E = []
    for idxfrom, edgs in enumerate(graph):
        for idxto, edge in enumerate(edgs):
            E.append((idxfrom, edge, weights[idxfrom][idxto]))
    E.sort(key=lambda edge: edge[2])

    # foreach edge if
    for (u, v, we) in E:
        s1 = find_set(sets, u)
        s2 = find_set(sets, v)
        if s1 is not s2:            # find(x) != find(y) then add to T and merge sets
            T.append((u, v, we))
            T.append((v, u, we))
            if len(s1) < len(s2):
                sets.remove(s1)
                for el in s1:
                    s2.add(el)
            else:
                sets.remove(s2)
                for el in s2:
                    s1.add(el)

    # reconvert to graph
    T.sort(key=lambda edge: edge[0])
    tree = [[] for _ in range(len(graph))]
    for (u, v, we) in T:
        tree[u].append(v)
    return tree


def find_set(sets: set, x: int) -> set:
    found = None
    for s in sets:
        if x in s:
            found = s
    return found


def MST_Prim(graph: list, weights: list):
    # set tree start, temp weights, and temp parents
    T = [[] for _ in range(len(graph))]
    W = [-1] * len(graph)
    P = [-1] * len(graph)

    # set start node as the first discovered: node 0, with its edges and weights in the pool, and W = 0
    u = 0
    pool = [(0, node, weights[0][idxnode]) for idxnode, node in enumerate(graph[0])]
    for (nodeinit, nodeto, we) in pool:
        W[nodeto] = we
        P[nodeto] = nodeinit
    W[u] = 0

    # while the minimal spanning tree is not completed (some nodes are not reached by an edge)
    while not is_spanning_tree(T):
        # get min edge from pool among unreached nodes
        u = min_edge(T, pool, weights, P, W)
        # add edge to T
        T[u].append(P[u])
        T[P[u]].append(u)
        # add edges from u to pool
        for idx, edge in enumerate(graph[u]):
            pool.append((u, edge, weights[u][idx]))

        # delete reached edges()
        delete_reached_edges(T, pool)
        # for each node reached by u, update its W if weight can be better and parent if so, too
        for idx, neighbor in enumerate(graph[u]):
            if len(T[neighbor]) == 0 and (weights[u][idx] < W[neighbor] or W[neighbor] == -1):
                W[neighbor] = weights[u][idx]
                P[neighbor] = u
    return T


def delete_reached_edges(T, pool):
    idxtodelete = []
    for idx, (v, u, edgeweight) in enumerate(pool):
        if len(T[v]) > 0 and len(T[u]) > 0:
            del pool[idx]


def min_edge(tree: list, pool: list, weights: list, P: list, W: list):
    node = None
    min_weight = None
    idx = None
    for tmpidx, (nodefrom, nodeto, edgeweight) in enumerate(pool):
        if min_weight is None and len(tree[nodeto]) == 0:
            node = nodeto
            min_weight = edgeweight
            idx = tmpidx
        elif min_weight is not None and len(tree[nodeto]) == 0:
            if edgeweight < min_weight:
                node = nodeto
                min_weight = edgeweight
                idx = tmpidx

    if node is not None:
        pool.remove(pool[idx])
    return node


def is_spanning_tree(T: list):
    # if some nodes are not reached by an edge return false
    for edgs in T:
        if len(edgs) == 0:
            return False
    return True


def ex164(nums: list):
    n = len(nums)
    B = [0] * n
    nums.sort()
    for i in range(n-3):
        j = i + 1
        k = i + 2
        while k < n:
            if nums[i] + nums[j] == nums[k]:
                B[k] = 1
                k += 1
            elif nums[i] + nums[j] < nums[k]:
                j += 1
            else:
                k += 1

    minimazed = []
    for i in range(n):
        if B[i] == 0:
            minimazed.append(nums[i])
    return minimazed


def ex235(matrix: list) -> bool:
    pass


# DAG assumed
def bellmanford(graph: list, nodefrom: int, nodeto: int):
    if nodefrom == nodeto:
        return 0

    dmin = 1e7
    for e, w in graph[nodefrom]:
        dnext = bellmanford(graph, e, nodeto) + w
        if dnext == 'inf':
            continue
        dmin = min(dmin, dnext) # molto meglio :D

    return dmin


def lis(nums: list) -> int:
    n = len(nums)
    dp = [None] * n
    dp[0] = 1
    for i in range(1, n):
        maximum = 1
        sequence = False
        for j in range(0, i):
            if nums[i] > nums[j] and dp[j] >= maximum:
                maximum = dp[j]
                sequence = True
        dp[i] = maximum + 1 if sequence else 1
    return max(dp)


def edit_distance(a, b, i, j):
    if i == len(a):
        return len(b) - j
    if j == len(b):
        return len(a) - i
    c = 0
    if a[i] == b[j]:
        c = 0
    else:
        c = 1
    return min(
        edit_distance(a, b, i+1, j+1) + c,  # add a word
        edit_distance(a, b, i, j + 1) + 1,       # insert
        edit_distance(a, b, i + 1, j) + 1       # delete
    )



if __name__ == '__main__':
    a = [el for el in 'lugano']
    b = [el for el in 'zurigo']
    print(edit_distance(a, b, 0, 0))
    '''
    map_names = {idx: c for idx, c in enumerate('abcdefghijkm')}
    meta_graph = [
        [(4, 1), (5, 2)],
        [(5, 1), (6, 3), (2, 1)],
        [(6, 3), (3, 2)],
        [(6, 1), (7, 2)],
        [(8, 1)],
        [(8, 1), (6, 3)],
        [(9, 2), (10, 3), (7, 1)],
        [(10, 3), (11, 3)],
        [(9, 3)],
        [],
        [(11, 1)],
        []
    ]
    adj = [[] for _ in range(len(map_names))]
    weight = [[] for _ in range(len(map_names))]
    for idxfrom, edges in enumerate(meta_graph):
        for idxto, w in edges:
            adj[idxfrom].append(idxto)
            adj[idxto].append(idxfrom)
            weight[idxfrom].append(w)
            weight[idxto].append(w)
    print(bellmanford(meta_graph, 0, len(adj)-1))
    print(lis([10, 9, 2, 5, 3, 7, 101, 18]))
    print(ex164([7, 89, 11, 88, 106, 4, 28, 71, 17]))
    a = [
        [7, 8, 3, 8, 8, 3],
        [7, 8, 3, 3, 3, 3],
        [1, 3, 3, 5, 8, 3],
        [7, 6, 3, 5, 3, 3],
        [0, 4, 3, 3, 3, 3],
        [9, 9, 1, 3, 7, 3],
    ]
    print(ex235(a))
    7 8 3 8 8 3
    7 8 3 3 3 3
    1 3 3 5 8 3
    7 6 3 5 3 3
    0 4 3 3 3 3
    9 9 1 3 7 3
    [4, 7, 11, 17, 28, 71, 88, 89, 106]
    map_names = {idx: c for idx, c in enumerate('abcdefghijkm')}
    # every edge only once, if a node has already all edges in previous iteration, then add an empty list
    meta_graph = [
        [(4, 1), (5, 2)],
        [(5, 1), (6, 3), (2, 1)],
        [(6, 3), (3, 2)],
        [(6, 1), (7, 2)],
        [(8, 1)],
        [(8, 1), (6, 3)],
        [(9, 2), (10, 3), (7, 1)],
        [(10, 3), (11, 3)],
        [(9, 3)],
        [],
        [(11, 1)],
        []
    ]
    adj = [[] for _ in range(len(map_names))]
    weight = [[] for _ in range(len(map_names))]
    for idxfrom, edges in enumerate(meta_graph):
        for idxto, w in edges:
            adj[idxfrom].append(idxto)
            adj[idxto].append(idxfrom)
            weight[idxfrom].append(w)
            weight[idxto].append(w)
    # print(adj)
    # print(weight)
    # mst = MST_Kruskal(adj, weight)
    # for idx, edges in enumerate(mst):
    #    print(map_names[idx], '->', [map_names[i] for i in edges])
    print(MST_Prim(adj, weight))
    # adjacency list of a graph
    map = {0:'cinta', 1:'pantaloni', 2:'mutande', 3:'felpa', 4:'canottiera'}
    adj = [[3], [0], [1], [], [3]]
    print(topological_sort(adj, map))
    A = [1, 100, 1, 2, 10, 12, 6, 8]
    B = [3, 7, 1, 5, 10, 12, 6, 8]
    C = [7, 62, 5, 57, 12, 39, 5, 8, 16, 48]
    print(f"ex100 = {ex100(A)}")      # [(1, 100)]
    print(f"ex100 = {ex100(B)}")      # [10, 12, 1, 8]
    print(f"ex102 = {ex102(B, 7)}")
    print(f"insertion sort {insertionsort(A)}")
    print(f"insertion sort {insertionsort(B)}")
    print(f"mergesort {mergesort(A)}")
    print(f"mergesort {mergesort(B)}")
    print(f"binarysearch true {binarysearch(mergesort(B), 12)}")
    print(f"binarysearch false {binarysearch(mergesort(B), 11)}")
    print(f"ex103 = {ex103(C)}")
    # ask for 105
    print(f"ex114 = {ex114([(0, 4), (-3, 1), (3, 1), (0, -2)])}")   # (-3, -2) (3, 4)
    #print(f"ex115 = {ex115([(-2, 0), (2, 0), (0, 2), (0, -2)], 4)}")   # 4
    #print(f"ex115 = {ex115([(-2, 0), (2, 0), (0, 2), (0, -2), (10, 10)], 4)}")   # 4
    #print(f"ex115 = {ex115([(-2, 0), (2, 0), (0, 2), (0, -2), (-1, 0), (1, 0), (0, 1), (0, -1), (10, 10)], 4)}")   # 8
    print(f"ex116 = {ex116(A)}")
    print(f"ex117 = {ex117sort(C)}")
    print(f"ex118 = {ex118([(0,0), (0,1), (1,1), (1,0)])}")
    print(f"ex118 = {ex118([(0,0), (0,1), (1,0), (1,1)])}") # n2
    print(f"ex118 = {ex118([(1,0), (1,1), (0,0), (0,1), (5, 3)])}") # n2
    print(f"ex118 = {ex118([(0,0), (0,2), (2,2), (2,0), (1, 0)])}")
    # print(f"michi = {tw_merge_sort(C)}")
    print(f"ex214 = {ex214([3, 6, 5, 1])}")
    mybst = BST()
    mybst.insert_all([12, 5, 2, 9, 4, 18, 15, 19, 13, 17])
    mybst.increasing_walk()
    print(BST.min(mybst.root).key, BST.max(mybst.root).key)
    print(mybst.search(-1), mybst.search(9), mybst.search(2), mybst.search(18))
    print(BST.successor(mybst.root).key, BST.successor(mybst.root.left).key, BST.successor(mybst.root.right).key)
    print(BST.predecessor(mybst.root).key, BST.predecessor(mybst.root.left).key, BST.predecessor(mybst.root.right).key)
    print(BST.successor(mybst.root.right.left.left).key)
    print(BST.predecessor(mybst.root.right.left.left).key)
    mybst.insert(10)
    print('to be deleted', mybst.root.left.key)
    mybst.delete(mybst.root.left)
    mybst.increasing_walk()
    print('to be deleted', BST.min(mybst.root))
    mybst.delete(BST.min(mybst.root))
    mybst.increasing_walk()
    mybst = BST()
    mybst.insert_all([15,4,1,7,5,13,6,10,9])
    mybst.increasing_walk()
    print('delete 4')
    mybst.delete(mybst.root.left)
    mybst.increasing_walk()
    mybst = BST()
    mybst.insert_all([15, 4, 1, 7, 5, 13, 6, 10, 9])
    mybst.increasing_walk()
    BST.lrotate(mybst.root.left.right)
    mybst.increasing_walk()
    mybst.root_insert(8)
    mybst.increasing_walk()
    '''
