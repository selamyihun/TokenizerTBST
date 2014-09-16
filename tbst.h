/**    
@file tbst.h   
This is the header file for the tbst class   
 that creates a tbst that consists of nodes that   
have a token data and the frequency of that token.    
Tbst is a threaded binary search tree that makes    
use of wasted NULL pointers in a regular binary search tree by    
making them its left child pointer point to its inorder predecessor    
and its right child pointer point to its preorder successor.   
         
       
@author Selam Yihun <selamiye@uw.edu>    
@version 1.0    
@section ASSIGNEMT Lab5    
@section DUE_DATE March 13, 2014   
*/
       
#ifndef TBST_H   
#define TBST_H   
       
#include "node.h"   
using namespace std;
int const FREQUENCY_LIMIT = 21;
       
/**    
tbst class   
A class that creates a tbst that consists of nodes that   
have a token data and the frequency of that token.   
This class has functions that insert nodes inorder,   
removes specific nodes, searches and find nodes with   
specified data, checks to see if the tree is empty.    
It also has functions that allow it to traverse the    
tree using inorder, preorder, postorder, iterativeInorder   
methods. The private member of this class is the   
root node pointer of the tree.    
*/
class tbst {   
private:   
    node* root;
    nodeData mostFrequentTokens[FREQUENCY_LIMIT];
    nodeData leastFrequentTokens[FREQUENCY_LIMIT];   
       
protected:   
    node* insertInorder(node*, node*);   
    node* removeValue(node*, nodeData&, bool);   
    node* removeNode(node*&);   
    node* removeLeftMostNode(node*, node*&, bool&, nodeData&);   
    node* findNode(node*, nodeData&) const;   
    node* findLeftMostNode(node*) const;   
    node* findRightMostNode(node*) const;   
    void inorder(void visit(nodeData&), node*) const;   
    void preorder(void visit(nodeData&), node*) const;   
    void postorder(void visit(nodeData&), node*) const;   
    void preorderCopyHelper(node*);  
    void destroyTree(node*);   
       
       
public:   
    tbst();   
    tbst(node*);   
    tbst(tbst&);   
    ~tbst();   
    bool isEmpty() const;   
    nodeData& getRootData() const;   
    void setRootData(nodeData&) const;   
    bool add(nodeData&);   
    bool remove(nodeData&);
    void removeEvenNodes();
    void getLeastFrequencies();
    void getMostFrequencies();
    void clear();   
    bool contains(nodeData&);   
    tbst& operator=(const tbst&); 
    void displayLeastAndMostFrequentTokens();
           
    void inorderTraverse(void visit(nodeData&)) const;   
    void preorderTraverse(void visit(nodeData&)) const;   
    void postorderTraverse(void visit(nodeData&)) const;   
    void iterativeInorderTraverse(void visit(nodeData&)) const; 
    void saveTokensToFile(const char*) const;  
};   
       
#include "tbst.cpp"   
#endif  
