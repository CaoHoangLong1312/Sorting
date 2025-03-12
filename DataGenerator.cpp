#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

// Binary insertion sort algorithm
int binarySearch(int a[], int left, int right, int key) {
    while (left <= right) {
        int mid = (left + right) / 2;

        if (key == a[mid]) {
            return mid + 1;
        } else if (key < a[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

void binaryInsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        int loc = binarySearch(a, 0, j, key);

        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Quick sort algorithm
int partition(int a[], int left, int right) {
	int pivot = right;
	right--;

	while (left <= right) {
		while (left <= right && a[left] < a[pivot]) {
			left++;
		}

		while (left <= right && a[right] > a[pivot]) {
			right--;
		}

		if (left <= right) {
			int temp = a[left];
			a[left] = a[right];
			a[right] = temp;

			left++;
			right--;
		}
	}

	int temp = a[left];
	a[left] = a[pivot];
	a[pivot] = temp;

	return left;
}

void quickSort(int a[], int left, int right) {
	if (left >= right) {
		return;
	}

	int pivot = partition(a, left, right);

	quickSort(a, left, pivot - 1);
	quickSort(a, pivot + 1, right);
}

// Merge sort algorithm
void merge(int b[], int p, int c[], int q, int a[]) {
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < p && j < q) {
		if (b[i] <= c[j]) {
			a[k] = b[i];
			i++;
		} else {
			a[k] = c[j];
			j++;
		}

		k++;
	}

	while (i < p) {
		a[k] = b[i];
		i++;
		k++;
	}

	while (j < q) {
		a[k] = c[j];
		j++;
		k++;
	}
}

void mergeSort(int a[], int n) {
	if (n > 1) {
		int mid = n / 2;
		int p = mid;
		int q = n - mid;

		int* b = new int[p];
		int* c = new int[q];

		for (int i = 0; i < p; i++) {
			b[i] = a[i];
		}

		for (int i = 0; i < q; i++) {
			c[i] = a[i + mid];
		}

		mergeSort(b, p);
		mergeSort(c, q);

		merge(b, p, c, q, a);

		delete[] b;
		delete[] c;
	}
}

// Selection sort algorithm
void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1 ; i++) {
		int min = i;

		for (int j = 1 + i; j < n ; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}

		swap(a[i], a[min]);
	}
}

// Counting sort algorithm
void countingSort(int a[], int n) {
	int maxVal = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > maxVal) {
			maxVal = a[i];
		}
	}

	int size = maxVal + 1;
	int* output = new int[n];
	int* count = new int[size];

	for (int i = 0; i < size; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		count[a[i]]++;
	}

	for (int i = 1; i < size; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		output[count[a[i]] - 1] = a[i];
		count[a[i]]--;
	}

	for (int i = 0; i < n; i++) {
		a[i] = output[i];
	}

	delete[] count;
	delete[] output;
}