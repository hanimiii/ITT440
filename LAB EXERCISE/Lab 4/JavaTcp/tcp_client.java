/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tcp_client;

import java.io.*;
import java.net.*;
import java.util.Random;

/**
 *
 * @author amiru
 */
public class tcp_client {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        Socket clientSocket = new Socket("localhost",6789);
        System.out.println("Connected with server\n");
        //Receive msg from server
//        BufferedReader messageFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
//        String serverSentence = messageFromServer.readLine();
//        String serverSentence1 = messageFromServer.readLine();
//        System.out.println(serverSentence);
//        System.out.println(serverSentence1);
//
//        //Send msg to server
//        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
//        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
////        String sentence = inFromUser.readLine();
////        String sentence2 = inFromUser.readLine();
//        int num1 = inFromUser.read();
//        int num2 = inFromUser.read();
//        outToServer.writeInt(num1 + '\n');
//        outToServer.writeInt(num2 + '\n');
        
        //==================================
        // Client side
        final DataInputStream FromServer = new DataInputStream(clientSocket.getInputStream());
        final DataOutputStream ToServer = new DataOutputStream(clientSocket.getOutputStream());
        //Receive msg from server
        String serverSentence = FromServer.readLine();
        System.out.println(serverSentence);
        
        
        //Send msg to server
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

        String msg1 = inFromUser.readLine();
        String msg2 = inFromUser.readLine();
        int num1 = Integer.parseInt(msg1);
        int num2 = Integer.parseInt(msg2);
        
        //=========================================
        if (num1 >=0 && num2 <= 100){
            Random rand = new Random();
            int newRand1 = rand.nextInt(num2);
            int newRand2 = rand.nextInt(num2);
            
            int lcm=0;
            ToServer.writeInt(newRand1 + '\n');
            ToServer.writeInt(newRand2 + '\n');
            ToServer.writeInt(lcm +'\n');

            //Random Number 1 prime number or not
            boolean flag = false;
            for(int i = 2; i <= newRand1/2; ++i)
            {
                // condition for nonprime number
                if(newRand1 % i == 0)
                {
                    flag = true;
                    break;
                }
            }
            //Random Number 1 prime number or not
            boolean flag2 = false;
            for(int i = 2; i <= newRand2/2; ++i)
            {
                // condition for nonprime number
                if(newRand2 % i == 0)
                {
                    flag2 = true;
                    break;
                }
            }
            
            lcm = (newRand1 > newRand2) ? newRand1 : newRand2;

            // Always true
            while(true)
            {
                if( lcm % newRand1 == 0 && lcm % newRand2 == 0 )
                {
                    System.out.println("The LCM of "+newRand1+" and "+newRand2+" is "+lcm);
                    break;
                }
                ++lcm;
            }
          
            

            if (!flag && !flag2){
                System.out.println(newRand1 + "&" + newRand2 + "is a prime number.");
                
            }else{
                System.out.println(newRand1 + "&" + newRand2 + " is not a prime number.");
            }
        }
        else{
            System.out.println("Please input according to the range given!");
        }
        
        
        
            
            
//            System.out.println("Number 1 entered: \n" + num1);
//            System.out.println("Number 2 entered: \n" + num2);
//            System.out.println("Random Number 1: \n" + newRand1);
//            System.out.println("Random Number 2: \n" + newRand2);
//            ToServer.writeInt(num1 + '\n');
//            ToServer.writeInt(num2 + '\n');
           //int n1=72;
           //int n2=120;
           
           //ToServer.writeInt(n1 + '\n');
           //ToServer.writeInt(n2 + '\n');
           //ToServer.writeInt(lcm +'\n');
           
            
            
        //============================================
        
        //================================
        //int num = 29;
        
        //==================================
        //System.out.println("Number 1 entered: "+msg1);
        //System.out.println("Number 2 entered: "+msg2);
        //ToServer.writeInt(num1 + '\n');
        //ToServer.writeInt(num2 + '\n');
        //===================================================================
        
        clientSocket.close();
    }
    
}
