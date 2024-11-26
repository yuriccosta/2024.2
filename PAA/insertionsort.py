def insertionsort(arr):                 # custo vezes
    for i in range(1, len(arr)):        # c1    n
        key = arr[i]                    # c2    n - 1
        j = i - 1                       # c3    n - 1
        while j >= 0 and key < arr[j]:  # c4    somatorio de i=1 ate n - 1 de (t(i)) + 1)
            arr[j + 1] = arr[j]         # c5    somatorio de i=1 ate n - 1 de t(i)
            j = j - 1                   # c6    somatorio de i=1 ate n - 1 de t(i)
        arr[j + 1] = key                # c7    n - 1


insertionsort([4,3,2,1])
