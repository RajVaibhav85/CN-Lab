package Socket;

import java.io.*;
import java.net.*;
import java.util.*;


public class Client {
    public static void main(String[] args) throws IOException {
        Socket s = new Socket("localhost", 5000);

        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        DataInputStream dis = new DataInputStream(s.getInputStream());

        Random rand = new Random();
        int num = rand.nextInt(9) + 1;
        dos.writeInt(num);
        System.out.println("Sent random number to server: " + num);
        int response = dis.readInt();
        System.out.println("Received response from server: " + response);
    }
}
