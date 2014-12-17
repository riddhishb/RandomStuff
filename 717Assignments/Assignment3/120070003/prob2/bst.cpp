#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
#include "bst.h"

BinSearchTree* BinSearchTree::buildTree(BinSearchTree *tree, char letter){
  if (tree == NULL) {
    tree = new BinSearchTree (letter); 
  } else { 
/*DO NOT EDIT BEFORE THIS LINE*/
/*Make appropriate changes here to build a BST*/
  	BinSearchTree *tree1 = tree;
  	int count = 0;
  	while(tree1 != NULL){
  		if(letter < tree1->symbol){
  			if(tree1->lChild !=NULL){
  			tree1 = tree1->lChild;}
  			else break;
  			
  		}
  		else {
  			if(tree1->rChild !=NULL){
  			tree1 = tree1->rChild;}
  			else break;
  			
  		}
  		count++;
  	}
  	 if(letter<tree1->symbol){
  		tree1->lChild = new BinSearchTree(letter);
  	}
  	else{
  		tree1->rChild = new BinSearchTree(letter);
  	}
  	tree = tree1;
  }
  return tree;
}
void BinSearchTree::printTreePreOrder (BinSearchTree *temp, std::ofstream &fp1) {
/*Make appropriate changes here*/
	fp1 << temp->symbol;
	if(temp->lChild != NULL)
        printTreePreOrder(temp->lChild,fp1);
        if(temp->rChild != NULL)
        printTreePreOrder(temp->rChild,fp1);
    
}
void BinSearchTree::printTreeInOrder (BinSearchTree *temp, std::ofstream &fp1) {
/*Make appropriate changes here*/

	if(temp->lChild != NULL)
        printTreeInOrder(temp->lChild,fp1);
        fp1<<temp->symbol;
        if(temp->rChild != NULL)
        printTreeInOrder(temp->rChild,fp1);
    
}
