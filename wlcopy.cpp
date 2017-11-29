//
// File: wl.cpp
// 
//  Description: Add stuff here ... 
//  Student Name: Zachary Harrison
//  UW Campus ID: zpharrison 
//  enamil: zpharrison@wisc.edu 

#include "wl.h"
 
// create instance of class to call functions
bst tree;

int main()
{
   bool quit = false;
   std::string cmd = "";
   std::string base = "";

   // enter while loop for execution
   while (!quit)
   {
      // print out '>' and wait for next command
      std::cout << ">";
      
      // get user input
      getline(std::cin, cmd);

      std::vector<std::string> args;
      std::istringstream iss(cmd);
      for (std::string s; iss >> s; )
      {
         args.push_back(s);
      }

      base = args.front();
      
      // check command type, if not valid throw error
      if (base.compare("load") == 0)
      {
         std::fstream myfile;
 	 std::string line;
         const char* filename = args[1].c_str();
	 myfile.open(filename);
         if(myfile.is_open())
         {
            while (getline(myfile, line))
	    {
	       std::vector<std::string> words;
	       std::istringstream iss(line);
	       for (std::string s; iss >> s;)
	       {
	          tree.insert((char*)s.c_str());
	       }
	    }
	 } else {
            std::cout<<"ERROR: Invalid command\n";
         }

      } else if (base.compare("locate") == 0) {
	 node* n = tree.find_value((char*)args[1].c_str());
	 if (n)
         {
	    std::cout<<n->value<<'\n';
	 } else {
	    std::cout<<"No matching entry\n";
	 }
      } else if (base.compare("new") == 0) {
         // delete tree
         tree.delete_tree();
      } else if (base.compare("end") == 0) {
         // end program and delete tree
         quit = true;
         tree.delete_tree();
      } else {
         // throw error ???
	 std::cout<<"ERROR: Invalid command\n";
      }

      // delete vector ???
   }

   // close file ???
   return 0;
}

// implementation of binary search tree class functions
bst::bst()
{
   tree.root_node = NULL;
}

//bst::~bst()
//{
   //tree.delete_tree();
//}

void bst::delete_tree(node* n)
{
   if(n != NULL)
   {
      tree.delete_tree(n->left);
      tree.delete_tree(n->right);
      delete n;
   }
}

void bst::delete_tree()
{
   tree.delete_tree(root_node);
   tree.root_node = NULL;
}

void bst::insert(char* value, node* n)
{
   if (/*value < n->value*/ strcasecmp(value, n->value) < 0)
   {
      if (n->left!=NULL)
      {
         insert(value, n->left);
      } else {
         n->left=new node;
         n->left->value=value;
         n->left->left=NULL;
         n->left->right=NULL;
      }
   }
   else if (/*value >= n->value*/ strcasecmp(value, n->value) >= 0)
   {
      if (n->right != NULL)
      {
         insert(value, n->right);
      } else {
         n->right = new node;
         n->right->value = value;
         n->right->left = NULL;
         n->right->right = NULL;
      }
   }
}

void bst::insert(char* value)
{
   if (root_node != NULL)
   {
      insert(value, root_node);
   } else {
      root_node = new node;
      root_node->value = value;
      root_node->left = NULL;
      root_node->right = NULL;
   }
}

node* bst::find_value(char* value, node* n)
{
   if (n != NULL)
   {
      if (/*value.compare(n->value)*/strcasecmp(value, n->value) == 0)
      {
         return n;
      }
      if (/*value.compare(n->value)*/ strcasecmp(value, n->value)< 0)
      {
         return find_value(value, n->left);
      } else {
         return find_value(value, n->right);
      }
   } else {
      return NULL;
   }
}

node* bst::find_value(char* value)
{
   return find_value(value, root_node);
}
