package Socket;

import java.io.*;
import java.net.*;
import java.util.*;

public class Server {
    public static void main(String[] args) throws IOException{
        ServerSocket ss = new ServerSocket(5000);
        Socket s = ss.accept();

        DataInputStream dis = new DataInputStream(s.getInputStream());
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());

        int num = dis.readInt(), ans = 1;
        for(int i = 2 ; i <= num ; i++){
            ans *= i;
        }
        dos.writeInt(ans);
    }
}
