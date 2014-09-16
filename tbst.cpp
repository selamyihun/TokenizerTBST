/**    
@file tbst.h   
This is the implementation file for the tbst class   
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
       
#ifndef TBST_CPP   
#define TBST_CPP   
       
#include "tbst.h"   
#include <fstream>
using namespace std;
int const MAX_PER_LINE = 7;
 
       
/**   
    Default Constructor   
    Sets root node pointer to NULL   
*/
tbst::tbst(): root(NULL) {}    
           
/**   
    Constructor   
    Creates a tbst with the given node as the root   
    @param theRoot the node* for the tbst to be created   
*/
tbst::tbst(node* theRoot) {   
    root = theRoot;   
}   
       
       
/**   
    Copy constructor   
    Creates a deep copy of this tbst   
    @param tree The tree to be copied   
*/
tbst::tbst(tbst& tree) {   
    *this = tree;   
}   
       
/**   
    destructor   
    Deletes the tree and returns memory   
*/
tbst::~tbst() {   
    this->clear();   
}   
       
/**   
    isEmpty   
    Checks whether a tree is empty or not   
    @return True if the tree is empty, false otherwise   
*/
bool tbst::isEmpty() const {   
    return (root == NULL);   
}   
       
/**   
    getRootData   
    Gets the root node's nodeData   
    @return nodeData of the root   
*/
nodeData& tbst::getRootData() const {   
    return this->root->getItem();   
}   
       
/**   
    setRootData   
    Sets the root node's nodeData   
    @param theRoot nodeData of the root   
*/
void tbst::setRootData(nodeData& theRoot) const {   
    this->root->setItem(theRoot);   
}   
       
/**   
    add   
    Adds a new item to the threaded binary search tree   
    @param theNewData nodeData of the new item   
    @return true if the add is is successful,false otherwise
*/
bool tbst::add(nodeData& theNewData) {   
    node* newNodePtr = new node(theNewData);   
    root = insertInorder(root, newNodePtr);   
       
    return true;   
}   
       
/**   
    Remove   
    Removes the given data from this BST   
    @param target The nodeData to be removed   
    @return true if remove was successful, false otherwise   
*/
bool tbst::remove(nodeData& target) {   
    bool success = false;   
    root = removeValue(root, target, success);   
    return success;   
}   
 
/**   
    removeEvenNodes   
    Removes the nodes whose frequencies are even
    numbers in the given data from this BST
*/
void tbst::removeEvenNodes() {    
    node* currentNode = findLeftMostNode(root);
     
    while (currentNode != NULL) {   
        nodeData theItem = currentNode->getItem();   
        if (theItem.getFrequency() % 2 == 0) {
            //remove(theItem);
        }
        currentNode = currentNode->nextInOrder();
    }
}
 
/**   
    Clear   
    Clears the threaded binary search tree   
    can be used by the client while destroyTree   
    is protected   
*/
void tbst::clear() {   
    destroyTree(root);   
}   
       
       
/**   
    contains   
    Checks to see if a specific nodeData is in the threaded binary search tree   
    @param anEntry the nodeData that is/isn't contained in this tbst   
    @return true if the nodeData is contained in the binary search tree   
*/
bool tbst::contains(nodeData& anEntry) {   
    return !(findNode(root, anEntry) == NULL);   
}   
       
       
/**   
    inorder   
    This method recursively traverses the binary search tree inorder   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
    @param subTreePtr Node* of the sub tree that is recursively passed   
*/
void tbst::inorder(void visit(nodeData&), node* subTreePtr) const {   
    if (subTreePtr != NULL) {   
        if (!subTreePtr->getisLeftThread())   
            inorder(visit, subTreePtr->getLeftChildPtr());   
        nodeData temp = subTreePtr->getItem();   
        visit(temp);   
        if (!subTreePtr->getisRightThread())   
            inorder(visit, subTreePtr->getRightChildPtr());   
    }   
}   
       
