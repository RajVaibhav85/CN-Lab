import java.util.*;
import java.io.*;


class Sender {
    void sendData(String[] data){
        int base = 0;
        int N = 3;
        Receiver receiver = new Receiver();

        while(base < data.length){
            System.out.println("Sending packets from " + base + " to " + Math.min(base + N - 1, data.length - 1));
            for(int i = base; i < Math.min(base + N, data.length); i++){
                System.out.println("Sending data: " + data[i]);
                int ack = receiver.receiveData(data[i], i);
                if(ack != -1) base++ ;
            }
            try{
                Thread.sleep(1000);
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
}

class Receiver {
    int base = 0;
    int receiveData(String data , int packet_no){
        Random rand = new Random();
        boolean isError = rand.nextBoolean();
        if(packet_no != base){
            System.out.println("Packet out of order! Expected: " + base + " Received: " + packet_no);
            isError = true;
        }
        else if(isError){
            System.out.println("Packet lost!");
        }
        else{
            System.out.println("Received data: " + data);
            base++;
        }
        return !isError ? base : -1;

    }
}




public class GoBackN {
    public static void main(String[] args){
        String data = "Hello this is a test message.";
        String[] tokens = data.split(" ");
        Sender sender = new Sender();
        sender.sendData(tokens);
    }
}