//
// File: wl.h
// 
//  Description: Add stuff here ... 
//  Student Name: Zachary Harrison
//  UW Campus ID: zpharrison 
//  enamil: zpharrison@wisc.edu
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <strings.h>

struct node
{
   char* value;
   struct node *right;
   struct node *left;
};

class bst
{
   public:
      bst();
      //~bst();

      void insert(char* value);
      node* find_value(char* value);
      void delete_tree();

   private:
      void insert(char* value, node* n);
      node* find_value(char* value, node* n);
      void delete_tree(node* n);

      node* root_node;  
};
