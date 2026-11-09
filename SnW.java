import java.util.*;
import java.io.*;


class Sender {
    void sendData(String data){
        System.out.println("Sending data: " + data);
        Receiver receiver = new Receiver();
        while(!receiver.receiveData(data).equals("ACK")){
            System.out.println("Resending data: " + data);
            try{
                Thread.sleep(1000);
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
}

class Receiver {
    String receiveData(String data){
        Random rand = new Random();
        boolean isError = rand.nextBoolean();
        if(isError){
            System.out.println("Packet lost!");
        }
        else{
            System.out.println("Received data: " + data);
        }
        return !isError ? "ACK" : "";

    }
}



public class SnW {
    public static void main(String[] args){
        String data = "Hello this is a test message.";
        String[] tokens = data.split(" ");
        Sender sender = new Sender();
        for(String token : tokens){
            sender.sendData(token);
        }
    }
}

