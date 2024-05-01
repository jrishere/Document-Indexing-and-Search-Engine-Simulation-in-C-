#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include "Data.cpp"
#include "Hashmap.cpp"

using namespace std;

bool compareStrings(const string &a, const string &b) {
    return a < b;
}

string cleanWord(const string& word) {
    string cleanWord = "";
    for (char c : word) {
        if (isalnum(c)) {  
            cleanWord += tolower(c);
        }
    }
    return cleanWord;
}

vector<int> listSingleWord(string in, vector<Data> vocab) {
    vector<string> words;
    vector<int> result;

    string line = in;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        // clean and lowercase the word
        string cleanedWord = cleanWord(word);
        // if the cleaned word is not empty, add it to the vocabulary
        if (!cleanedWord.empty()) {
            words.push_back(cleanedWord);
        }
    }

    string singleWord;
    for (const string& word : words) {
        // Assuming there is only one word in the list for single-word search
        singleWord = word;
        break;
    }

    // Check if the single word is present in each line
    for (int i = 0; i < vocab.size(); i++) {
        if (vocab[i].getLine() == singleWord) {
            result.push_back(vocab[i].getLineNumber());
        }
    }

    return result;
}

vector<int> multipleNOT(vector<string> words, vector<Data> vocab) {
    vector<int> result;

    // Find the positions of "NOT" in the input
    string notWord1 = words[1];
    string notWord2 = words[4];
    string op = words[2];

    vector<int> badLines;

    for(int i = 0; i < vocab.size(); i++) {
        if(op == "and")
            {
            if(vocab[i].getLine() == notWord1 || vocab[i].getLine() == notWord2)
            {
                badLines.push_back(vocab[i].getLineNumber());
            }
        }
        else if(op == "or")
        {
            if(vocab[i].getLine() == notWord1 || vocab[i].getLine() == notWord2)
                continue;
            else
                result.push_back(vocab[i].getLineNumber());
        }
    }
    for(int i = 0; i < vocab.size(); i++) {
        bool isBadLine = false;
        for(int j = 0; j < badLines.size(); j++) {
            if(vocab[i].getLineNumber() == badLines[j]) {
                isBadLine = true;
                break;
            }
        }
        if(!isBadLine) {
            result.push_back(vocab[i].getLineNumber());
        }
    }
    cout << endl;

    return result;
}

vector<int> listNOT(string in, vector<Data> vocab) {
    vector<string> words;
    vector<int> result;

    string line = in;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        // clean and lowercase the word
        string cleanedWord = cleanWord(word);
        // if the cleaned word is not empty, add it to the vocabulary
        if (!cleanedWord.empty()) {
            words.push_back(cleanedWord);
        }
    }

    cout << endl;
    int amntNots = 0;
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "not") {
            amntNots += 1;
        }
    }
    if(amntNots == 1)
    {
        // looks for words that are NOT
        string notWord;
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == "not") {
                notWord = words[i + 1];
            }
        }
        string andWord;
        // ex: (NOT be) AND a
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == "and" && words[i + 1] != "not") {
                andWord = words[i + 1];
            }
        }
        for (int i = 0; i < vocab.size(); i++) {
            if (vocab[i].getLine() == andWord) {
                // check if second word is equal to not word
                for (int j = 0; j < vocab.size(); j++) {
                    if (vocab[j].getLine() == notWord && vocab[j].getLineNumber() == vocab[i].getLineNumber()) {
                        // Skip this iteration if "AND" and "NOT" words are in the same line
                        continue;
                    } else if (vocab[j].getLineNumber() == vocab[i].getLineNumber()) {
                        // Check if the line contains the "notWord"
                        bool containsNotWord = false;
                        for (int k = 0; k < vocab.size(); k++) {
                            if (vocab[k].getLine() == notWord && vocab[k].getLineNumber() == vocab[i].getLineNumber()) {
                                containsNotWord = true;
                                break;
                            }
                        }
                        if (!containsNotWord) {
                            result.push_back(vocab[i].getLineNumber());
                        }
                    }
                }
            }
        }
    }
    else if(amntNots >> 1)
    {
        result = multipleNOT(words, vocab);
    }
    int n = result.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                // Swap result[j] and result[j + 1]
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    // Remove duplicates from result
    vector<int> uniqueResult;
    for (int i = 0; i < result.size(); i++) {
        bool isDuplicate = false;
        for (int j = 0; j < uniqueResult.size(); j++) {
            if (result[i] == uniqueResult[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            uniqueResult.push_back(result[i]);
        }
    }

    return uniqueResult;
    
}

vector<int> listOR(string in, vector<Data> vocab){
    vector<string> words;
    vector<int> result;

    string line = in;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        // clean and lowercase the word
        string cleanedWord = cleanWord(word);
        // if the cleaned word is not empty, add it to the vocabulary
        if (!cleanedWord.empty()) {
            words.push_back(cleanedWord);
        }
    }
    string word1;
    string word2;
    for(int i = 0; i < words.size(); i++)
    {
        if(words[i] == "or")
        {
            word1 = words[i-1];
            word2 = words[i+1];
        }
    }
    for(int i = 0; i < vocab.size(); i++)
    {
        if(vocab[i].getLine() == word1 || vocab[i].getLine() == word2)
        {
            result.push_back(vocab[i].getLineNumber());
        }
    }
    int n = result.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                // Swap result[j] and result[j + 1]
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < result.size(); ++i) {
        for (int j = i + 1; j < result.size(); ++j) {
            if (result[i] == result[j]) {
                result.erase(result.begin() + j);
                --j;  // Adjust j after the erase operation
            }
        }
    }

    return result;
    
}
vector<int> listAND(string in, vector<Data> vocab){
    vector<string> words;
    vector<int> result;

    string line = in;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        // clean and lowercase the word
        string cleanedWord = cleanWord(word);
        // if the cleaned word is not empty, add it to the vocabulary
        if (!cleanedWord.empty()) {
            words.push_back(cleanedWord);
        }
    }

    string word1;
    string word2;
    for(int i = 0; i < words.size(); i++) {
        if(words[i] == "and") {
            word1 = words[i-1];
            word2 = words[i+1];
        }
    }

    // Check if both words are present in the same line
    for(int i = 0; i < vocab.size(); i++) {
        if(vocab[i].getLine() == word1) {
            // Check if the second word is also in the same line
            for(int j = 0; j < vocab.size(); j++) {
                if(vocab[j].getLine() == word2 && vocab[j].getLineNumber() == vocab[i].getLineNumber()) {
                    result.push_back(vocab[i].getLineNumber());
                }
            }
        }
    }

    return result;
}