/**   
    preorder   
    This method recursively traverses the binary search tree in preorder   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
    @param subTreePtr Node* of the sub tree that is recursively passed   
*/
void tbst::preorder(void visit(nodeData&), node* subTreePtr) const {   
    if (subTreePtr != NULL) {   
        nodeData temp = subTreePtr->getItem();   
        visit(temp);   
        if (!subTreePtr->getisLeftThread())   
            preorder(visit, subTreePtr->getLeftChildPtr());   
        if (!subTreePtr->getisRightThread())   
            preorder(visit, subTreePtr->getRightChildPtr());   
    }   
}   
       
/**   
    postorder   
    This method recursively traverses the binary search tree in postorder   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
    @param subTreePtr Node* of the sub tree that is recursively passed   
*/
void tbst::postorder(void visit(nodeData&), node* subTreePtr) const {   
    if (subTreePtr != NULL) {   
        if (!subTreePtr->getisLeftThread())   
            postorder(visit, subTreePtr->getLeftChildPtr());   
        if (!subTreePtr->getisRightThread())   
            postorder(visit, subTreePtr->getRightChildPtr());   
        nodeData temp = subTreePtr->getItem();   
        visit(temp);   
    }   
}   
       
/**   
    preorderCopyHelper   
    This method recursively traverses given binary search tree in preorder  
    and adds each node to this tree for copying the tree  
    @param subTreePtr Node* of the sub tree that is recursively passed   
*/
void tbst::preorderCopyHelper(node* subTreePtr)  {   
    if (subTreePtr != NULL) {   
        nodeData* temp = new nodeData;  
        temp->setData(subTreePtr->getItem());   
        this->add(*temp);  
        if (!subTreePtr->getisLeftThread())   
            preorderCopyHelper(subTreePtr->getLeftChildPtr());   
        if (!subTreePtr->getisRightThread())   
            preorderCopyHelper(subTreePtr->getRightChildPtr());   
    }   
}   
       
       
/**   
    destroyTree   
    This method recursively traverses the binary search tree in postorder   
    while destroying each node   
    @param subTreePtr Node* of the sub tree that is recursively passed   
*/
void tbst::destroyTree(node* subTreePtr) {   
    if (subTreePtr != NULL) {   
        if(!subTreePtr->getisLeftThread())   
            destroyTree(subTreePtr->getLeftChildPtr());   
        if(!subTreePtr->getisRightThread())   
            destroyTree(subTreePtr->getRightChildPtr());   
        subTreePtr->removeItem();  
        delete subTreePtr;   
        subTreePtr = NULL;   
    }   
}   
       
/**   
    inorderTraverse   
    This method calls inorder function for the inorder traversal of the BST   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
*/
void tbst::inorderTraverse(void visit(nodeData&)) const {   
    inorder(visit, root);   
}   
       
       
/**   
    preorderTraverse   
    This method calls preorder function for the preorder traversal of the BST   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
*/
void tbst::preorderTraverse(void visit(nodeData&)) const {   
    preorder(visit, root);   
}   
       
       
/**   
    postorderTraverse   
    This method calls postorder function for the postorder traversal of the BST   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node   
*/
void tbst::postorderTraverse(void visit(nodeData&)) const {   
    postorder(visit, root);   
}   
       
       
/**   
    iterativeInorderTraverse   
    This method iteratively traverses the binary search tree inorder   
    by using the threads   
    @param visit is a client-defined function that performs an operation   
            on/with the data in each visited node    
*/
void tbst::iterativeInorderTraverse(void visit(nodeData&)) const {   
    node* currentNode = findLeftMostNode(root);
    int lineCount = 0;
    while (currentNode != NULL) {   
        nodeData theItem = currentNode->getItem();   
        visit(theItem);   
        currentNode = currentNode->nextInOrder();
        lineCount++;
        if (lineCount == MAX_PER_LINE) {
            cout << endl;
            lineCount = 0;
        }
    }
    cout << endl <<endl;
}   
 
 
/**   
    saveTokensToFile 
    This method iteratively traverses the binary search tree inorder   
    by using the threads to print to a file
    @param outputFileName the name of the file to be printed on   
    
*/
void tbst::saveTokensToFile(const char* outputFileName) const {   
    node* currentNode = findLeftMostNode(root);
    int lineCount = 0;
    while (currentNode != NULL) {   
        nodeData theItem = currentNode->getItem();   
        ofstream outputFile;
        outputFile.open(outputFileName, std::ios_base::app);
        outputFile << theItem;   
        currentNode = currentNode->nextInOrder();
        lineCount++;
        if (lineCount == MAX_PER_LINE) {
            outputFile << endl;
            lineCount = 0;
        }
    }
}   
       
