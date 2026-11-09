#include<bits/stdc++.h>
using namespace std;

string toip(int ip){
    return to_string((ip >> 24) & 0xFF) + "." + to_string((ip >> 16) & 0xFF) + "." + to_string((ip >> 8) & 0xFF) + "." + to_string(ip & 0xFF);
}

int toint(string ip){
    int val = 0, octet = 0;
    for(char c : ip){
        if(c == '.') {
            val = (val << 8) | octet;
            octet = 0;
        } else {
            octet = octet * 10 + (c - '0');
        }
    }
    return (val << 8) | octet;
}

int main(){
    string address = "192.168.10.0";
    int cidr = 26;
    int subnets = 4;

    int address_int = toint(address);
    int blockSize = (1 << (32 - cidr));
    int hosts = blockSize - 2;
    int subnetmask = (cidr == 0) ? 0 : (0xFFFFFFFF << (32 - cidr));
    address_int = address_int & subnetmask;

    cout << "Address: " << address << "\n";
    cout << "CIDR: " << cidr << "\n";
    cout << "Subnet Mask: " << toip(subnetmask) << "\n";
    cout << "Number of Subnets: " << subnets << "\n";
    cout << "Block Size: " << blockSize << "\n";
    cout << "Number of Hosts per Subnet: " << hosts << "\n\n";

    for(int i = 0 ; i < subnets ; i++){
        int currentNetwork = address_int + (i * blockSize);
    int firstHost = currentNetwork + 1;
    int BroadcastAddress = currentNetwork + 1 + hosts;
    int lastHost = BroadcastAddress - 1;
    cout << "Subnet " << i + 1 << ":\n";
    cout << "Current Network: " << toip(currentNetwork) << "\n";
    cout << "First Host: " << toip(firstHost) << "\n";
    cout << "Last Host: " << toip(lastHost) << "\n";
    cout << "Broadcast Address: " << toip(BroadcastAddress) << "\n\n";
    }
}