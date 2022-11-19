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
        bool flag = true;
        while (flag) {

            for (int i = 0; i < 8; i++) {
                if (!inFile.read(byte, 1)) {
                    flag = false;
                    break;
                }
                int temp_byte = byte[0];
                std::bitset<8> bitset = temp_byte;
                cout << temp_byte << " -- > " << bitset << " (bit)" << endl;
                textFile += bitset.to_string();
            }
            cout<<flag<<endl;
            cout << "--------------------" << endl;

            if(flag != false)
            {  cout << "text in file without changes:\n" << textFile << endl;
                magicencode();//когда 8 символов считали вызываем
                clearOutputTextFile();
            }
            if(inFile.eof()){break;}
        }

        inFile.close();
    }
    returnNonSystem();
    writeToFileHamming(outFileName);


}

void HammingCode::RemoveProtection(const string& inFileName, const string& outFileName){
    //todo HammingCode::RemoveProtection
}

//64 - info
// -control
string HammingCode::delChar(string st[], int n){
    string str;
    for (int i = 0; i < 72; i++)
    {
        if (i != n)
            str += st[i];
    }
    return str;
}
void HammingCode::clearOutputTextFile(){
    textFile.clear();
}

void HammingCode::magicencode(){
    string block[72];

   //запись набора значений в строку с добавлением контрольных битов
    for(int i=0;i<71;i++){
        if(i== 0 || i == 1 || i ==3 || i ==7 || i==15 || i==31 || i==63){
            block[i]='0';
        }
    }

    block[2]=textFile[0];
    block[4]=textFile[1];
    block[5]=textFile[2];
    block[6]=textFile[3];

    for(int i = 4 ; i < 11; i++){ // с 8 по 14
        block[i+4]=textFile[i];
    }
    for(int i = 11 ; i < 26; i++){ // c 16 по 31
        block[i+5]=textFile[i];
    }
    for(int i = 26; i < 57; i++){ // c 32 по 62
        block[i+6]=textFile[i];
    }
    for(int i = 57; i < 64; i++){ // с 57 по 70
        block[i+7]=textFile[i];
    }

    cout <<"add ks "<<  endl;
    for (int i = 0 ; i < 71; i++){
        cout<<block[i];
    }
    cout << endl;

    //начало подсчета значения контрольных битов
    // 0
    int sum = 0;
    for(int i = 2 ; i < 71; i = i + 2){
        sum += stoi(block[i]);
    }

    cout.flush();
//    cout<<"sum for 0: "<< sum <<endl;
    block[0]=sum % 2 == 0 ?  '0' : '1';
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;

    //1
    sum=0;
    for(int i = 2; i < 71; i = i + 4){
        sum+=stoi(block[i]);
        sum+=stoi(block[i-1]);
    }

    block[1]=sum % 2 == 0 ?  '0' : '1';

    cout.flush();
    //cout<<"sum for 1: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;

    //3
    sum=0;
    for(int i = 3; i < 71; i = i + 8){
        sum+=stoi(block[i]);
        sum+=stoi(block[i+1]);
        sum+=stoi(block[i+2]);
        sum+=stoi(block[i+3]);

    }
    block[3]=sum % 2 == 0 ?  '0' : '1';
    cout.flush();
//    cout<<"sum for 3: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;


    //7
    sum=0;
    for(int i = 7; i < 71; i = i + 16){
        for(int j = 0; j < 8; j++)
            {
                sum+=stoi(block[i+j]);
            }

    }
    block[7]=sum % 2 == 0 ?  '0' : '1';
    cout.flush();
//    cout<<"sum for 7: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;

    //15
    sum=0;
    for(int i=15;i<71;i=i+32){
        for(int j=0;j<16;j++)
        {
            sum+=stoi(block[i+j]);
        }

    }
    block[15]=sum % 2 == 0 ?  '0' : '1';
    cout.flush();
//    cout<<"sum for 15: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;

    //31
    sum=0;
    for(int i = 31; i < 71; i = i + 64){
        for(int j=0;j<32;j++){
            sum+=stoi(block[i+j]);
        }

    }
    block[31]=sum % 2 == 0 ?  '0' : '1';
    cout.flush();
//    cout<<"sum for 31: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;

    //63
    sum=0;
    for(int i = 63; i < 71; i = i + 128){
        for(int j = 0; j < 8; j++){
            sum+=stoi(block[i+j]);
        }

    }
    block[63]=sum % 2 == 0 ?  '0' : '1';
    cout.flush();
//    cout<<"sum for 63: "<< sum <<endl;
//    for (int i = 0 ; i < 71; i++){
//        cout<<block[i];
//    }
//    cout << endl;
//    cout << "\n--------------------------\n";
//    int sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1(before) "<<sum_unit<<endl;
    //end count control bit---------


        for (int i = 0 ; i < 71; i++){
        cout<<block[i];
    }
    cout << endl;


    //0
    string new_block;
    block[71] = block[0];//перенесли значение контрольного бита с индексом ноль в конец(создаем систематический код)
    block[0] = '/';
    new_block = delChar(block, 0);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;


    //1
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
    //sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1 "<<sum_unit<<endl;
    block[71] = block[0];
    block[0]='/';
    new_block = delChar(block, 0);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;

    //3
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
//    sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
    //cout<<"count 1 "<<sum_unit<<endl;
    block[71]=block[1];
    block[1]='/';
    new_block = delChar(block, 1);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;

    //7
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
//    sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1 "<<sum_unit<<endl;
    block[71]=block[4];
    block[4]='/';
    new_block = delChar(block, 4);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;
//    sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1 "<<sum_unit<<endl;


    //15
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
    block[71]=block[11];
    block[11]='/';
    new_block = delChar(block, 11);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;
//    sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1 "<<sum_unit<<endl;


    //31
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
    block[71]=block[26];
    block[26]='/';
    new_block = delChar(block, 26);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;
//    sum_unit = 0;
//    for(int i=0;i<71;i++){
//        if(block[i]=="1") sum_unit+=1;
//    }
//    cout << "\n--------------------------\n";
//    cout<<"count 1 "<<sum_unit<<endl;


    //63
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
    block[71]=block[57];
    block[57]='/';
    new_block = delChar(block, 57);
//    for (int i = 0 ; i < 71; i++){
//        cout<<new_block[i];
//    }
//    cout << endl;

    //систематический код
    for (int i = 0 ; i < 71; i++){
        block[i] = new_block[i];
    }
    cout<<endl;

    for (int i = 0 ; i < 71; i++){
        outputFile += block[i];
    }
    cout<< "------ OUTPUT FILE ------\n";
    for(int i=0;i<71;i++){
        cout<<outputFile[i];
    }
    cout<<endl;
}

