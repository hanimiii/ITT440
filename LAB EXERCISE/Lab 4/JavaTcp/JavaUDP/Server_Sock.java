package server_sock;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server_Sock {

    public static void main(String[] args) {
        try{
//            ServerSocket ser = new ServerSocket(9999);
//            Socket sock = ser.accept();
//            
//            BufferedReader ed = new BufferedReader(new InputStreamReader(sock.getInputStream()));
//            String tmp = ed.readLine();
//            System.out.println("I Received: " + tmp);
//            
//            PrintStream pr = new PrintStream(sock.getOutputStream());
//            String str = "Yup I got it!!";
//            pr.println(str);
              
              //Create new socket
              ServerSocket ser = new ServerSocket(9999);
              //Accept new connection
              Socket sock = ser.accept();
              
              //Send function
              PrintStream pr = new PrintStream(sock.getOutputStream());
              String msgSend = "[Server] Calculate Least Common Multiple(LCM)";
              pr.println(msgSend);
              
              msgSend = "[Server] Enter First Number: ";
              pr.println(msgSend);
             
              //receive function
              BufferedReader ed = new BufferedReader(new InputStreamReader(sock.getInputStream()));
              String rcvMsg = ed.readLine();
              
              int firstNo = Integer.parseInt(rcvMsg);
              
              msgSend = "[Server] Enter Second Number: ";
              pr.println(msgSend);
             
              rcvMsg = ed.readLine();
              
              int secondNo = Integer.parseInt(rcvMsg);
              
              System.out.println("Server: Receiving 2 Number From Client");
              System.out.println("Server: First Number is " + firstNo);
              System.out.println("Server: Second Number is " + secondNo);
              
              int lcm;
              lcm = (firstNo > secondNo) ? firstNo: secondNo;
              
              while(true){
                  if(lcm % firstNo == 0 && lcm % secondNo == 0){
                      msgSend = "The LCM of " + firstNo + " and " + secondNo + " is " + lcm;
                      System.out.println(msgSend);
                      msgSend = "[Server] " + msgSend;
                      pr.println(msgSend);
                      //System.out.printf("The LCM of %d and %d is %d.", firstNo, secondNo, lcm);
                      break;
                  }
                  ++lcm;
              }
              
              
        }
        catch(Exception ex){
        
        }
    }
    
}
