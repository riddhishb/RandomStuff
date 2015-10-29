// binary search tree 

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct node{
	int root;
	struct node *left;
	struct node *right;
};

struct node* newNode(int val){
	struct node* temp = (struct node*)
						malloc(sizeof(struct node));
	temp->root = val;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void preOrder(struct node* node1)
{
	if (node1 == NULL)
		return;
	printf("%d ", node1->root);
	preOrder(node1->left);
	preOrder(node1->right);
}

// this will create a BST from a sorted array
struct node* sortedArr2BST(int arr[],int start,int end){
	if(start>end) return NULL;
	int mid = 0.5*(start+end);
	struct node *root1 = newNode(arr[mid]);
	
	root1->left = sortedArr2BST(arr,start,mid-1);
	root1->right = sortedArr2BST(arr,mid+1,end);	
	return root1;
}

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main(){

	// now to take input of an int array and sort it
	// then convert that sorted array into
	int N; cin>>N;
	int arr[N];
	for(int i=0;i<N;i++) cin>>arr[i];

	// sorting the array
	// Sort the array using library function for quick sort
    qsort (arr, N, sizeof(arr[0]), compare);	
	for(int i=0;i<N;i++) cout << arr[i] << " ";
	cout <<endl;	
	struct node *out = sortedArr2BST(arr,0,N-1);	
	
	preOrder(out);
	return 0;
}
