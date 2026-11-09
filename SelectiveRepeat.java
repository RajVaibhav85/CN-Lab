import java.util.*;
import java.io.*;


class Sender {
    void sendData(String[] data){
        int base = 0;
        int N = 3;
        Receiver receiver = new Receiver();
        boolean[] acked = new boolean[data.length];

        while(base < data.length){
            int end = Math.min(base + N, data.length);
            for(int i = base; i < end ; i++){
                if(!acked[i]){
                    System.out.println("Sending data: " + data[i]);
                    acked[i] = receiver.receiveData(data[i], i);
                }
            }
            try{
                Thread.sleep(1000);
            }catch(InterruptedException e){
                e.printStackTrace();
            }
            for(int i = base; i < end; i++){
                if(acked[i]) base++ ;
                else break;
            }
        }
    }
}

class Receiver {
    boolean receiveData(String data , int packet_no){
        Random rand = new Random();
        boolean isError = rand.nextBoolean();
        if(isError){
            System.out.println("Packet lost!");
        }
        else{
            System.out.println("Received data: " + data);
        }
        return !isError;

    }
}



public class SelectiveRepeat {
    public static void main(String[] args){
        String data = "Hello this is a test message.";
        String[] tokens = data.split(" ");
        Sender sender = new Sender();
        sender.sendData(tokens);
    }
}


