import statistics
def calcVariation(arr, start, d):
    return sum([abs(arr[i]+arr[i-1]) for i in range(start+1, start+d)])

def main():
    d,n = map(int,input().split())
    if d>n:
        return "impossible"
    tasks = list(map(int, input().split()))
    best_max = 10000000
    best_sum = 10000000
    best_indexes = []
    for i in range(0, n-d+1):
        arr = tasks[i:i+d]
        temp_max = max(arr)
        temp_sum = sum(arr)
        if temp_max < best_max:
            best_max = temp_max
            best_sum = temp_sum
            best_indexes = [i]
        elif temp_max == best_max:
            if temp_sum < best_sum:
                best_sum = temp_sum
                best_indexes = [i]
            elif temp_sum == best_sum:
                best_indexes.append(i)
    if len(best_indexes)==1: return best_indexes[0]+1
    return best_indexes[0]+1
    #min_var = 1000000
    #best_index = -1
    #for i in best_indexes:
    #    var = statistics.variance(tasks[i:i+d])
    #    if var<min_var:
    #        min_var = var
    #        best_index = i
    #return best_index+1

if __name__ == "__main__":
    print(main())