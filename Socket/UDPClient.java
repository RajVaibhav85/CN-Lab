package Socket;

import java.io.*;
import java.net.*;
import java.util.*;

public class UDPClient {
    public static void main(String[] args) throws IOException {
        DatagramSocket ds = new DatagramSocket();
        InetAddress ip = InetAddress.getByName("localhost");

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a string: ");
        String str = sc.nextLine();

        byte[] data = str.getBytes();
        ds.send(new DatagramPacket(data, data.length, ip, 5001));

        byte[] buf = new byte[1024];
        DatagramPacket in = new DatagramPacket(buf, buf.length);
        ds.receive(in);

        System.out.println("Server says: " + new String(in.getData(), 0, in.getLength()));
        ds.close();
    }
}
