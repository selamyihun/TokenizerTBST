/**    
@file node.h    
A class of each node which is going to include nodeData object to    
hold the token and frequency data, 2 pointers to Node: leftChildPtr   
rightChildPtr, and the boolean for isLeftThread and isRightThread.    
         
         
@author Selam Yihun <selamiye@uw.edu>    
@version 1.0    
@section ASSIGNEMT Lab5    
@section DUE_DATE March 13, 2014   
*/
       
#ifndef NODE_H   
#define NODE_H   
       
#include "nodeData.h"   
using namespace std;   
       
class node {   
private:   
    nodeData* item;   
    node* leftChildPtr;   
    node* rightChildPtr;   
    bool isLeftThread, isRightThread;   
       
public:   
    node();   
    node(nodeData&);   
    ~node();  
       
    void setItem(nodeData&);   
    void removeItem();  
    nodeData& getItem() const;   
           
    node* getLeftChildPtr() const;   
    node* getRightChildPtr() const;   
       
    void setLeftChildPtr(node*);   
    void setRightChildPtr(node*);   
    void setisLeftThread(bool);   
    void setisRightThread(bool);   
    bool getisLeftThread() const;   
    bool getisRightThread() const;   
    bool isLeaf();   
    bool hasOneChild();   
    node* nextInOrder();   
       
};   
       
#include "node.cpp"   
#endif 