/**   
    operator=    
    This is the assignment operator for the tbst class, it copies the   
    rightside tbst to this tbst   
    @param rightSide a tbst object to be assigned from   
*/
tbst& tbst::operator=(const tbst& rightTree) {   
    if(this->root == rightTree.root) {   
      return *this;   
    }   
    this->clear();   
    this->preorderCopyHelper(rightTree.root);  
     
    return *this;  
}   
       
/**   
    insertInorder   
    Recursively finds where the given node should be placed and insert it in    
    a leaf at that point   
    @param subTreePtr the pointer to the tree to insert into   
    @param newNode the node to insert into the tree subTreePtr points to   
    @return the node that subTreePtr point to   
*/
node* tbst::insertInorder(node* subTreePtr, node* newNode) {   
    if (subTreePtr == NULL) {   
        return newNode;   
    } else if (newNode->getItem() < subTreePtr->getItem()) {   
        if (!subTreePtr->getisLeftThread()) {   
            node* temp = insertInorder(subTreePtr->getLeftChildPtr(), newNode);   
            subTreePtr->setLeftChildPtr(temp);   
        } else {   
            newNode->setLeftChildPtr(subTreePtr->getLeftChildPtr());   
            newNode->setisLeftThread(true);   
            subTreePtr->setLeftChildPtr(newNode);   
            subTreePtr->setisLeftThread(false);   
        }   
        if (subTreePtr->getLeftChildPtr()->isLeaf()) {   
            subTreePtr->getLeftChildPtr()->setRightChildPtr(subTreePtr);   
            subTreePtr->getLeftChildPtr()->setisRightThread(true);   
        }   
    } else if (newNode->getItem() == subTreePtr->getItem()) {   
        subTreePtr->getItem().incrementFrequency();
        newNode->removeItem();
        delete newNode;   
        newNode = NULL;   
    } else {   
        if (!subTreePtr->getisRightThread()) {   
            node* temp = insertInorder(subTreePtr->getRightChildPtr(),newNode);   
            subTreePtr->setRightChildPtr(temp);   
        } else {   
            newNode->setRightChildPtr(subTreePtr->getRightChildPtr());   
            newNode->setisRightThread(true);   
            subTreePtr->setRightChildPtr(newNode);   
            subTreePtr->setisRightThread(false);   
        }   
        if (subTreePtr->getRightChildPtr()->isLeaf()) {   
            subTreePtr->getRightChildPtr()->setLeftChildPtr(subTreePtr);   
            subTreePtr->getRightChildPtr()->setisLeftThread(true);   
        }   
    }   
    return subTreePtr;   
}   
       
