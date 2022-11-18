//
// Created by grigory on 15/11/22.
//

#ifndef OTIK_ARCHIVE_HAMMINGCODE_H
#define OTIK_ARCHIVE_HAMMINGCODE_H

#include "ReedSolomonWrapper.h"

using namespace std;
class HammingCode {
    string textFile;
    vector<char> outputFile;
    int N = 8;



public:
    void AddProtection(const string& inFileName, const string& outFileName);
    void RemoveProtection(const string& inFileName, const string& outFileName);

    void magicencode();
};


#endif //OTIK_ARCHIVE_HAMMINGCODE_H
