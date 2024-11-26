def selectionsort(arr):                      # custo vezes
    n = len(arr)                             # c1   1
    for i in range(n - 1):                   # c2   n
        min = i                              # c3   n - 1
        for j in range(i+1, n):              # c4   somatorio de i=1 ate n - 1 de (n - t(i) + 1)
            if arr[j] < arr[min]:            # c5   somatorio de i=1 ate n - 1 de (n - t(i))
                min = j                      # c6   somatorio de i=1 ate n - 1 de (n - t(i))
        arr[i], arr[min] = arr[min], arr[i]  # c7   n - 1
    return arr                               # c8   1


selectionsort([5,4,3,2,1])
