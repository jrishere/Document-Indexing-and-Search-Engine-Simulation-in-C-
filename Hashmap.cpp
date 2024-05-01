#include <iostream>
#include "Hashmap.h"
using namespace std;

Hashmap::Hashmap(string line_, int lineNumber_, int hashValue_) : line(line_), lineNumber(lineNumber_), hashValue(hashValue_) {
    // The member variables should be assigned directly in the member initializer list
    // Also, avoid re-declaring the parameters using the same names as the member variables
}

int Hashmap::getLineNumber() {
    return lineNumber;
}

string Hashmap::getLine() {
    return line;
}

void Hashmap::setLine(string line_) {
    line = line_;
}

int Hashmap::getHashValue() {
    return hashValue;
}

void Hashmap::setHashValue(int hashValue_)
{
    hashValue = hashValue_;
}