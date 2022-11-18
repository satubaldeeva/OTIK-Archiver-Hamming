//
// Created by grigory on 15/11/22.
//

#include <bitset>
#include "HammingCode.h"


void HammingCode::AddProtection(const string& inFileName, const string& outFileName) {
    ifstream inFile;
    ofstream extractedFile;
    inFile.open(inFileName);

    if (!inFile)
        cout << "Can't read file " << inFileName << endl;
    else {

        //reading symbols
        char byte[1];
        while (inFile.read(byte, 1)) {
            int temp_byte = byte[0];
            std::bitset<8> bitset = temp_byte;
            cout <<temp_byte<<" -- > "<< bitset << " (bit)" << endl;
            textFile+=bitset.to_string();

        }
        cout<<textFile<<endl;
        //magicencode();
    }
}

void HammingCode::RemoveProtection(const string& inFileName, const string& outFileName){
    //todo HammingCode::RemoveProtection
}

//64 - info
// -control
void HammingCode::magicencode(){
    vector<char> block;
   //non system
   //запись набора значений в строку с добавлением контрольных битов
    for(int i=0;i<71;i++){
        if(i== 0 || i == 1 || i ==7 ||i==15 || i==31 || i==63)
        {block[i]='0';}

    }
    block[2]=textFile[0];
    block[4]=textFile[1];
    block[5]=textFile[2];
    block[6]=textFile[3];
    for(int i= 4 ;i<11;i++){
        block[i+4]=textFile[i];
    }
    for(int i= 11 ;i<26;i++){
        block[i+5]=textFile[i];
    }
    for(int i= 26 ;i<57;i++){
        block[i+6]=textFile[i];
    }
    for(int i= 56 ;i<64;i++){
        block[i+7]=textFile[i];
    }
    //начало подсчета значения контрольных битов//0
    int sum=0;
    for(int i=2;i<71;i=i+2){
        sum+=int((block[i]));

    }
    cout.flush();
    cout<<sum<<"dfsdf"<<endl;
    block[0]=sum % 2 == 0 ?  '0' : '1';

    //1
    sum=0;
    for(int i=2;i<71;i=i+4){
        if(i==2){
            sum+=int((block[i]));
        }
        sum+=int((block[i]));
        sum+=int((block[i-1]));
    }

    block[1]=sum % 2 == 0 ?  '0' : '1';
    //3
    sum=0;
    for(int i=3;i<71;i=i+8){
        sum+=int((block[i]));
        sum+=int((block[i+1]));
        sum+=int((block[i+2]));
        sum+=int((block[i+3]));

    }
    block[3]=sum % 2 == 0 ?  '0' : '1';

    //7
    sum=0;
    for(int i=7;i<71;i=i+16){
        for(int j=0;j<8;j++)
            {
                sum+=int((block[i+j]));
            }

    }
    block[7]=sum % 2 == 0 ?  '0' : '1';

    //15
    sum=0;
    for(int i=15;i<71;i=i+32){
        for(int j=0;j<16;j++)
        {
            sum+=int((block[i+j]));
        }

    }
    block[15]=sum % 2 == 0 ?  '0' : '1';

    //31
    sum=0;
    for(int i=31;i<71;i=i+64){
        for(int j=0;j<32;j++)
        {
            sum+=int((block[i+j]));
        }

    }
    block[31]=sum % 2 == 0 ?  '0' : '1';
    //63
    sum=0;
    for(int i=63;i<71;i=i+128){
        for(int j=0;j<9;j++)
        {
            sum+=int((block[i+j]));
        }

    }
    block[63]=sum % 2 == 0 ?  '0' : '1';
    //end count control bit---------
    //0
    block[71]=block[0];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[0]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());

    //1
    block[71]=block[0];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[0]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());

    //3
    block[71]=block[1];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[1]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());

    //7
    block[71]=block[4];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[4]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());

    //15
    block[71]=block[11];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[11]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());
    //31
    block[71]=block[26];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[26]='/';
    block.erase((std::remove(block.begin(),block.end(),'/')),block.end());

    //63
    block[71]=block[57];
   //перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[57]='/';
    block.erase(block.end());

    //систематический код
    for(int i=0;i<77;i++){
        cout<<block[i];
    }
    cout<<endl;
    cout<<"sdfsdfgdgsfg"<<endl;

    outputFile.insert( outputFile.end(),block.begin(), block.end() );
    for(int i=0;i<77;i++){
        cout<<outputFile[i];
    }
    cout<<endl;
}
