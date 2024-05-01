Document Search Engine README
=============================

Overview
--------
This C++ application is designed to simulate a basic document indexing and search engine. It indexes text documents by creating a vocabulary from the words within the document and applying hash functions for efficient search operations. Users can perform complex queries with logical operators such as AND, OR, and NOT to retrieve specific lines that match the search criteria.

Features
--------
- Document Indexing: Converts text files into an indexed format for faster search operations using hashing.
- Search Capability: Supports complex search queries using logical operators AND, OR, and NOT.
- Output Formatting: Outputs search results and document indices to specified files.

Prerequisites
-------------
- C++ compiler (GCC recommended)
- Makefile (optional for compilation)

Compilation and Execution
-------------------------
To compile and run the program, follow these steps:
1. Ensure that you have a C++ compiler installed on your system.
2. Place your document file and the search query file in the same directory as your source code.
3. Compile the code using the following command:
   g++ -o DocumentSearch main.cpp
4. Run the program by passing the document and query files along with the desired output filenames:
   ./DocumentSearch document.txt queries.txt document_output.txt query_output.txt

Input Format
------------
- Document File: Should contain the text to be indexed. Each line is considered a separate entry.
- Query File: Contains search queries, one per line.

Output Format
-------------
- Document Output File: Contains the indexed format of the document, showing line numbers and their corresponding hash values.
- Query Output File: Lists the search queries and their results in the format Query->[Line Numbers], where Line Numbers are the lines in the document that match the query.

Example Usage
-------------
Given a document named sample.txt and a query file named queries.txt, compile and run as follows:
./DocumentSearch sample.txt queries.txt output.txt results.txt

Known Issues and Limitations
----------------------------
- Hash collisions are handled with a basic linear probing method, which may not be efficient for very large datasets.
- The cleaning function for words only removes non-alphanumeric characters and converts to lower case, which may not be sufficient for all languages or special cases.
