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

long long comparisonCount = 0;

// Binary insertion sort algorithm
int binarySearch(int a[], int left, int right, int key) {
    while (true) {
		comparisonCount++;
		if (left > right) {
			return left;
		}

		int mid = (left + right) / 2;

		comparisonCount++;
		if (key == a[mid]) {
			return mid + 1;
		}

		comparisonCount++;
		if (key < a[mid]) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
}

void binaryInsertionSort(int a[], int n) {
    int i = 1;
	while (true) {
		comparisonCount++;
		if (i >= n) {
			break;
		}

		int key = a[i];
		int j = i - 1;

		int loc = binarySearch(a, 0, j, key);
		
		while (true) {
			comparisonCount++;
			if (j < loc) {
				break;
			}

			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = key;
		i++;
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
			HoanVi(a[left], a[right]);

			left++;
			right--;
		}
	}

	HoanVi(a[left], a[pivot]);
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

		HoanVi(a[i], a[min]);
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

// Insertion sort algorithm
void insertionSort(int arr[], int n)
{

	int current, temp;	//current là biến vị trí hiện tại
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		current = i;
		temp = arr[i];

		while (current > 0 && arr[current - 1] > temp)
		{
            comparisonCount += 2;
			arr[current] = arr[current - 1];
			current--;
		}

        if (current > 0) {
            comparisonCount++;
        }

		arr[current] = temp;
	}

    comparisonCount++;
}

// Bubble sort algorithm
void bubbleSort(int arr[], int n)
{

	int index = 1, temp;

	while (++comparisonCount && index != 0)
	{
		index = 0;
		for (int i = 0; i < n - 1; i++)
		{
            comparisonCount++;
			if (arr[i] > arr[i + 1])
			{
				index++;
				/*
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				*/
				HoanVi(arr[i], arr[i + 1]);
			}
            comparisonCount++;

		}
        comparisonCount++;
	}
}

// Radix sort algorithm
int findMax(int arr[], int n)
{
	int nmax = arr[0];
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		nmax = max(nmax, arr[i]);
	}

    comparisonCount++;
	return nmax;
}

void radixSort(int arr[], int n)
{
	int nmax = findMax(arr, n), index = 1, digit;
	int temp[10] = { 0 };
	int* result = new int[n];

	while (++comparisonCount && nmax / index > 0)
	{
		int temp[10] = { 0 };
		for (int i = 0; i < n; i++)
		{
            comparisonCount++;
			temp[arr[i] / index % 10]++;
		}

        comparisonCount++;

		for (int i = 1; i < 10; i++)
		{
            comparisonCount++;
			temp[i] = temp[i] + temp[i - 1];
		}

        comparisonCount++;

		for (int i = n - 1; i >= 0; i--)
		{
            comparisonCount++;
			digit = arr[i] / index % 10;
			result[temp[digit] - 1] = arr[i];
			temp[digit]--;
		}

        comparisonCount++;

		for (int i = 0; i < n; i++)
		{
            comparisonCount++;
			arr[i] = result[i];
		}

        comparisonCount++;
		index *= 10;
	}

	delete[] result;
}

// Flash sort algorithm
void flashSort(int arr[], int n)
{
	int maxVal = arr[0], minVal = arr[0], maxIndex = 0;
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		if (arr[i] > maxVal)
		{
			maxVal = arr[i];
			maxIndex = i;
		}

        comparisonCount++;

		if (arr[i] < minVal)
			minVal = arr[i];

        comparisonCount++;
	}

    comparisonCount++;
    comparisonCount++;

	if (maxVal == minVal) {
        return;
    }

	int m = floor(0.45 * n);  
	int* L = new int[m]();
	int k;
	for (int i = 0; i < n; i++)
	{
        comparisonCount++;
		k = floor((m - 1) * (arr[i] - minVal) / (maxVal - minVal));
		L[k]++;
	}

    comparisonCount++;

	for (int i = 1; i < m; i++)
	{
        comparisonCount++;
		L[i] += L[i - 1];  
	}

    comparisonCount++;

	int count = 0, index = 0;
	while (++comparisonCount && count < n)
	{
		k = floor((m - 1) * (arr[index] - minVal) / (maxVal - minVal));
		while (++comparisonCount && index >= L[k])
		{
			k = floor((m - 1) * (arr[++index] - minVal) / (maxVal - minVal));
		}

		int temp = arr[index];
		while (++comparisonCount && index < L[k])
		{
			k = floor((m - 1) * (temp - minVal) / (maxVal - minVal));
			swap(temp, arr[--L[k]]);
			count++;
		}
	}

	delete[] L;

    insertionSort(arr, n);
}

// Shaker sort algorithm
void shakerSort(int arr[], int n)
{
	int bienPhai, bienTrai;
	int left = 0, right = n - 1;
	while (++comparisonCount && left < right)
	{
		bienPhai = -1;
		bienTrai = -1;
		for (int i = left; i < right; i++)
		{
            comparisonCount += 2;

			if (arr[i] > arr[i + 1])
			{
				HoanVi(arr[i], arr[i + 1]);
				bienPhai = i;
			}
		}

        comparisonCount += 2;

		if (bienPhai == -1)
		{
			break;
		}

		right = bienPhai;
        comparisonCount++;

		if (left == right) break;

		for (int i = right; i > left; i--)
		{
            comparisonCount += 2;
			if (arr[i] < arr[i - 1])
			{
				HoanVi(arr[i], arr[i - 1]);
				bienTrai = i;
			}
		}

        comparisonCount += 2;

		if (bienTrai == -1)
		{
			break;
		}

		left = bienTrai;
	}
}

// Heap Sort Algorithm
void max_heapify(int a[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] > a[largest]) { // nếu con trái tồn tại và lớn hơn cha
		largest = left; // đổi giá trị giữa cha với con
	}

	if (right < n && a[right] > a[largest]) { // nếu con phải tồn tại, lớn hơn cha 
		largest = right;
	}

	if (largest != i) { // nếu nút cha ko phải là cha ban đầu
		HoanVi(a[i], a[largest]);
		max_heapify(a, n, largest);
	}
}

void build_maxheap(int a[100], int n) {
	for (int i = n/2 - 1; i >= 0; i--) { //duyệt từ nút cha cuối lên gốc
		max_heapify(a, n, i);
	}
}

void heap_sort(int a[100], int n) {
	build_maxheap(a, n); // bước 1: xây dựng max_heap

	for (int i = n - 1; i > 0; i--) {
		HoanVi(a[i], a[0]); //đưa max về cuối
		max_heapify(a, i, 0); //gọi heapify trên phần còn lại
	}
}

// shell sort algorithm
void shell_sort(int a[100], int n) {
	int gap = n/2;

	while (gap > 0) {
		for (int i = 0; i < n; i++) {
			int temp = a[i];
			int j = i;
			while (j >= gap && a[j - gap] > temp)
			{
				a[j] = a[j - gap];
				j = j - gap;
			}
			a[j] = temp;
		}
		cout << "\n";
		for(int i = 0; i < n; i++){
			cout << a[i] << " ";
		}
		gap /= 2;
	}
}