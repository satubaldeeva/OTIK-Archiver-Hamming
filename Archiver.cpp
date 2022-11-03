//
// Created by Grigory on 20/09/2022.
//

#include "Archiver.h"

using namespace std;

void Archiver::Compress(CompressType type) {
    switch (type) {
        case PACK:
            for(auto file : files)
                packer.Pack(file, archive_file, true);
            break;
        case SHANNON:
            for(auto file : files)
                shannonCompressor.Compress(file, archive_file, true);

            break;
        case RLE:
            for(auto file : files)
                RLECompressor.Compress(file, archive_file, true);
            break;
        case INTELLIGENT:
            intelligentArchive();

        case TESTALL:
            compressAllMethods();
    }
}





    void Archiver::Extract(const string& archiveName){

        ifstream archiveFile;

        archiveFile.open(archiveName);
        if(!archiveFile) {
            cout << "Can't read file " << archiveName << endl;
        }
        else {
            file_header header{};

            archiveFile.seekg(0, ios_base::beg);


            while (!archiveFile.eof() && archiveFile.peek() != EOF) {

                //read header from archive
                memset(&header, 0, sizeof(struct file_header));
                archiveFile.read(header.signature, SIGNATURE_SZ);
                archiveFile.read(header.name, NAME_SZ);
                archiveFile.read(header.version, VERSION_SZ);
                archiveFile.read(header.size, SIZE_SZ);
                archiveFile.read(header.algorithm, ALGORITHM_SZ);
                archiveFile.read(header.padding, PADDING_SZ);   //going through padding without reading

                /////
                cout << "DEBUG | (sign from file): " << string(header.signature) << endl;
                cout << "DEBUG | (version from file): " << string(header.version) << endl;
                cout << "DEBUG | (alg code from file): " << string(header.algorithm) << endl;
                cout << "DEBUG | (size code from file): " << string(header.size) << endl;
                /////

                if (strcmp(header.signature, SIGN) != 0) {
                    cout << "Error: Signature mismatch!" << endl;
                    break;
                }


                if (strcmp(header.version, VERSION) != 0) {
                    cout << "Error: Incompatible version!" << endl;
                    break;
                }

                if (strcmp(header.algorithm, "1") == 0) {
                    shannonCompressor.Extract(archiveFile, header);
                }
                else if(strcmp(header.algorithm, "0") == 0)
                    packer.Unpack(archiveFile, header);
                else if(strcmp(header.algorithm, "2") == 0)
                    RLECompressor.Extract(archiveFile, header);
                else {
                    cout << "Error: Invalid algorithm code!" << endl;
                    break;
                }


            }
            archiveFile.close();
        }

    }

void Archiver::intelligentArchive(){
    for(auto file : files){

        int packSize = packer.Pack(file, archive_file+"_packTMP", false),
            shannonSize = shannonCompressor.Compress(file, archive_file+"_shannonTMP", false),
            RLESize = RLECompressor.Compress(file, archive_file+"_rleTMP", false);

        if( packSize <= shannonSize &&  packSize <= RLESize){
            packer.Pack(file, archive_file, true);
            remove((archive_file+"_shannonTMP").c_str());
            remove((archive_file+"_packTMP").c_str());
            remove((archive_file+"_rleTMP").c_str());
        }

        if( shannonSize <= RLESize &&  shannonSize <= packSize){
            shannonCompressor.Compress(file, archive_file, true);
            remove((archive_file+"_shannonTMP").c_str());
            remove((archive_file+"_packTMP").c_str());
            remove((archive_file+"_rleTMP").c_str());
        }

        if( RLESize <= shannonSize &&  RLESize <= packSize){
            RLECompressor.Compress(file, archive_file, true);
            remove((archive_file+"_shannonTMP").c_str());
            remove((archive_file+"_packTMP").c_str());
            remove((archive_file+"_rleTMP").c_str());
        }
    }

}


void Archiver::compressAllMethods(){
    cout << "***NOTE: FOR TESTS ONLY. YOU WON'T BE ABLE TO EXTRACT FILES!!***" << endl;
    for(const auto& file : files){
        packer.Pack(file, archive_file, true);
        shannonCompressor.Compress(file, archive_file, false);
        RLECompressor.Compress(file, archive_file, false);

    }
}




