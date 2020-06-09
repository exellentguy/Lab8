#include <iostream>
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

constexpr int N = 1000;
constexpr int M = 100;


int Srch(const int* array, int size, int value)
{
    for (int i = 0; i < size; ++i)
        if (array[i] == value)
            return i;
    return 1111;
}


void RandomFillArray(int* arr, int size, int min, int max) {
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> distribution(min + 1, max - 1);
    for (int i = 0; i < size; ++i)
        arr[i] = distribution(generator);
}




void QckSort(int* arr, int first, int last)
{
    if (first < last)
    {
        int left = first, right = last, middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
                swap(arr[left], arr[right]);
                left++;
                right--;
            }
        } while (left <= right);
        QckSort(arr, first, right);
        QckSort(arr, left, last);
    }
}

void Transposition(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int* arr, int start, int end)
{
    int pivot = arr[end];
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            Transposition(&arr[i], &arr[j]);
        }
    }
    Transposition(&arr[i + 1], &arr[end]);
    return (i + 1);
}

void NotRecursiveQckSort(int* arr, int start, int end)
{
    int* stack = new int[end - start + 1];

    int top = -1;

    stack[++top] = start;
    stack[++top] = end;

    while (0 <= top)
    {
        end = stack[top--];
        start = stack[top--];

        int p = Partition(arr, start, end);

        if (p - 1 > start)
        {
            stack[++top] = start;
            stack[++top] = p - 1;
        }
        if (p + 1 < end)
        {
            stack[++top] = p + 1;
            stack[++top] = end;
        }
    }
    delete[] stack;
}

int BSrch(int* arr, int val, int left, int right) {
    int mid = (right + left) / 2;
    if (arr[mid] == val)
        return mid;
    if (arr[mid] > val)
        return BSrch(arr, val, left, mid);
    if (arr[mid] < val)
        return BSrch(arr, val, mid + 1, right);
    return -1;
}

int NotRecursiveBSrch(const int* arr, int value, int left, int right) {
    while (left <= right) {
        int mid = (right + left) / 2;
        if (arr[mid] == value)
            return mid;
        if (arr[mid] > value)
            right = mid;
        if (arr[mid] < value)
            left = mid + 1;
    }
    return -1;
}

void PrntFrst(int* arr, int n, string prefix)
{
    cout << prefix;
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    srand(time(0));
    int arr[N];
    RandomFillArray(arr, N, -1000, 1000);
    cout << "Liner Search: " << Srch(arr, N, 43) << endl;

    int arr2[M];
    int arr3[] = { 1, 2, 3, 4, 5 };
    int arr4[N];

    RandomFillArray(arr2, M, -10, 10);
    PrntFrst(arr2, 100, "Numbers(random from -10 to 10): ");
    QckSort(arr2, 0, M - 1);
    PrntFrst(arr2, 100, "Quicksort: ");

    RandomFillArray(arr2, M, -10, 10);
    NotRecursiveQckSort(arr2, 0, M - 1);
    PrntFrst(arr2, 100, "Not recusive quicksort(first 100 element from Random Number): ");

    cout << BSrch(arr3, 1, 0, 4) << endl;
    cout << NotRecursiveBSrch(arr3, 5, 0, 4) << endl;
    RandomFillArray(arr4, N, -10, 10);


    auto beginLinearSearch = std::chrono::steady_clock::now();
    Srch(arr4, N, 8);
    auto endLinearSearch = std::chrono::steady_clock::now();

    QckSort(arr4, 0, N - 1);

    PrntFrst(arr4, 100, "Sorted(quicksort 1000 elements, random from -10 to 10): ");

    auto beginRecursiveBinarySearch = std::chrono::steady_clock::now();
    BSrch(arr4, 8, 0, N - 1);
    auto endRecursiveBinarySearch = std::chrono::steady_clock::now();

    auto beginNotRecursiveBinarySearch = std::chrono::steady_clock::now();
    NotRecursiveBSrch(arr4, 8, 0, N - 1);
    auto endNotRecursiveBinarySearch = std::chrono::steady_clock::now();

    auto recursiveBinarySearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endRecursiveBinarySearch - beginRecursiveBinarySearch).count();
    auto linearSearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endLinearSearch - beginLinearSearch).count();
    auto notRecursiveBinarySearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endNotRecursiveBinarySearch - beginNotRecursiveBinarySearch).count();

    std::cout << "Linear search time(search 8 in array of 1000 elements) " << linearSearchTime << " ns" << endl;
    std::cout << "Recursive binary search time(search 8 in array of 1000 elements) " << recursiveBinarySearchTime << " ns" << endl;
    std::cout << "Not recursive binary search time(search 8 in array of 1000 elements) " << notRecursiveBinarySearchTime << " ns" << endl;
}