vector<int> searchResult(string in, vector<Data> vocab) {
    vector<int> answer;

    int checker;
    bool NOT = in.find("NOT") != string::npos;
    bool AND = in.find("AND") != string::npos;
    bool OR = in.find("OR") != string::npos;

    if(NOT)
    {
        answer = listNOT(in, vocab);
    }
    else if(AND)
    {
        answer = listAND(in, vocab);
    }
    else if(OR)
    {
        answer = listOR(in, vocab);
    }
 
    else
    {
        answer = listSingleWord(in, vocab);
    }


    return answer;
}

vector<Hashmap> buildDocumentMatrix(vector<Hashmap> hashmaps)
{
    // sort from least to greatest based on line number and hash value using bubble sort
    for (int i = 0; i < hashmaps.size() - 1; i++) {
        for (int j = 0; j < hashmaps.size() - i - 1; j++) {
            if ((hashmaps[j].getLineNumber() > hashmaps[j + 1].getLineNumber()) ||
                ((hashmaps[j].getLineNumber() == hashmaps[j + 1].getLineNumber()) &&
                 (hashmaps[j].getHashValue() > hashmaps[j + 1].getHashValue()))) {
                swap(hashmaps[j], hashmaps[j + 1]);
            }
        }
    }

    return hashmaps;
}
vector<Hashmap> buildDictionary(vector<Data> lines) {
    // assigns each value a hash value and stores it in a vector
    vector<Hashmap> hashValues;
    int hash = 0;
    const int N = 999883;

    for(int i = 0; i < lines.size(); i++) {
        hash = 0;

        for(int j = 0; j < lines[i].getLine().length(); j++) {
            hash = hash + static_cast<int>(lines[i].getLine()[j]);
        }

        hash = hash % N;

        // collision check
        bool collision = false;

        // check for collisions
        for(int k = 0; k < hashValues.size(); k++) {
            if(hashValues[k].getHashValue() == hash && hashValues[k].getLine() != lines[i].getLine()) {
                collision = true;
                break;
            }
        }

        // handle collisions
        if (collision) {
            // handle the collision by modifying the hash
            while (collision) {
                hash += 1;
                collision = false; // reset the collision flag

                // check for new collisions
                for(int k = 0; k < hashValues.size(); k++) {
                    if(hashValues[k].getHashValue() == hash && hashValues[k].getLine() != lines[i].getLine()) {
                        collision = true;
                        break;
                    }
                }
            }
        }

        hashValues.push_back(Hashmap(lines[i].getLine(), lines[i].getLineNumber(), hash));
    }

    return hashValues;
}