/**   
    removeValue   
    Removes the given target from the tree while maintaining a binary   
    search three   
    @param subTreePtr The pointer to thetree to remove a value from   
    @param target The value to be removed   
    @param success True if the value is removed, false otherwise   
    @return A pointer to the node at this tree location after the value    
    is removed   
*/
node* tbst::removeValue(node* subTreePtr, nodeData& target, bool success) {   
    if (subTreePtr == NULL) {   
        success = false;   
        return NULL;   
    } else if (subTreePtr->getItem() == target) {   
        subTreePtr = removeNode(subTreePtr);    
        success = true;   
        return subTreePtr;   
    } else if (target < subTreePtr->getItem()) {   
        if (subTreePtr->getLeftChildPtr()->isLeaf() &&   
            subTreePtr->getLeftChildPtr()->getItem() == target){   
            node* temp = subTreePtr->getLeftChildPtr();   
            subTreePtr->setLeftChildPtr(temp->getLeftChildPtr());   
            if(temp->getisLeftThread())   
                subTreePtr->setisLeftThread(true);   
            removeValue(temp, target, success);   
        } else if (!subTreePtr->getisLeftThread()) {   
            node* temp = removeValue(subTreePtr->getLeftChildPtr(), target,    
                success);   
            subTreePtr->setLeftChildPtr(temp);   
        }   
        return subTreePtr;   
               
    } else {   
        if (subTreePtr->getRightChildPtr()->isLeaf() &&   
            subTreePtr->getRightChildPtr()->getItem() == target){   
            node* temp = subTreePtr->getRightChildPtr();   
            subTreePtr->setRightChildPtr(temp->getRightChildPtr());   
            if(temp->getisRightThread())   
                subTreePtr->setisRightThread(true);   
            removeValue(temp, target, success);   
        } else if (!subTreePtr->getisRightThread()) {   
            node* temp = removeValue(subTreePtr->getRightChildPtr(), target,    
                success);   
            subTreePtr->setRightChildPtr(temp);   
        }   
        return subTreePtr;   
    }   
}   
       
       
/**   
    removeNode   
    Removes the item in the node, N, to which theNode points   
    @param theNode The node to be removed from the tree   
    @return A pointer to the node at this tree location after N is deleted  
*/
node* tbst::removeNode(node*& theNode) {   
    if (theNode->isLeaf()) {   
        theNode->removeItem();  
        delete theNode;   
        theNode = NULL;   
        return theNode;   
    } else if (theNode->hasOneChild()) {   
        node* nodeToConnect;   
        if(theNode->getLeftChildPtr() == NULL){  
            nodeToConnect = theNode->getRightChildPtr();   
            node* temp = findLeftMostNode(theNode->getRightChildPtr());  
            temp->setLeftChildPtr(NULL);  
            temp->setisLeftThread(false);  
        } else if(theNode->getRightChildPtr() == NULL){  
            nodeToConnect = theNode->getLeftChildPtr();   
            node* temp = findRightMostNode(theNode->getLeftChildPtr());  
            temp->setRightChildPtr(NULL);  
            temp->setisRightThread(false);  
        } else {  
        if (theNode->getLeftChildPtr() != NULL && !theNode->getisLeftThread()){   
            nodeToConnect = theNode->getLeftChildPtr();   
            if (theNode->getisRightThread())   
                nodeToConnect->setisRightThread(true);   
            else
                nodeToConnect->setisRightThread(false);   
            nodeToConnect->setRightChildPtr(theNode->getRightChildPtr());   
        } else {    
            nodeToConnect = theNode->getRightChildPtr();            
            if (theNode->getisLeftThread())   
                nodeToConnect->setisLeftThread(true);  
            else
                nodeToConnect->setisLeftThread(false);   
            nodeToConnect->setLeftChildPtr(theNode->getLeftChildPtr());  
        }   
        }  
        theNode->removeItem();  
        delete theNode;   
        theNode = NULL;   
        return nodeToConnect;   
    } else {   
        node* rightChild;  
        nodeData newNodeValue;  
        bool isRightThread;  
        if(theNode->getRightChildPtr()->isLeaf()){   
            removeLeftMostNode(theNode->getRightChildPtr(),rightChild,   
                isRightThread, newNodeValue);   
            theNode->setItem(newNodeValue);   
            theNode->setRightChildPtr(rightChild);   
            if (isRightThread)   
                theNode->setisRightThread(true);   
            else
                theNode->setisRightThread(false);   
        } else {   
            node* temp = removeLeftMostNode(theNode->getRightChildPtr(),    
                rightChild, isRightThread, newNodeValue);   
            theNode->setItem(newNodeValue);   
            theNode->setRightChildPtr(temp);   
            node * temp2 = findLeftMostNode(theNode->getRightChildPtr());   
            temp2->setLeftChildPtr(theNode);   
            temp2->setisLeftThread(true);   
        }   
        return theNode;   
    }   
}   
       
