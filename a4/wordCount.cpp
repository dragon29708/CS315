// Author: Andrew Cassidy
// Date: 3/31/20
// Description: Implements a hash data strucuture for Spring 2020 CS 315 Assignment 4

#include <iostream>
#include <string>
#include "LList.h"
#include "wordHash.h"

using namespace std;

void quickSort(string array[], int lowIndex, int highIndex);
void getKthSmallest(int lowIndex, int highIndex, int k, string array[], wordHash * myHash);

int main() {
    // array of strings that are inputted
    string list[10000];
    // get all the words
    int i = 0;
    while (true) {
        // get the new string
        string newString;
        cin >> newString;
        // we did not hit the last string so add it to the array
        if (newString != "") {
            list[i] = newString;
            i++;
        }
        // hit the end of the file
        else {
            // this index will have nothing to store
            i--;
            break;
        }
    }
    // sort the list
    quickSort(list, 0, i);
    // hash that will store the counts of the strings
    wordHash * myHash = new wordHash;
    // insert the list into the hash
    for (int j = 0; j < i + 1; j++) {
        myHash->insert(list[j]);
    }
    // print the sorted list with its corresponding counts
    for (int j = i; j >= 0; j--) {
        if (list[j] != list[j-1]) {
            cout << list[j] << " " << myHash->findCount(list[j]) << endl;
        }
    }
    // place all strings into a new array without any duplicates
    string newList[10000];
    // num is the next index to place a string into newList
    int num = 0;
    for (int j = 0; j < i + 1; j++) {
        // copy the first thing in no problem
        if (j == 0) {
            newList[num] = list[j];
            num++;
        }
        // check for duplicate strings. dont place dup strings in newList
        else {
            // if its not a duplicate, place it in the newList
            if (list[j] != list[j - 1]) {
                newList[num] = list[j];
                num++;
            }
        }
    }
    // sort newList highest to lowest based on deacreasing occurances
    // and print them to the screen
    cout << endl;
    for (int j = num-1; j >=0 ; j--) {
        getKthSmallest(0, j, j, newList, myHash);
    }
    // alphabetically sort each subsection where each string in the
    // subsection has the same count
    int startIndex = 0;
    int subsectionCount = myHash->findCount(newList[0]);;
    for (int j = 0; j < num - 1; j++) {
        // if we hit the end of a subsection
        if (myHash->findCount(newList[j+1]) > subsectionCount) {
            // sorted subsection will be from start index to j
            quickSort(newList, startIndex, j);
            // new subsection will start at j + 1
            startIndex = j + 1;
            subsectionCount = myHash->findCount(newList[j+1]);
        }
    }
    // print the sorted list with its corresponding counts
    for (int j = num - 1; j >= 0; j--) {
        cout << newList[j] << " " << myHash->findCount(newList[j]) << endl;
    }
    return 0;
} // main()

// swaps the values stored in 2 indicies in an array
void swap(string array[], int index1, int index2) {
    // cant swap on same index
    if (index1 == index2)
        return;
    // holder val for when i need to swap
    string holder;
    // hold one value for swap
    holder = array[index1];
    // swap the values
    array[index1] = array[index2];
    array[index2] = holder;
} // swap()

// USED FOR QUICK SORT: partitions an array using a pivot value. values to left of pivot are
// smaller and values to the right are larger
int partition(string array[], int lowIndex, int highIndex) {
    int pivot, index;
    // value where we will find its right spot
    pivot = highIndex;
    // index of (everything to the left, not including me, is less than array[pivot])
    index = lowIndex;
    for (int i = lowIndex; i < highIndex; i++) {
        // if the next thing in the list is smaller than the pivot, swap the current
        // index and array[i] and increase the index since we have one more value
        // less than the pivot
        if (array[i].compare(array[pivot]) > 0) {
            swap(array, i, index);
            index++;
        }
    }
    // we know index is not less than pivot. its either greater than or equal. swap the
    // values since index is where pivot belongs. (everthing to the left and right of index is smaller and greater than the pivot respectively)
    swap(array, index, pivot);
    return index;
}

// Quick sort: nlog(n) method
// Description: quick sort partitions the array into different sections recursively using a pivot value. this pivot value
// happens when we partition the array so that values smaller than the pivot are to the left of it and values
// larger than it are to the right. ie we recursivly find the perfect spots in the array for all pivots. each
// time getting faster and faster.
void quickSort(string array[], int lowIndex, int highIndex) {
    int pivot;
    // sort if the list is not empty or is just one element
    if (lowIndex < highIndex) {
        // partition to the left and right of a pivot. get the index of the pivot that
        // is in the correct position in the array
        pivot = partition(array, lowIndex, highIndex);
        // partition above the pivot
        quickSort(array, lowIndex, pivot - 1);
        // partition below the pivot
        quickSort(array, pivot + 1, highIndex);
    }
} // quickSort()

// USED FOR GETKTHSMALLEST: partitions an array using a pivot value. values to left of pivot are
// smaller and values to the right are larger
int partition2(string array[], int lowIndex, int highIndex, wordHash * myHash) {
    int pivot, index;
    // value where we will find its right spot
    pivot = highIndex;
    // index of (everything to the left, not including me, is less than array[pivot])
    index = lowIndex;
    for (int i = lowIndex; i < highIndex; i++) {
        // if the next thing in the list is smaller than the pivot, swap the current
        // index and array[i] and increase the index since we have one more value
        // less than the pivot
        if (myHash->findCount(array[i]) < myHash->findCount(array[pivot])) {
            swap(array, i, index);
            index++;
        }
    }
    // we know index is not less than pivot. its either greater than or equal. swap the
    // values since index is where pivot belongs. (everthing to the left and right of index is smaller and greater than the pivot respectively)
    swap(array, index, pivot);
    return index;
}

void getKthSmallest(int lowIndex, int highIndex, int k, string array[], wordHash * myHash) {
    // partition the bucket, discriminating on string counts.
    // partition will return the index of the point that placed in its correct position in the bucket
    int pivot = partition2(array, lowIndex, highIndex, myHash);
    // if we got lucky and found the kth smallest already
    if (pivot == k) {
        return;
    }
    // find k to the left of pivot
    else if (pivot > k) {
        getKthSmallest(lowIndex, highIndex - 1, k, array, myHash);
    }
    // find k to the right of the pivot
    else {
        getKthSmallest(pivot + 1, highIndex, k, array, myHash);
    }
} // getKthSmallest()
