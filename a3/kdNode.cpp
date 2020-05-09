// Author: Andrew Cassidy
// Date: 3/11/20
// Description: kd tree node object implimentation for a program called: kd

#include <iostream>
#include "kdNode.h"

using namespace std;

const int MAX_BUCKET_SIZE = 10;

kdNode::kdNode() {
    // nodes point to NULL
    leftNode = rightNode = NULL;
    dim = -1;
    median = -1;
    isLeaf = true;
} // kdNode()

kdNode::~kdNode() {
    // if the right and/or left nodes aren't null, delete them
    if (rightNode) {
        delete rightNode;
    }
    if (leftNode) {
        delete leftNode;
    }
} // kdNode()

bool kdNode::checkBucket() {
    // if the bucket has more than MAX_BUCKET_SIZE 4d points = bucket.size()/4
    // then return true, else false
    if (bucket.size()/4 > MAX_BUCKET_SIZE) {
        // pick the dimension and median value we want to discriminate the bucket on
        discriminate();
        // break up and empty the bucket dumping its values to the left and right
        breakBucket();
        // check everyone elses buckets recursivly
        leftNode->checkBucket();
        rightNode->checkBucket();
        // return true since node was changed
        return true;
    }
    else {
        // return false since node wasn't changed
        return false;
    }
} // checkBucket()

// calculates and returns the range of all points vals over a certain dimension
int calcRange(vector<int> bucket, int dimToCheck) {
    int minNum, maxNum, range;
    // let the min and max be the first two elements of the dim (we check if this is true)
    switch(dimToCheck) {
        case 0:
            minNum = bucket[0];
            maxNum = bucket[4];
            break;
        case 1:
            minNum = bucket[1];
            maxNum = bucket[5];
            break;
        case 2:
            minNum = bucket[2];
            maxNum = bucket[6];
            break;
        case 3:
            minNum = bucket[3];
            maxNum = bucket[7];
    }
    // check if min and max are true for now
    if (minNum > maxNum || maxNum < minNum) {
        // swap the values of min and max
        int temp = minNum;
        minNum = maxNum;
        maxNum = temp;
    }
    // loop through the loop (based on which dimension to check)
    // and find the min and max values
    for (int i = 2; i < bucket.size()/4; i++) {
        // see if the next point val in same dim is a new smallest or biggest
        int checkThisNum = bucket[(i * 4) + dimToCheck];
        // update min or max if we find a new min or max
        if (checkThisNum < minNum) {
            minNum = checkThisNum;
        }
        if (checkThisNum > maxNum) {
            maxNum = checkThisNum;
        }
    }
    // calculate the range
    range = abs(maxNum - minNum);
    return range;
} // calcRange

// swaps two 4d points in the bucket
void swap(vector<int> &bucket, int index1, int index2) {
    // temporary array to hold the contents of the first 4d point
    int temp[] = {bucket[index1], bucket[index1 + 1], bucket[index1 + 2], bucket[index1 + 3]};
    // swap 1 with 2
    bucket[index1] = bucket[index2];
    bucket[index1 + 1] = bucket[index2 + 1];
    bucket[index1 + 2] = bucket[index2 + 2];
    bucket[index1 + 3] = bucket[index2 + 3];
    // swap 2 with 1
    bucket[index2] = temp[0];
    bucket[index2 + 1] = temp[1];
    bucket[index2 + 2] = temp[2];
    bucket[index2 + 3] = temp[3];
} // swap()

int partition(vector<int> &bucket, int lowIndex, int highIndex, int dim) {
    int pivot, index;
    // value where we will find its point's correct spot in bucket
    pivot = highIndex;
    // index of (everything to the left, not including me, is less than array[pivot])
    index = lowIndex;
    for (int i = lowIndex; i < highIndex; i+=4) {
        // if the next thing in the list is smaller than the pivot, swap the current
        // index and array[i] and increase the index since we have one more value
        // less than the pivot
        if (bucket[i + dim] < bucket[pivot + dim]) {
            swap(bucket, i, index);
            index += 4;
        }
    }
    // we know index is not less than pivot. its either greater than or equal. swap the
    // values since index is where pivot belongs. (everything to the left and right of index is smaller and greater than the pivot respectively)
    swap(bucket, index, pivot);
    return index;
} // partition()

void kdNode::getKthSmallest(int lowIndex, int highIndex, int k) {
    // partition the bucket, discriminating on dim values.
    // partition will return the index of the point that placed in its correct position in the bucket
    int pivot = partition(bucket, lowIndex, highIndex, dim);
    // if we got lucky and found the kth smallest already
    if (pivot == k) {
        median = bucket[pivot + dim];
        medianIndex = pivot;
    }
    // find k to the left of pivot
    else if (pivot > k) {
        getKthSmallest(lowIndex, highIndex - 4, k);
    }
    // find k to the right of the pivot
    else {
        getKthSmallest(pivot + 4, highIndex, k);
    }
}

void kdNode::discriminate() {
    // 1st goal: loop through all points in the bucket, compute their ranges, and
    // use their range to pick which dimension to discriminate on based on who
    // has the largest range.

    // assume dim 0 has biggest range for now
    int range = calcRange(bucket, 0);
    dim = 0;
    // check all the ranges of the dimensions (1-3) and see if they are bigger than dim 0
    for (int i = 1; i < 4; i++) {
        int checkRange = calcRange(bucket, i);
        // if checkRange(i) is bigger than current biggest, make it the new biggest
        // and change the dim we use to i
        if (checkRange > range) {
            range = checkRange;
            dim = i;
        }
    }

    // 2nd goal: find the median value (based on the dim we just choose) by
    // partitioning the bucket with the median in the middle.

    // index's of the first and last point in the bucket
    int highIndex = bucket.size() - 4;
    int lowIndex = 0;
    // middle element index
    int k;
    // check if bucket has even or odd number of points
    if (bucket.size()/4 % 2 == 0) {
        // bucket has even num of points
        // num points is even. the k is the left of the 2 middle points
        k = bucket.size()/2 - 4;
    }
    else {
        // bucket has odd num of points
        // k will be the direct middle point
        k = bucket.size()/2 - 2;
    }
    // partition the array around the median = k
    // this will change the median, medianIndex data members
    getKthSmallest(lowIndex, highIndex , k);
} // discriminate()

void kdNode::breakBucket() {
    // goal: dump the points into the left and right nodes. points to the right of
    // the median index will go to the right node, left points to the left node.

    // new left and right nodes to be inserted into the tree
    kdNode * newLeftNode = new kdNode;
    kdNode * newRightNode = new kdNode;
    // loop through the list and dump points to the right node
    for (int i = medianIndex + 4; i < bucket.size(); i++) {
        newRightNode->bucket.push_back(bucket[i]);
    }
    // insert the new right node into the tree!
    rightNode = newRightNode;
    // loop through the list and dump points to the right node
    for (int i = 0; i < medianIndex + 4; i++) {
        newLeftNode->bucket.push_back(bucket[i]);
    }
    // insert the new left node into the tree!
    leftNode = newLeftNode;
    // node has now become and internal node with its children becoming leaf nodes.
    // "zeroing out" data members to indicate leaf node has become an internal node
    bucket.clear();
    medianIndex = 0;
    isLeaf = false;
} // breakBucket()

void kdNode::print() {
    // print the bucket
    for (int i = 0; i < bucket.size()/4; i++) {
        cout << bucket[(4 * i)]     << " ";
        cout << bucket[(4 * i) + 1] << " ";
        cout << bucket[(4 * i) + 2] << " ";
        cout << bucket[(4 * i) + 3] << endl;
    }
} // print()