/**     
    removeLeftmostNode     
    Removes the leftmost node in the left subtree of the node     
    @param nodePtr The node to be removed from the tree 
    @param rightChild the right child of the inorder successor
    @param isRightThread whether or not the node isRightThread 
    @param inorderSuccessor The indorder successor of the node to be removed    
    @return A pointer to the revised node tree     
*/
node* tbst::removeLeftMostNode(node* nodePtr, node*& rightChild,  
                        bool& isRightThread, nodeData& inorderSuccessorData) {   
    if (nodePtr->getLeftChildPtr() ==  NULL ||   
        nodePtr->getisLeftThread()) {   
        inorderSuccessorData = nodePtr->getItem();  
        rightChild = nodePtr->getRightChildPtr();   
        isRightThread = nodePtr->getisRightThread();  
                       
        return removeNode(nodePtr);   
    } else {   
        node* temp = removeLeftMostNode(nodePtr->getLeftChildPtr(),    
            rightChild, isRightThread, inorderSuccessorData);   
        if(temp == NULL)   
            nodePtr->setLeftChildPtr(temp);   
        return nodePtr;   
    }   
}   
       
/**   
    findNode   
    Locates the node in the binary search tree to which subTreeptr points   
    that contains the value target.    
    @param subTreePtr The Node pointer for the SubTree of the BST   
    @param target The indorder successor of the node to be removed   
    @return Either a pointer to the located node or NULL if not found   
*/
       
node* tbst::findNode(node* subTreePtr, nodeData& target) const {   
    if (subTreePtr == NULL) {   
        return NULL;   
    } else if (subTreePtr->getItem() == target) {   
        return subTreePtr;   
    } else if (target < subTreePtr->getItem()) {   
        if(!subTreePtr->getisLeftThread())  
            return findNode(subTreePtr->getLeftChildPtr(), target);  
        else
            return NULL;  
    } else {   
        if(!subTreePtr->getisLeftThread())  
            return findNode(subTreePtr->getRightChildPtr(), target);   
        else
            return NULL;  
    }   
}   
       
       
/**   
    findLeftMostNode   
    Finds the leftmost node in the left subtree of the node   
    @param nodePtr The pointer to the node where the search starts   
    @return A pointer to the left most node  
*/
node* tbst::findLeftMostNode(node* nodePtr) const {   
           
    if (nodePtr->getLeftChildPtr() ==  NULL ||   
        nodePtr->getisLeftThread()) {   
        return nodePtr;   
    } else {   
        node* temp = findLeftMostNode(nodePtr->getLeftChildPtr());   
        return temp;   
    }   
}   
       
       
/**   
    findRightMostNode   
    Finds the rightmost node in the left subtree of the node   
    @param nodePtr The pointer to the node where the search starts  
    @return A pointer to the right most node  
*/
node* tbst::findRightMostNode(node* nodePtr) const {   
           
    if (nodePtr->getRightChildPtr() ==  NULL ||   
        nodePtr->getisRightThread()) {   
        return nodePtr;   
    } else {   
        node* temp = findRightMostNode(nodePtr->getRightChildPtr());   
        return temp;   
    }   
}   
       
