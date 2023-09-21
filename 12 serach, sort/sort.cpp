//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------

template < class DT >
void selectionSort(DT keyList[], int numKeys)

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    int min;
    int mindex;

    for (int i = 0; i < numKeys - 1; i++)
    {
        min = keyList[i];
        mindex = i;

        for (int j = i + 1; j < numKeys; j++)
        {
            if (min > keyList[j])
            {
                min = keyList[j];
                mindex = j;
            }
        }

        keyList[mindex] = keyList[i];
        keyList[i] = min;
    }
}

//--------------------------------------------------------------------

template < class DT >
void quickPartition(DT keyList[], int numKeys, int left, int right);

template < class DT >
void quickSort(DT keyList[], int numKeys)

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, numKeys, 0, numKeys - 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void quickPartition(DT keyList[], int numKeys,
    int left, int right)

    // Recursive partner of the quickSort routine. Partitions the array
    // entries between left and right into two subarrays. One subarray
    // contains the keys that are less than or equal to splitValue, and
    // the other contains the keys that are greater than splitValue.
    // Recursively sorts each of these subarrays.
{
    int pivotindex = left;

    int low = left + 1, high = right;


    while (low < high)
    {

        while (keyList[low] < keyList[pivotindex])
            low++;

        while (keyList[high] > keyList[pivotindex])
            high--;


        if (low < high)
        {
            DT temp = keyList[low];
            keyList[low] = keyList[high];
            keyList[high] = temp;
            low++;
            high--;
        }
    }


    if (low >= high && keyList[pivotindex] > keyList[high])
    {
        int temp = keyList[pivotindex];
        keyList[pivotindex] = keyList[high];
        keyList[high] = temp;
    }

    if (left < high - 1)
        quickPartition(keyList, numKeys, left, high - 1);
    if (high + 1 < right)
        quickPartition(keyList, numKeys, high + 1, right);
}

//--------------------------------------------------------------------

template < class DT >
void bubbleSort(DT keyList[], int numKeys)
{
    for (int i = numKeys - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (keyList[j] > keyList[j + 1])
            {
                int temp = keyList[j];
                keyList[j] = keyList[j + 1];
                keyList[j + 1] = temp;
            }
        }
    }
}