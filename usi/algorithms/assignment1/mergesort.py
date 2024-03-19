def mergesort(l: list):
    if len(l) > 1:
        middle = len(l) // 2
        left = l[:middle]
        right = l[middle:]
        mergesort(left)
        mergesort(right)

        i = j = k = 0
        left_len, right_len = len(left), len(right)

        while i < left_len and j < right_len:
            if(left[i] < right[j]):
                l[k] = left[i]
                i += 1
            else:
                l[k] = right[j]
                j += 1

            k += 1

        while i < left_len:
            l[k] = left[i]
            i += 1
            k += 1

        while j < right_len:
            l[k] = right[j]
            j += 1
            k += 1