/**     
    getLeastFrequencies     
    Gets the 21 least frequent tokens in a given file     
*/
void tbst::getLeastFrequencies(){
    node* currentNode = findLeftMostNode(root);
    int frequencyCount = 0;
    int correctedPosition = 0;
    bool canInsert = true;
     
    while (currentNode != NULL) {   
        nodeData theItem = currentNode->getItem();   
        if(frequencyCount == 0){
            leastFrequentTokens[0] = theItem; 
            frequencyCount++;
        } else if (frequencyCount > 0){
            for (int index = 0; index < FREQUENCY_LIMIT; index++){
                if(theItem.getFrequency() <
                    leastFrequentTokens[index].getFrequency()) {
                    for (int index2 = frequencyCount - 1; index2 > index - 1;
                        index2--)
                        if (!(frequencyCount == FREQUENCY_LIMIT && index2 == 
                        frequencyCount - 1)) {
                        leastFrequentTokens[index2 + 1] = 
                        leastFrequentTokens[index2];
                    }
                    correctedPosition = index;
                    canInsert = true;
                    break;
                } else if (theItem.getFrequency() >
                    leastFrequentTokens[index].getFrequency() &&
                    index == frequencyCount){
                    correctedPosition = frequencyCount;
                    canInsert = true;
                    break;
                } else if (frequencyCount == FREQUENCY_LIMIT) {
                    canInsert = false;
                }
            }
            if (canInsert == true) 
                leastFrequentTokens[correctedPosition] = theItem;
            if (frequencyCount < FREQUENCY_LIMIT)
                frequencyCount++;
        }       
        currentNode = currentNode->nextInOrder();
    }       
}
 
 
/**     
    getMostFrequencies     
    Gets the 21 most frequent tokens in a given file     
*/
void tbst::getMostFrequencies(){
    node* currentNode = findLeftMostNode(root);
    int frequencyCount = 0;
    int correctedPosition = 0;
    bool canInsert = true;
     
    while (currentNode != NULL) {   
        nodeData theItem = currentNode->getItem();   
        if(frequencyCount == 0){
            mostFrequentTokens[0] = theItem; 
            frequencyCount++;
        } else if (frequencyCount > 0){
            for (int index = 0; index < FREQUENCY_LIMIT; index++){
                if(theItem.getFrequency() >
                    mostFrequentTokens[index].getFrequency()) {
                    for (int index2 = frequencyCount - 1; index2 > index - 1;
                        index2--){
                        if (!(frequencyCount == FREQUENCY_LIMIT && index2 == 
                            frequencyCount - 1))
                            mostFrequentTokens[index2 + 1] = 
                            mostFrequentTokens[index2];
                    }
                    correctedPosition = index;
                    canInsert = true;
                    break;
                } else if (theItem.getFrequency() <
                    mostFrequentTokens[index].getFrequency() &&
                    index == frequencyCount &&
                    frequencyCount < FREQUENCY_LIMIT){
                    correctedPosition = frequencyCount;
                    canInsert = true;
                    break;
                } else if (frequencyCount == FREQUENCY_LIMIT) {
                    canInsert = false;
                }
            }
            if (canInsert == true) 
                mostFrequentTokens[correctedPosition] = theItem;            
            if (frequencyCount < FREQUENCY_LIMIT)
                frequencyCount++;
        }       
        currentNode = currentNode->nextInOrder();
    }       
}
 
/**     
    displayLeastAndMostFrequentTokens     
    Displays the least 21 and the most 21 frequencies of this
    tree    
*/ 
void tbst::displayLeastAndMostFrequentTokens() {
    int lineCount = 0;
 
    cout << endl << "Displaying the Most Frequent Tokens:" << endl;
    for (int index = 0; index < FREQUENCY_LIMIT; index++)  {   
        cout << mostFrequentTokens[index];
        lineCount++;
        if (lineCount == MAX_PER_LINE) {
            cout << endl;
            lineCount = 0;
        }
    }
    lineCount = 0;
 
    cout << endl << "Displaying the Least Frequent Tokens:" << endl;
    for (int index = 0; index < FREQUENCY_LIMIT; index++)  {   
        cout << leastFrequentTokens[index];
        lineCount++;
        if (lineCount == MAX_PER_LINE) {
            cout << endl;
            lineCount = 0;
        }
    }
}
 
       
#endif 
