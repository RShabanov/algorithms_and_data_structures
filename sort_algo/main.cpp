#include <iostream>
#include <string>
using namespace std;


template<typename T>
void insertion_sort(T* arr, int array_len);

template<typename T>
void selection_sort(T* arr, int array_len);

template<typename T>
void print_array(T* arr, int array_len) {
    for (int i = 0; i < array_len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template<typename T>
void quicksort(T* arr, T* l, T* r);

template<typename T>
T* partition(T* arr, T* l, T* r);

void insertion_sort(string arr[], int array_len);


int main() {
    const int array_len = 7;
    int arr[array_len] { 9, 2, 7, 3, 4, 3, 11 };
    
//     constexpr int array_len = 4;
//     string arr[array_len] { "qwe", "qwerty", "asd", "qwer" };
    
    insertion_sort(arr, array_len);
//     cout << *(arr + array_len - 1) << endl;
//     quicksort(arr, arr, arr + array_len - 1);
    
    for (auto item : arr)
        cout << item << " ";
    cout << endl;
    
    return 0;
}

void insertion_sort(string arr[], int array_len) {
    for (int i = 1; i < array_len; i++) {
        auto key = arr[i];
        int index = i;
        for (int j = i - 1; j >= 0; j--)
            if (arr[j].length() > key.length()) {
                index = j;
                break;
            }
        
        arr[i] = arr[index];
        arr[index] = key;
    }
}


template<typename T>
void insertion_sort(T arr[], int array_len) {
    for (int i = 1; i < array_len; i++) {
        T key = arr[i];
        int index = i;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > key) {
                index = j + 1;
                break;
            }
        }
        
        arr[i] = arr[index];
        arr[index] = key;
        
        for (int i = 0; i < array_len; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
}


template<typename T>
void selection_sort(T* arr, int array_len) {
    for (int i = 0; i < array_len - 1; i++) {
        int m = i;
        for (int j = i + 1; j < array_len; j++)
            if (arr[j] > arr[m]) m = j;
            
        if (m != i) {
            T temp = arr[i];
            arr[i] = arr[m];
            arr[m] = temp;
        }
        
        cout << "# " << i << endl;
        print_array(arr, array_len);
    }
}

template<typename T>
void quicksort(T* arr, T* l, T* r) {
    if (l < r) {
        auto q { partition(arr, l, r) };
        quicksort(arr, l, q);
        quicksort(arr, q + 1, r);
    }
}
    
template<typename T>
T* partition(T* arr, T* left, T* right) {
    T *l = left,
        *r = right;
    T m { *(l + ((r - l) >> 1)) };
    
    while (true) {
        while (*l < m) l++;
        while (*r > m) r--;
        
        if (*l <= *r) return l;
        
        T temp = *l;
        *l = *r;
        *r = temp;
    }
}
