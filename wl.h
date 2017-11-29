//
// File: wl.h
// 
//  Description: This file contains the bst class and the node structure used
//		 in the tree.
//  Student Name: Zachary Harrison
//  UW Campus ID: zpharrison 
//  enamil: zpharrison@wisc.edu
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdlib.h>

struct node
{
   char value[256];
   int cur;
   int *index;
   node *right;
   node *left;
};

class bst
{
   public:
      bst();

      void insert(char* value, int count);
      node* find_value(char* value);
      void delete_tree();
 
   private:
      void insert(char* value, node* n, int count);
      node* find_value(char* value, node* n);
      void delete_tree(node* n);

      node* root_node;  
};
