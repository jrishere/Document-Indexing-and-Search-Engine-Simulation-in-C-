#include <iostream>
#include "Data.h"
using namespace std;

Data::Data(string line_, int lineNumber_) : line(line_), lineNumber(lineNumber_) {
    line = line_;
    lineNumber = lineNumber;
}

int Data::getLineNumber() {
    return lineNumber;
}

string Data::getLine() {
    return line;
}
void Data::setLine(string line_)
{
    line = line_;
}