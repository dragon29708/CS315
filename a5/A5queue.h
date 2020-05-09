//
// Created by andrew on 4/22/20.
//

#ifndef A5_A5QUEUE_H
#define A5_A5QUEUE_H

#include <vector>

template<class T>
class A5queue {
public:
    // constructor and deconstructor
    A5queue ();
    ~A5queue ();
    // functions
    void push (T insertMe); // inserts object of type T into queue
    void pop (); // removes the top object in the queue
    T front (); // returns a pointer to the first object in the queue
    bool empty (); // returns a bool whether or not the queue is empty or not
    int size (); // returns the size of the queue
private:
    // data members
    std::vector<T> Q;
};

// A5queue definition

template<class T>
A5queue<T>::A5queue () {
    // does nothing
} // A5queue()

// deletes the vector
template<class T>
A5queue<T>::~A5queue () {
    Q.clear();
} // ~A5queue()

// inserts the object into the vector
template<class T>
void A5queue<T>::push (T insertMe) {
    Q.push_back(insertMe);
} // push(T insertMe)

// removes the first element in the vector
template<class T>
void A5queue<T>::pop () {
    Q.erase(Q.begin());
} // pop()

// returns an reference to the first
template<class T>
T A5queue<T>::front () {
    return Q.front();
} // front()

// returns a bool whether or not the queue is empty or not
template<class T>
bool A5queue<T>::empty () {
    return Q.empty();
} // empty()

template<class T>
int A5queue<T>::size () {
    return Q.size();
} // size()

// size()

#endif //A5_A5QUEUE_H