#include <iostream>
using namespace std;
#ifndef HASHMAP_H
#define HASHMAP_H

class Hashmap
{
    protected:
        string line;
        int lineNumber;
        int hashValue;
    public:
        Hashmap(string line, int lineNumber, int hashValue);
        int getLineNumber();
        string getLine();
        int getHashValue();
        void setLine(string line_);
        void setHashValue(int hashValue_);
};



#endif