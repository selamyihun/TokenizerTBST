/**    
@file node.cpp    
The implementation of a class of each node which is going to include nodeData    
object to hold the token and frequency data, 2 pointers to Node: leftChildPtr   
rightChildPtr, and the boolean for isLeftThread and isRightThread.    
         
        
@author Selam Yihun <selamiye@uw.edu>    
@version 1.0    
@section ASSIGNEMT Lab5    
@section DUE_DATE March 13, 2014   
*/
       
#ifndef NODE_CPP   
#define NODE_CPP   
       
#include "node.h"   
using namespace std;   
       
/**   
    Default Constructor   
    Sets item, leftChildPtr, and RightChildPtr to NULL and sets    
    isLeftThread and isRightThread to false   
*/
node::node(): item(NULL), leftChildPtr(NULL), rightChildPtr(NULL),    
    isLeftThread(false), isRightThread(false){}   
       
/**    
    Constructor that sets the token and frequency to a given value.   
    @param theNodeData The nodeData to set this node to   
*/ 
node::node(nodeData& theNodeData) {   
    item = &theNodeData;   
    leftChildPtr = NULL;   
    rightChildPtr = NULL;   
    isLeftThread = false;   
    isRightThread = false;   
}   
     
     
/**    
    Default Destructor   
*/ 
node::~node() {   
}   
       
/**   
    setItem   
    Sets the data of this node   
    @param theNodeData the Node of which you want the data from   
    @return The data of a given node   
*/
void node::setItem(nodeData& theNodeData) {   
    if(item == NULL)   
        item = &theNodeData;   
       
    item->setData(theNodeData);    
}   
     
/**   
    removeItem  
    Deletes the item and sets the pointer to NULL  
*/
void node::removeItem() {   
    delete item;  
    item = NULL;  
}   
       
       
/**   
    getItem   
    Gets the data of this node   
    @param theNodeData the Node of which you want the data from   
    @return The data of a given Node   
*/
nodeData& node::getItem() const {   
    return *item;   
}   
       
/**    
    getLeftChildPtr   
    This method gets the left child of the node.    
    @return Node, the pointer to the left child of the node   
*/
node* node::getLeftChildPtr() const {   
    return leftChildPtr;   
}   
       
/**    
    getRightChildPtr   
    This method gets the right child of the node.    
    @return Node, the pointer to the left child of the node   
*/
node* node::getRightChildPtr() const {   
    return rightChildPtr;   
}   
       
/**    
    setleftChildPtr   
    This method sets the left child of the node.    
    @param  futureLeftChildPtr, the node to be assigned as   
            this node's left child   
*/
void node::setLeftChildPtr(node* futureLeftChildPtr) {   
    leftChildPtr = futureLeftChildPtr;   
}   
       
/**    
    setRightChildPtr   
    This method sets the right child of the node.    
    @param  futureRightChildPtr, the node to be assigned   
            as this node's right child   
*/
void node::setRightChildPtr(node* futureRightChildPtr) {   
    rightChildPtr = futureRightChildPtr;   
}   
       
/**    
    setisLeftThread   
    This method sets the boolean value of isLeftThread of the node.    
    @param  isThread, sets the value of left thread true or false   
*/
void node::setisLeftThread(bool isThread) {   
    isLeftThread = isThread;   
}   
       
/**    
    setisRightThread   
    This method sets the boolean value of isRightThread of the node.    
    @param  isThread, sets the value of right thread true or false   
*/
void node::setisRightThread(bool isThread) {   
    isRightThread = isThread;   
}   
       
/**    
    getisLeftThread   
    This method gets the left thread child of the node.    
    @return true, if the left child is threaded   
*/
bool node::getisLeftThread() const {   
    return isLeftThread;   
}   
       
/**    
    getisRightThread   
    This method gets the right thread child of the node.    
    @return true, if the right child is threaded   
*/
bool node::getisRightThread() const {   
    return isRightThread;   
}   
       
/**    
    isLeaf   
    This method checks whether or not the node is a leaf in the    
    threaded binary search tree.   
    @return True if node is a leaf, false otherwise   
*/
bool node::isLeaf() {   
    if((leftChildPtr == NULL && rightChildPtr == NULL) ||    
        (isLeftThread == true && isRightThread == true) ||    
        (leftChildPtr == NULL && isRightThread == true) ||    
        (rightChildPtr == NULL && isLeftThread == true)) {   
        return true;   
    } else {    
        return false;   
    }   
}   
       
/**    
    hasOneChild   
    This method checks whether or not the node has one child   
    @return True if node has one child, false otherwise   
*/
bool node::hasOneChild() {   
    return (leftChildPtr != NULL && rightChildPtr == NULL &&   
            isLeftThread == false && isRightThread == false) ||    
            (rightChildPtr != NULL && leftChildPtr == NULL &&   
            isLeftThread == false && isRightThread == false) ||   
            (rightChildPtr != NULL && leftChildPtr != NULL &&   
            isLeftThread == false && isRightThread == true) ||   
            (rightChildPtr != NULL && leftChildPtr != NULL &&   
            isLeftThread == true && isRightThread == false);   
}   
       
/**    
    nextInOrder   
    Finds the next indorder Node by using the threads   
    @return temp the next inorder node of the threaded BST   
*/
node* node::nextInOrder() {   
    node* temp = rightChildPtr;   
    if (rightChildPtr == NULL) {   
        return NULL;   
    }   
    if (isRightThread) {   
        return temp;   
    }   
    while (!temp->isLeftThread) {   
        temp = temp->leftChildPtr;   
    }   
    return temp;   
}   
       
#endif   
