#include<bits/stdc++.h>
using namespace std;

string bit_stuff(string s){
    stringstream ss;
    int count = 0;
    for(char c : s){
        ss << c;
        if(c == '1'){
            count++;
            if(count == 5){
                ss << '0';
                count = 0;
            }
        }
        else count = 0;
    }
    return ss.str();
}

string bit_destuff(string s){
    stringstream ss;
    int count = 0;
    for(char c : s){
        if(count == 5){
            count = 0;
            continue;
        }
        if(c == '1') count++;
        else count = 0;
        ss << c;
    }
    return ss.str();
}

string byte_stuff(string s){
    stringstream ss;
    string FLAG = "01111110", ESC = "01111101";

    for(int i = 0 ; i < s.length() ; i += 8){
        string byte = s.substr(i,8);
        if(byte == FLAG || byte == ESC)
            ss << ESC;
        ss << byte;
    }

    return ss.str();
}

string byte_destuff(string s){
    stringstream ss;
    string FLAG = "01111110", ESC = "01111101";

    for(int i = 0 ; i < s.length() ; i += 8){
        string byte = s.substr(i, 8);
        if(byte == ESC){
            i += 8;
            byte = s.substr(i, 8);
        }
        ss << byte;
    }
    return ss.str();
}

int main(){
    string input = "0111111000000000011111100000000001111110";
    cout << "Original: \t" << input << endl;
    string stuffed = bit_stuff(input);
    cout << "Stuffed: \t" << stuffed << endl;
    string destuffed = bit_destuff(stuffed);
    cout << "Destuffed: \t" << destuffed << endl;
    string byte_stuffed = byte_stuff(input);
    cout << "Byte Stuffed: \t" << byte_stuffed << endl;
    string byte_destuffed = byte_destuff(byte_stuffed);
    cout << "Byte Destuffed: " << byte_destuffed << endl;
}