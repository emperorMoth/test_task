#include <iostream>
#include <random>
#include <cstdlib>
using namespace std;

random_device rd;
mt19937 gen(rd());

class FirstStep {
    int n, mutableSize, *mutablePointer;
    int maxSizeOfSubArr;

    int getCountOfArrs() {
        cout << "Enter a number of arrays: \n";
        cin >> n;
        if ((cin.fail()) || (n <= 0)) {
            cout << "'n' must be integer and > 1. Try to input value again, please." << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            getCountOfArrs();
        }
        else if (n > 0) {
            return n;
        }
    }

    int sortingValArr(int n, int size, int* unsortedValsArr, int* sortedValsArr) {
        int elemIndex = 0;
        for (int i = 0; i < size; i++) {
            if (unsortedValsArr[i] != unsortedValsArr[i + 1]) {
                sortedValsArr[elemIndex] = unsortedValsArr[i];
                elemIndex += 1;
                if (elemIndex == n) {
                    return *sortedValsArr;
                } else {
                    continue;
                }

            } else {
                continue;
            }
        }
    }
    //comparison functions ->
    static int compForIncrem(const void * a, const void * b) {
        return (*(int*)a - *(int*)b);
    }
    static int compForDecrem(const void* a, const void* b) {
        return (*(int*)b - *(int*)a);
    }
public:
    int start() {
        getCountOfArrs();
        int size = ((n < 10) ? (n + (n / 2)) : (n * 2));
        int* unsortedValsArr = new int[size];
        int* sortedValsArr = new int[n];

        maxSizeOfSubArr = ((n > 9) ? (n * 2) : (n * 4));
        uniform_int_distribution<int> dist(3, maxSizeOfSubArr);

        for (int i = 0; i < size; i++) {
            unsortedValsArr[i] = dist(rd);
        }
        qsort(unsortedValsArr, size, sizeof(int), compForIncrem);

        sortingValArr(n, size, unsortedValsArr, sortedValsArr);
        delete[] unsortedValsArr;

        createSubArrs(n, sortedValsArr);
        delete[] sortedValsArr;
        return 0;
    }

    int createSubArrs(int n, int *sortedValsArr) {
        uniform_int_distribution<int> dist(1, 10000);
        for (int i = 0; i < n; i++) {
            mutableSize = sortedValsArr[i];
            int* subArr = new int[mutableSize];
            for (int j = 0; j < mutableSize; j++) {
                subArr[j] = dist(rd);
            }
            if ((i + 1) % 2 == 0) {
                qsort(subArr, mutableSize, sizeof(int), compForIncrem);
            }
            else {
                qsort(subArr, mutableSize, sizeof(int), compForDecrem);
            }
            cout << i + 1 << ": ";
            for (int j = 0; j < mutableSize; j++) {
                cout << subArr[j] << " ";
            }
            cout << endl;
            delete[] subArr;
        }
        return 0;
    }
};

int main() {
    FirstStep prog;
    prog.start();

    return 0;
}
 