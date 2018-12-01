package client_sock;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

public class Client_Sock {

    public static void main(String[] args) {
        try{
//            Socket sock = new Socket("localhost", 9999);
//        
//            PrintStream pr = new PrintStream(sock.getOutputStream());
//            
//            System.out.print("Enter Something : ");
//            
//            InputStreamReader rd = new InputStreamReader(System.in);
//            BufferedReader ed = new BufferedReader(rd);
//            
//            String temp = ed.readLine();
//           
//            pr.println(temp);

              //Socket function
              Socket sock = new Socket("localhost", 9999);
              
              //Read Function
              BufferedReader gt = new BufferedReader(new InputStreamReader(sock.getInputStream()));
              String rcvMsg = gt.readLine();
              System.out.println(rcvMsg);
              
              rcvMsg = gt.readLine();
              System.out.print(rcvMsg);
              
              //User enter
              PrintStream pr = new PrintStream(sock.getOutputStream());
              InputStreamReader rd = new InputStreamReader(System.in);
              BufferedReader ed = new BufferedReader(rd);
              
              String sendMsg = ed.readLine();
              pr.println(sendMsg);
              
              rcvMsg = gt.readLine();
              System.out.print(rcvMsg);
              
              sendMsg = ed.readLine();
              pr.println(sendMsg);
              
              rcvMsg = gt.readLine();
              System.out.println(rcvMsg);
        }         
        catch(Exception ex){
            
        }
    }
    
}
