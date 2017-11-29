//
// File: wl.cpp
// 
//  Description: This file implements all functions in the bst class along with
//               the main method that reads the file and inserts words into the
//		 tree, searches words from user input, creates new trees and
//	         terminates the program.
//  Student Name: Zachary Harrison
//  enamil: zpharrison@wisc.edu 

#include "wl.h"
 
// create instance of class to call functions
bst tree;

int main()
{
   // variables to be used throughout main
   bool quit = false;
   std::string cmd = "";
   std::string base = "";
   std::vector<int> words;
   int ei = 0;
   std::fstream myfile;
   
   // enter while loop for execution
   while (!quit)
   {
      // set ad to true for correct command
      std::cout << ">";
      bool ad = true;
       
      // get user input
      getline(std::cin, cmd);

      // loop through command to get all words
      std::vector<std::string> args;
      std::istringstream iss(cmd);
      for (std::string s; iss >> s; )
      {
         args.push_back(s);
      }

      // get main word of command
      base = args.front();

      // check command type, if not valid throw error
      // if load command, parse file and insert into tree
      if (base.compare("load") == 0)
      {
 	 std::string line;
         const char* filename = args[1].c_str();
         // open file and loop through, insert all words to the tree
	 myfile.open(filename);
         if(myfile.is_open())
         {
	    int count = 1;
            while (getline(myfile, line))
	    {
	       std::stringstream ss(line);
	       for (std::string s; ss >> s;)
	       {
                  for (int i=0; i<(int)s.size(); i++)
                  {
                     if (!isdigit(s.at(i)) && !isalpha(s.at(i)))
                     {
                        s.erase(i);
                     }
                  }
	          tree.insert((char*)s.c_str(), count);
                  count++;
	       }
	    }
	 } else {
            std::cout<<"ERROR: Invalid command\n";
         }
      // if locate, search tree for entered word
      } else if (base.compare("locate") == 0) {
	 if(args.size() != 3)
         {
            std::cout<<"ERROR: Invalid command\n";
         } else {
            // check for non numerical or digit characters
            for (int i=0; i<(int)args[2].size(); i++)
            {
               if (!isdigit(args[2].at(i)))
               {
                  std::cout<<"ERROR: Invalid command\n";
                  ad = false;
                  break; 
               }
            }
            for (int j=0; j<(int)args[1].size(); j++)
            {
               if (!ad) break;
               if (!isdigit(args[1].at(j)) && !isalpha(args[1].at(j)))
               {
                  std::cout<<"ERROR: Invalid command\n";
                  ad = false;
                  break; 
               }
            }
            if (ad) 
            {
               // search tree for word, print if found
               ei = atoi((char*)args[2].c_str());
               node* n = tree.find_value((char*)args[1].c_str());
	       if (n)
               {
                  if (n->index[ei-1] > 0) 
                  {
	             std::cout<<n->index[ei-1]<<'\n';
	          } else {
                     std::cout<<"No mathcing entry\n";
                  }
               } else {
	          std::cout<<"No matching entry\n";
	       }
            }
         }
      // if new, delete tree structure
      } else if (base.compare("new") == 0) {
         // close file and delete tree
         myfile.close();
         tree.delete_tree();
      // if end, delete tree and set flag to exit looop
      } else if (base.compare("end") == 0) {
         // end program close file and delete tree
         quit = true;
         myfile.close();
         tree.delete_tree();
      } else {
	 std::cout<<"ERROR: Invalid command\n";
      }
   }
   return 0;
}

// implementation of binary search tree class functions

/**
 * Constructor. Sets root node to null
 *
 */
bst::bst()
{
   tree.root_node = NULL;
}

/**
 * Private method that recursively deletes the tree
 *
 * @param n first node to start delete from
 */
void bst::delete_tree(node* n)
{
   // if node isn't null recursively delete all nodes
   if(n != NULL)
   {
      tree.delete_tree(n->left);
      tree.delete_tree(n->right);
      free(n->index);
      delete n;
   }
}

/**
 * Public delete method. Calls private delete with root node
 *
 */
void bst::delete_tree()
{
   // delete tree starting with root node
   tree.delete_tree(root_node);
   tree.root_node = NULL;
}

/**
 * Private insert. Recurseively navigates down tree to find right insertion spot
 *
 * @param value Value that the node will have. Determines where node will be.
 * @param n Node where search starts
 * @param count Where the word(value) is in the file
 */
void bst::insert(char* value, node* n, int count)
{
   // if value is less than node, go left
   if (strcasecmp(value, n->value) < 0)
   {
      // check if add new node or keep traversing
      if (n->left!=NULL)
      {
         insert(value, n->left, count);
      } else {
         // create new node and set all values
         n->left=new node;
         strncpy(n->left->value, value, sizeof(n->left->value));
         if (n->left->cur)
            n->left->cur++;
         else 
            n->left->cur = 0;
         n->left->index = (int*)malloc(10*sizeof(int));
         n->left->index[n->left->cur] = count;
         n->left->left=NULL;
         n->left->right=NULL;
      }
   }
   // if value greater than current node go right
   else if (strcasecmp(value, n->value) > 0)
   {
      // check if add new node or keep traversing
      if (n->right != NULL)
      {
         insert(value, n->right, count);
      } else {
         // create new node and set all values
         n->right = new node;
         strncpy(n->right->value, value, sizeof(n->right->value));
         if (n->right->cur)
            n->right->cur++;
         else 
            n->right->cur = 0;
         n->right->index = (int*)malloc(10*sizeof(int));
         n->right->index[n->right->cur] = count;
         n->right->left = NULL;
         n->right->right = NULL;
      }
   } else {
      // word already exists in tree so add another index to array
      n->cur++;
      // resize index array if necessary
      if ((n->cur*sizeof(int)) >= sizeof(n->index))
      {
         size_t new_size = sizeof(n->index) * 2;
         int* new_array = (int*)realloc(n->index, new_size);
         n->index = new_array;
      }
      n->index[n->cur] = count;
   }
}

/**
 * Public insert. Creates root node if none or inserts from root node
 *
 * @param value Word from file that the node will contain
 * @param count Where the word(value) is in the file
 */
void bst::insert(char* value, int count)
{
   // if first node exists, traverse for correct spot
   // if not create root node
   if (root_node != NULL)
   {
      insert(value, root_node, count);
   } else {
      root_node = new node;
      strncpy(root_node->value, value, sizeof(root_node->value));
      root_node->cur = 0;
      root_node->index = (int*)malloc(10*sizeof(int));
      root_node->index[root_node->cur] = count;
      root_node->left = NULL;
      root_node->right = NULL;
   }
}

/**
 * Private search. Finds where value is in tree and returns node
 *
 * @param value Word to search tree for
 * @param n Node to start search from
 * @return n Returns the node if found, else NULL
 */
node* bst::find_value(char* value, node* n)
{
   // recursively search tree for value, if not found return null
   if (n != NULL)
   {
      if (strcasecmp(value, n->value) == 0)
      {
         return n;
      }
      if (strcasecmp(value, n->value)< 0)
      {
         return find_value(value, n->left);
      } else {
         return find_value(value, n->right);
      }
   } else {
      return NULL;
   }
}

/**
 * Public search. Finds node corresponding to passed in word.
 *
 * @param value Word to be searched for
 * @return Node that will be returned if found
 */
node* bst::find_value(char* value)
{
   return find_value(value, root_node);
}
