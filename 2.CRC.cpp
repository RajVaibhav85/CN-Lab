#include<bits/stdc++.h>
using namespace std;

string xor_division(string dividend, string divisor){
    int dividend_len = dividend.length(), divisor_len = divisor.length();
    for(int i = 0 ; i <= dividend_len - divisor_len ; i++){
        if(dividend[i] == '1'){
            for(int j = 0 ; j < divisor_len ; j++){
                dividend[i+j] = (dividend[i+j] == divisor[j]) ? '0' : '1';
            }
        }

    }
    return dividend.substr(dividend_len - divisor_len + 1);
}

int main(){
    string data = "11010011";
    string divisor = "1001";
    string remainder = xor_division(data, divisor);
    cout << "Data: " << data << endl;
    cout << "Divisor: " << divisor << endl;
    cout << "Remainder: " << remainder << endl;
    cout << "Encoded Data: " << data + remainder << endl;
    cout << "Decoded Data: " << xor_division(data + remainder, divisor) << endl;
}