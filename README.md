# Word_Locator
Reads in a file, then able to locate words within the file using a bst tree.

# Usage
1. make clean
2. make 
3. to run: wl or ./wl

# Valid commands
1. load <filename>
  loads a file and constructs a binary search tree on the words in the file


2. locate <word> <n>
  outputs the number of occurences of the specified word from the beginning of the file to the nth occurence of the word

3. new
  resets the tree to be empty

4. end
  terminates the program
