#include <iostream>
using namespace std;
#ifndef DATA_H
#define DATA_H

class Data
{
    protected:
        string line;
        int lineNumber;
    public:
        Data(string line, int lineNumber);
        int getLineNumber();
        string getLine();
        void setLine(string line_);
};



#endif