/**      
@file lab5main.cpp      
A program that creates a tbst from token and frequency pairs of a text file(s), 
displays the 21 most frequent tokens and the 21 least frequent tokens in. 
If next to last arg is lab5out.txt the results will be output to that file.  
the file(s).      
             
               
@author Selam Yihun <selamiye@uw.edu>      
@version 1.0      
@section ASSIGNEMT Lab5      
@section DUE_DATE March 13, 2014     
*/
   
#include "tbst.h"   
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
 
using namespace std;
 
const char* COMMAND_ARGUMENT_OUTPUT = "FILE";
const char* OUTPUT_FILE_NAME = "lab5out.txt";
int const MAX_FILES = 50;
int const DEFAULT_ARGC = 2;
int const ASCII_UPPERCASE_A = 65;
int const ASCII_LOWERCASE_A = 97;
int const ASCII_UPPERCASE_Z = 90;
int const ASCII_LOWERCASE_Z = 122;
int const APOSTROPHE_CHAR = '\'';
 
// prototypes for main's helper functions
void showIntroduction();
void tokenize(tbst&, char*, const bool&);
void showResults(tbst&);
void buildTree(tbst&, ifstream&);
ostream& outputFileName(ostream&, char*, clock_t&);
void addToken(tbst&, const string&);
void outputToFile(nodeData&);
 
int main(int argc, char* argv[]){
    int cmdLineArgument = 1;    // skips the first command line argument
    int totalFiles = argc;
    bool printToFile = false;
    char* defaultFileName = "hamlet.txt"; 
 
    showIntroduction();
    if (!strcmp(argv[argc-1], COMMAND_ARGUMENT_OUTPUT)){
        totalFiles--; 
        printToFile = true;
    }
 
    if (argc == 1 || (argc == DEFAULT_ARGC && printToFile)) {
        tbst frequencyTree;     
        tokenize(frequencyTree, defaultFileName, printToFile);
        showResults(frequencyTree);
        if(printToFile)
            frequencyTree.saveTokensToFile(OUTPUT_FILE_NAME);
    }   else if (argc > MAX_FILES + DEFAULT_ARGC) { 
        //maximum 50 files + 2 arguments for FILE and program name
         cerr << endl << "Input argument value is invalid; must input an "
                 << "less than or equal to " << MAX_FILES <<"files!" << 
                 endl << endl;  
            return 1;
    } 
        for (cmdLineArgument; cmdLineArgument < totalFiles; cmdLineArgument++){
            tbst frequencyTree;
            tokenize(frequencyTree, argv[cmdLineArgument], printToFile);
            showResults(frequencyTree);
            if(printToFile)
                frequencyTree.saveTokensToFile(OUTPUT_FILE_NAME);
        }
     
}
 
/**      
    showInstructions     
    Displays the description of this program.           
*/
void showIntroduction(){  
    cout << "-----------------------------------------------------------------"
         << endl  
         << "This program creates a tbst from token and frequency pairs of a"
         << " text file(s), displays the 21 most frequent tokens and the 21 "
         << "least frequent tokens in the file(s)." << endl << endl;  
}  
  
 
/**      
    tokenize      
    Opens, processes, and times the given file.      
    @param frequencyTree The tree that is built from the tokens and frequency 
    pairs from a file. 
    @param fileName The name of the file to read in and build the frequencyTree 
    with. 
    @param printToFile true if the user desires to print the results to a file, 
    fale otherwise. 
*/
void tokenize(tbst& frequencyTree, char* fileName, 
              const bool& printToFile) {
    ifstream inputFile(fileName);
     
    if (!inputFile.is_open()){
        cerr << "Could not open file: " << fileName << endl;
    } else {
        clock_t timerStart = clock();
        buildTree(frequencyTree, inputFile);
        clock_t timerEnd = clock();
        clock_t timer = timerEnd - timerStart;
 
        outputFileName(cout, fileName, timer);
 
        if (printToFile){
            ofstream outputFile(OUTPUT_FILE_NAME);
            outputFileName(outputFile, fileName, timer);
        }
    }
}
 
 
/**      
    buildTree      
    builds the tree from the given file.      
    @param frequencyTree The tree that is built from the tokens and frequency 
    pairs from a file. 
    @param inputFile The file to read in and build the frequencyTree 
*/
void buildTree(tbst& frequencyTree, ifstream& inputFile) {
    char currentToken[80];
    currentToken[0] = '\0';
 
    while (!inputFile.eof()) {
        char currentChar[2];
        currentChar[0] = inputFile.get();
        currentChar[1] = '\0';
        int currentCharAscii = (int)currentChar[0];
        string tokenValue;
         
        if ((ASCII_UPPERCASE_A <= currentCharAscii
            && currentCharAscii <= ASCII_UPPERCASE_Z)
            || (ASCII_LOWERCASE_A <= currentCharAscii 
            && currentCharAscii <= ASCII_LOWERCASE_Z)
            || currentCharAscii == APOSTROPHE_CHAR){
            strcat(currentToken, currentChar);
        } else if (currentChar[0] == ' ' || currentChar[0] == '\n' || 
             currentChar[0] == '\t') {
            tokenValue = currentToken;      
            if (currentToken[0] != '\0')
                addToken(frequencyTree, tokenValue);
            currentToken[0] = '\0';
        } else {
            if (currentToken != ""){
                tokenValue = currentToken;
                addToken(frequencyTree, tokenValue);
                currentToken[0] = '\0';
            }
            tokenValue = currentChar;
            addToken(frequencyTree, tokenValue);
        }
    }
}
 
 
/**      
    addToken      
    adds a nodeData to the tree.      
    @param frequencyTree The tree that is built from the tokens and frequency 
    pairs from a file. 
    @param tokenValue The string value of the token to be added. 
*/
void addToken(tbst& frequencyTree, const string& tokenValue) {
    nodeData* token = new nodeData(1, tokenValue);
    frequencyTree.add(*token);
}
 
 
/**      
    showResults      
    shows the results of the 21 most frequent tokens and the 21 least 
    frequent tokens in a given file.      
    @param frequencyTree The tree that is built from the tokens and frequency 
    pairs from a file. 
    @param printToFile true if the user desires to print the results to a file, 
    false otherwise. 
*/ 
void showResults(tbst& frequencyTree){
    frequencyTree.getLeastFrequencies();
    frequencyTree.getMostFrequencies();
    frequencyTree.displayLeastAndMostFrequentTokens();
}
 
 
/**      
    outputFileName      
    Displays the name of the file being processed and how long it take to 
    processe.      
    @param output The tree that is built from the tokens and frequency 
    pairs from a file. 
    @param fileName The name of the file to read in and build the frequencyTree 
    with. 
    @param timer The start time of the process. 
    @return Output Outputs the name of the file being processed and how long it  
    took to process.  
*/
ostream& outputFileName(ostream& output, char* fileName, clock_t& timer) {
    output << "-------------------------------------------------------" << endl
           << "File being processed: " << fileName << "\tTime elapsed to "
           << "process file = " <<(float)timer / (float)CLOCKS_PER_SEC << 
           " seconds." << endl << endl;
    return output;
}
