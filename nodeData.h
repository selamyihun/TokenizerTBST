/**    
@file nodeData.h   
This is the header file for our nodeData class, which is   
a class to hold the token and frequency data of a node,   
it includes an overloaded < operator, an overloaded ==   
operator, and an friend overloaded << operator.    
       
         
@author Selam Yihun <selamiye@uw.edu>    
@version 1.0    
@section ASSIGNEMT Lab5    
@section DUE_DATE March 13, 2014   
*/
       
       
#ifndef NODE_DATA_H   
#define NODE_DATA_H   
       
#include <iostream>   
#include <string>   
       
using namespace std;   
       
/**     
nodeData class    
A class to hold the token and frequency data of a node,    
it includes an overloaded < operator for less than     
comparison, an overloaded == operator for equality    
comparison, and an overloaded << operator for     
outputing the frequency and token of the nodeData.    
*/
       
class nodeData {   
    friend ostream& operator<<(ostream& , const nodeData&);    
       
    public:   
        nodeData();   
        nodeData(int, string);   
        nodeData(const nodeData&);   
        bool operator<(const nodeData&); 
        bool operator>(const nodeData&); 
        bool operator==(const nodeData&);
        bool operator!=(const nodeData&);
        void incrementFrequency();   
        void setData(const nodeData&);
        int getFrequency() const;
           
    private:       
        string token;   
        int frequency;   
};   
       
#include "nodeData.cpp"   
#endif   