void HammingCode::writeToFileHamming(const string& outFileName){
    ofstream outputHamming;cout<<outputFile[0]<<endl;
    outputHamming.open(outFileName, ios::app);
    if (!outputHamming) {
        cout << "Can't open inFileName " << outFileName << endl;

    } else {

        outputHamming << outputFile<< endl;
    }

}

void HammingCode::retByteCode(){

      int sum = 0;
}

void HammingCode::returnNonSystem(){

    string newSystem[71];
    int j=0;
    //ks
    for(int i=0;i<71;i++){
        if(i== 0 || i == 1 || i ==3 || i ==7 || i==15 || i==31 || i==63){
            newSystem[i]='0';
        }
        else{
            newSystem[i]=outputFile[j];
            j++;
        }

    }
    cout<<"NonSystem(simple ks=0)"<<endl;
    for(int i=0;i<71;i++){
        cout<< newSystem[i];
    }
    cout<<endl;
    newSystem[0]=outputFile[64];
    newSystem[1]=outputFile[65];
    newSystem[3]=outputFile[66];
    newSystem[7]=outputFile[67];
    newSystem[15]=outputFile[68];
    newSystem[31]=outputFile[69];
    newSystem[63]=outputFile[70];
    cout<<"NonSystem(simple)"<<endl;
    for(int i=0;i<71;i++){
       cout<< newSystem[i];
    }
    cout<<endl;

    cout<<"SystemCode"<<endl;
    for(int i=0;i<71;i++){
        cout<< outputFile[i];
    }
    cout<<endl;
    //Make error
    newSystem[56]='0';
    //Make error



//START TO COUNT OF ERRORS IN FILE
    int errors = 0;
    // 0
    int sum = 0;
    for(int i = 2 ; i < 71; i = i + 2){
        sum += stoi( newSystem[i]);
    }
    sum = sum % 2 == 0 ?  0 : 1;

    if((stoi(newSystem[0])-sum) != 0) errors +=1;
    //1
    sum=0;
    for(int i = 2; i < 71; i = i + 4){
        if(i==2)
        {
            sum+=stoi( newSystem[i]);
        }
        else{
            sum+=stoi( newSystem[i]);
            sum+=stoi( newSystem[i-1]);
        }

    }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[1])-sum) !=0) errors +=2;

    //3
    sum=0;
    for(int i = 3; i < 71; i = i + 8){
        if(i==3){
            sum+=stoi( newSystem[i+1]);
            sum+=stoi( newSystem[i+2]);
            sum+=stoi( newSystem[i+3]);
        }
        else{sum+=stoi( newSystem[i]);
            sum+=stoi( newSystem[i+1]);
            sum+=stoi( newSystem[i+2]);
            sum+=stoi( newSystem[i+3]);
        }
    }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[3])-sum) !=0) errors +=4;

    //7
    sum=0;
    for(int i = 7; i < 71; i = i + 16){
        if(i==7)
        {
            for(int j = 1; j < 8; j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }
        else{
            for(int j = 0; j < 8; j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }

        }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[7])-sum) !=0) errors +=8;
    cout.flush();

    //15
    sum=0;
    for(int i=15;i<71;i=i+32){
        if (i==15){
            for(int j=1;j<16;j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }else
        {
            for(int j=0;j<16;j++)
            {
                sum+=stoi( newSystem[i+j]);}
        }


    }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[15])-sum) !=0) errors +=16;
    cout.flush();


    //31
    sum=0;
    for(int i = 31; i < 71; i = i + 64){
        if(i==31){
            for(int j=1;j<32;j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }else{
            for(int j=0;j<32;j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }


    }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[31])-sum) !=0) errors +=32;

    //63
    sum=0;
    for(int i = 63; i < 71; i = i + 128){
        if(i==63){
            for(int j = 1; j < 8; j++)
            {
                sum+=stoi( newSystem[i+j]);
            }
        }else
        {for(int j = 0; j < 8; j++)
            {
                sum+=stoi( newSystem[i+j]);
            }}


    }
    sum=sum % 2 == 0 ?  0 : 1;
    if((stoi(newSystem[63])-sum) != 0) errors += 64;
    cout.flush();
