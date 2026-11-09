package Socket;

import java.io.*;
import java.net.*;
import java.util.*;

public class UDPServer {
    public static void main(String[] args) throws IOException {
        DatagramSocket ds = new DatagramSocket(5001);

        byte[] buf = new byte[1024];
        DatagramPacket in = new DatagramPacket(buf, buf.length);
        ds.receive(in);

        String str = new String(in.getData(), 0, in.getLength());
        System.out.println("Received from client: " + str);

        String rev = new StringBuilder(str).reverse().toString();
        String reply = str.equals(rev) ? "Palindrome" : "Not a palindrome";

        byte[] out = reply.getBytes();
        DatagramPacket resp = new DatagramPacket(out, out.length, in.getAddress(), in.getPort());
        ds.send(resp);
        ds.close();
    }
}
