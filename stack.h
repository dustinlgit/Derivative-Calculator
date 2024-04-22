#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class Stack{
public:
    int top;
    int data[MAX_SIZE];   
};

static void initStack(Stack& s) {
    s.top = -1;
}

static bool isEmpty(const Stack& s){
    return s.top == -1;
}

static bool isFull(const Stack& s){
    return s.top == MAX_SIZE - 1;
}

static void push(Stack& s, int item){
    if(isFull(s))
        cout << "full stack; cannot push" << item << endl;
    else
        s.data[(s.top)++] = item;
}

static int pop(Stack& s){
    if(isEmpty(s))
        cout << "empty stack; cannot pop\n";
    else{
        int item = s.data[(s.top)--];
        return item;
    }
}

static int peek(Stack& s){
    if (isEmpty(s)) {
        cout << "empty stack" << endl;
        return -1;   //Return an error
    }
    else
        return s.data[s.top];
    
}
#endif STACK_H