//    cout<<"sum for 63: "<< sum <<endl;
    int sum_unit = 0;
    for(int i=0;i<71;i++){
        if(newSystem[i]=="1") sum_unit+=1;
    }
    cout << "\n--------------------------\n";
    cout<<"count 1 "<<sum_unit<<endl;
    cout<<"position of error  "<<errors-1<<endl;


    if (errors != 0) {
        if (newSystem[errors-1] == "0") newSystem[errors-1]= "1";
        else newSystem[errors-1]="0";
    }

    string res;

    for (int i = 0; i <71; i++){
            if (i != 0 && i != 1 && i != 3 && i != 7 && i != 15 && i != 31 && i != 63) {
                res+=newSystem[i];
        }
        if(res.size()==8){
            for(int i=0;i<8;i++){
                cout<<res[i];

            }bin_to_dec(res);
            cout<<endl;
            cout.flush();
            res.clear();
        }
    }






}
void HammingCode::bin_to_dec(const string& a){
    int count=0;
    for(int i =0;i<8;i++){
        const char b = a[i];
        if(b=='1'){
            count+=pow(2,7-i);
        }
    }
    cout<<"\n"<< count<<endl;

    dec_to_ASCII(count);

}

void HammingCode::dec_to_ASCII(int a){

    char n= static_cast<char>(a);

    cout<<n<<endl;

}