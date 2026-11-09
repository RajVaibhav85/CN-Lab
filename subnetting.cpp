#include <iostream>
#include <string>
using namespace std;

string toip(int ip){
    return to_string((ip >> 24) & 0xFF) + "." + to_string((ip >> 16) & 0xFF) + "." + to_string((ip >> 8) & 0xFF) + "." + to_string(ip & 0xFF);

}
int toint(string& ip){
    int val =0;
    int octet= 0;
    for(char c: ip){
        if(c=='.'){
            val= (val<<8) | octet;
            octet =0;
        }else{
            octet = octet *10 +(c- '0');
        }
    }
    return (val <<8) | octet;
}

int main(){
    string addres;
    int cidr;
    int subnets;

    cout << "enter input: ";
    if(!(cin >> addres)) return 0;
    cout << "enter cidr : ";
    cin >> cidr;
    cout << "enter subnets: ";
    cin >> subnets;

    int mask = (cidr == 0) ? 0 : (~0U << (32 - cidr));
    int hostbits = 32 - cidr;
    int blocksize = 1 << hostbits;
    int hosts = (blocksize >= 2) ? (blocksize - 2) : 0;
    int currentnet = toint(addres);

    for(int i =1; i<= subnets; ++i){
        int first = currentnet +1;
        int brod = currentnet +blocksize -1;
        int last = brod - 1;

        cout << left
             << i << " " << toip(currentnet) << " " << toip(mask) << " " << toip(first) << " " << toip(last) << " " << toip(brod) << " " << hosts << "\n";

        currentnet += blocksize;
    }
    return 0;
}
