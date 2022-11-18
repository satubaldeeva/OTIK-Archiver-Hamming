//
// Created by grigory on 15/11/22.
//

#ifndef OTIK_ARCHIVE_HAMMINGCODE_H
#define OTIK_ARCHIVE_HAMMINGCODE_H

#include "ReedSolomonWrapper.h"

using namespace std;
class HammingCode {
    string textFile;
    string outputFile;
    int N = 8;

public:
    void AddProtection(const string& inFileName, const string& outFileName);
    void RemoveProtection(const string& inFileName, const string& outFileName);

    void magicencode();

    string delChar(string st[], int n);

    void clearOutputTextFile();

    void writeToFileHamming(const string &outFileName);
};


#endif //OTIK_ARCHIVE_HAMMINGCODE_H
