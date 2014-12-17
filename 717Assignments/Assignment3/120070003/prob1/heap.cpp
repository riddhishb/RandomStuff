#include <iostream>
using namespace std;
#include "heap.h"

Heap::Heap(int size){
//create a heap of size+1 positions. 0th position is unused.
	priority = new int[size+1];
}

Heap::~Heap()
{
	delete []priority;
	priority = NULL;
}

void Heap::createHeap() {
//upon creation, no elements are in the heap
   last = 0;
}

int Heap::empty() {
  if (last == 0)
    return(1);
  else
    return(0);
}


int Heap::deleteMin() {
  int item;
  
  if (last < 1)
  	return(-10000);
  item = priority[1];

  priority[1] = priority[last];
  last = last - 1;
  
  Heapify(1);
  return(item);
}

/*DO NOT EDIT BEFORE THIS LINE*/
void Heap::Heapify(int pos)
{
/*Fill in the functionality to perform Heapify() operation on the array priority[] at position pos*/
  int l = 2*pos; // postion of the left branch 
  int r = l+1;   // position of the right branch
  int minimum = pos;
  int temp;
  if((l<=last)&&(priority[l]<priority[pos])){
    minimum = l;
  }
  if((r<=last)&&(priority[r]<priority[minimum])){
    minimum = r;
  }
  if(minimum != pos) { // exchange the array terms
    temp = priority[pos];
    priority[pos] = priority[minimum];
    priority[minimum] = temp;
    Heapify(minimum);
  }
}
void Heap::insertHeap(int x) {
/*Fill in the functionality for inserting elements into a heap. The heap is stroed in an array called 
priority*/
  last = last +1;
  priority[last]=x;
  int i = last;
  int parent = priority[last/2];
  while(parent>priority[i]){
    priority[i/2] = priority[i];
    priority[i] = parent;
    i=i/2;
    if(i==1){break;}
    parent = priority[i/2];
  }
}

/*DO NOT EDIT AFTER THIS LINE*/

/*If you need to, call this function to see if the heap is being built properly and operated properly*/
void Heap::printHeap()
{
	int i=1;
	while(i<=last){
		cout << priority[i++] << " ";
	}
	cout<<endl;
}
