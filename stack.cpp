#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

const int MAX_SIZE = 20;  //size of the stack

struct Stack {
    int top;
    int data[MAX_SIZE];
};


//static since it doesn't need to be accedded from outside the current source file 
static void initStack(Stack& s) {
    s.top = -1;
}

//static bool isEmpy(Stack &s) // by value
static bool isEmpy(const Stack& s) {   // even though is pass by reference, 'const' means it can't be changed
    return s.top == -1;
}

static bool isFull(const Stack& s) {
    return s.top == MAX_SIZE - 1;
}

//PUSH
static void push(Stack& s, int item) {
    if (isFull(s)) {
        cout << "full stack; cannot push" << item << endl;
    }
    else {
        s.data[++(s.top)] = item;
        cout << item << " pushed on top the stack" << endl;
    }
}

//POP
static int pop(Stack& s) {
    if (isEmpy(s)) {
        cout << "empty stack; nothing to pop" << endl;
        return -1;  //Return an error
    }
    else {
        int item = s.data[(s.top)--];
        return item;
    }
}

//PEEK
static int peek(const Stack& s) {
    if (isEmpy(s)) {
        cout << "empty stack" << endl;
        return -1;   //Return an error
    }
    else {
        return s.data[s.top];
    }
}



#endif STACK_H