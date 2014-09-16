/**    
@file nodeData.cpp   
This is the source file for our nodeData class, which is   
a class to hold the token and frequency data of a node,   
it includes an overloaded < operator.   
       
@author Selam Yihun <selamiye@uw.edu>    
@version 1.0    
@section ASSIGNEMT Lab5    
@section DUE_DATE March 13, 2014   
*/
       
#ifndef NODE_DATA_CPP   
#define NODE_DATA_CPP   
       
#include "nodeData.h"   
       
/**    
    Constructor that initializes the frequency to zero   
    and the token to an empty string.    
*/
nodeData::nodeData(){   
    frequency = 0;   
    token = "";   
}   
       
       
       
/**    
    Constructor that initializes the frequency to theFrequency   
    and the token to theToken.   
    @param theFrequency The int to set this frequency to   
    @param theToken The string to set this token to   
*/
nodeData::nodeData(int theFrequency, string theToken) {   
    frequency = theFrequency;   
    token = theToken;   
}   
       
/**    
    Copy Constructor    
    Creates a copy of a nodeData.    
    @param rightNodeData The nodeData that is to be copied.
*/
nodeData::nodeData(const nodeData& rightNodeData) {   
    frequency = rightNodeData.frequency;   
    token = rightNodeData.token;   
}   
       
       
/**    
    Operator<   
    Allows less than comparison between nodeDatas    
    @param rightNodeData the righthand side nodeData to be compared     
            with this nodeData    
    @return True if this nodeData is less than rightNodeData;    
            false otherwise.    
*/
bool nodeData::operator<(const nodeData& rightNodeData) {   
    return (token < rightNodeData.token);   
}  
   
/**    
    Operator>   
    Allows greater than comparison between nodeDatas    
    @param rightNodeData the righthand side nodeData to be compared     
            with this nodeData    
    @return True if this nodeData is greater than rightNodeData;    
            false otherwise.    
*/
bool nodeData::operator>(const nodeData& rightNodeData) {   
    return (token > rightNodeData.token);   
}  
       
 
 
 
/**    
    Operator==   
    Allows equality comparison between nodeDatas    
    @param rightNodeData the righthand side nodeData to be compared     
            with this nodeData    
    @return True if this nodeData is equal to rightNodeData;    
            false otherwise.    
*/
bool nodeData::operator==(const nodeData& rightNodeData) {   
    return (token == rightNodeData.token);   
}   
 
/**    
    Operator!=   
    Allows inequality comparison between nodeDatas    
    @param rightNodeData the righthand side nodeData to be compared     
            with this nodeData    
    @return True if this nodeData is not equal to rightNodeData;    
            false otherwise.    
*/
bool nodeData::operator!=(const nodeData& rightNodeData) {   
    return !(token == rightNodeData.token);   
}  
 
/**    
    incrementFrequency   
    increments the frequency of this nodeData.   
*/
void nodeData::incrementFrequency() {   
    frequency++;   
}   
       
       
/**    
    setData   
    sets the data of this nodeData to the data   
    of theNodeData   
    @param theNodeData the nodeData to be copied   
*/
void nodeData::setData(const nodeData& theNodeData) {   
    this->token = theNodeData.token;   
    this->frequency = theNodeData.frequency;   
}   
 
/**    
    getFrequency   
    gets the frequency of this nodeData  
    @return returns the frequency 
*/
int nodeData::getFrequency() const {   
    return this->frequency;  
} 
 
       
/**    
    Output operator <<   
        
    Allows the output of the contents of nodeData class   
    @param ostream output is the output to be produced    
    @param SortSetArray is the array to be printed out    
    @return output    
*/
ostream& operator<<(ostream& output, const nodeData& rightNodeData) {    
   output << " " << rightNodeData.token << " " << rightNodeData.frequency;   
            
   return output;    
}    
       
#endif   