vector<Data> buildVocabulary(vector<Data> lines) {
    vector<Data> vocabulary;

    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i].getLine();
        int lineNumber = lines[i].getLineNumber();

        stringstream ss(line);
        string word;

        while (ss >> word) {
            // clean and lowercase the word
            string cleanedWord = cleanWord(word);

            // if the cleaned word is not empty, add it to the vocabulary
            if (!cleanedWord.empty()) {
                vocabulary.push_back(Data(cleanedWord, lineNumber));
            }
        }
    }

    // bubble sort for sorting the vocabulary in alphabetical order
    for (int i = 0; i < vocabulary.size() - 1; i++) {
        for (int j = 0; j < vocabulary.size() - i - 1; j++) {
            if (vocabulary[j].getLine() > vocabulary[j + 1].getLine()) {
                swap(vocabulary[j], vocabulary[j + 1]);
            }
        }
    }

    return vocabulary;
}

int main(int argc, char *argv[]) {
    const string doc1 = argv[1];
    ifstream inputDoc(doc1);
    const string instructionInput = argv[2];
    ifstream inputInstr(instructionInput);
    const string outputFileName = argv[3];
    ofstream outputFile(outputFileName);
    const string outputInstrName = argv[4];
    ofstream outputInstr(outputInstrName);

    if (!inputInstr.is_open()) {
        cerr << "Error opening instruction input file: " << instructionInput << endl;
    return 1; // or exit(1) to indicate an error
}

    // document indexing:
    vector<Data> lines;
    string str;
    int lineNumber = 1;
    while (getline(inputDoc, str)) {
        lines.push_back(Data(str, lineNumber));
        lineNumber++;
    }

    vector<Data> vocab = buildVocabulary(lines);
    vector<Hashmap> hashValues = buildDictionary(vocab);
    hashValues = buildDocumentMatrix(hashValues);


    Hashmap temp = Hashmap(" ", 0, 0);
    for(int i = 0; i < hashValues.size(); i++)
    {
        for(int j = 0; j < hashValues.size(); j++)
            if(hashValues[i].getLineNumber() < hashValues[j].getLineNumber())
            {
                temp = hashValues[i];
                hashValues[i] = hashValues[j];
                hashValues[j] = temp;
            }
    }

    // sorting the hashValues based on line number and hash value using bubble sort
    for (int i = 0; i < hashValues.size() - 1; i++) {
        for (int j = 0; j < hashValues.size() - i - 1; j++) {
            if ((hashValues[j].getLineNumber() > hashValues[j + 1].getLineNumber()) ||
                ((hashValues[j].getLineNumber() == hashValues[j + 1].getLineNumber()) &&
                 (hashValues[j].getHashValue() > hashValues[j + 1].getHashValue()))) {
                swap(hashValues[j], hashValues[j + 1]);
            }
        }
    }
    
    
    // output in desired format for document matrix
    int count = 0;
    for (int i = 0; i < hashValues.size(); i++) {
        if (i == 0) {
            outputFile << hashValues[i].getLineNumber() << "->[" << hashValues[i].getHashValue() << ", ";
        }
        else if(hashValues[i].getLine() == hashValues[i - 1].getLine())
            continue;
        else if (hashValues[i].getLineNumber() != hashValues[i - 1].getLineNumber()) {
            outputFile << hashValues[i].getLineNumber() << "->[" << hashValues[i].getHashValue() << ", ";
        } else if (hashValues[i].getLineNumber() != hashValues[i + 1].getLineNumber()) {
            outputFile << hashValues[i].getHashValue() << "]";
            if (i < hashValues.size() - 1) {
                outputFile << endl;
            }
        } else {
            outputFile << hashValues[i].getHashValue() << ", ";
        }
    }
    outputFile.close();

    vector<Data> instrData;
    string instr;
    lineNumber = 1;
    while (getline(inputInstr, instr)) {
        instrData.push_back(Data(instr, lineNumber));
        lineNumber++;
    }

    vector<int> found;
    for(int i = 0; i < instrData.size(); i++)
    {
            found = searchResult(instrData[i].getLine(), vocab);
            outputInstr << instrData[i].getLine() << "-->[";
            for(int j =0; j < found.size(); j++)
            {
                if(found.size() - 1 != j)
                    outputInstr << found[j] << ", ";
                else
                    outputInstr << found[j];
            }
            outputInstr << "]" << endl;
    }

    outputInstr.close();
    return 0;
}