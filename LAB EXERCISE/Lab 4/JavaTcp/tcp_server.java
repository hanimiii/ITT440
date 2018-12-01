package tcp_server;
import java.io.*;
import java.net.*;
import java.util.*;
/**
 *
 * @author Amirul Hazim
 */
public class tcp_server {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        ServerSocket ourFirstSocket  = new ServerSocket(6789);
        
        while(true){
            Socket connectionSocket = ourFirstSocket.accept();
         
            //Send data to client
            //DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            //BufferedReader inFromClient = new BufferedReader(new InputStreamReader(System.in));

            
            //==========================================
            // Server side
            final DataInputStream InFromCli = new DataInputStream(connectionSocket.getInputStream());
            final DataOutputStream OutToCli = new DataOutputStream(connectionSocket.getOutputStream());
            // than use OutToClient.writeInt() and InFromClient.readInt()
            String msg2 = "SERVER CLIENT RANDOM NUMBER \n";
            //String gap = "\n";
            //String msg1 = "Enter max range of random number 0-100 : \n";
            
            OutToCli.writeBytes(msg2);
            int n1 = InFromCli.readInt();
            int n2 = InFromCli.readInt();
            int lcm = InFromCli.readInt();
            
            int newn1 = n1 - 10;
            int newn2 = n2 - 10;
            int newlcm = lcm - 10;
            
            // maximum number between n1 and n2 is stored in lcm
            newlcm = (newn1 > newn2) ? newn1 : newn2;

            // Always true
            while(true)
            {
                if( newlcm % newn1 == 0 && newlcm % newn2 == 0 )
                {
                    System.out.println("The LCM of "+newn1+" and "+newn2+" is "+newlcm);
                    break;
                }
                ++newlcm;
            }

    
//            int num1 = InFromCli.readInt();
//            int num2 = InFromCli.readInt();
//            num1 = num1-10;
//            num2=num2-10;
//
//         
//            if (num1 >=0 && num2 <= 100){
//                Random rand = new Random();
//                int newRand = rand.nextInt(num2);
//                System.out.println("Received number 1: " + num1);
//                System.out.println("Received number 2: " + num2);
//                System.out.println("Random Number: " + newRand);
//            }else
//            {
//                System.out.println("Please input according to the range given!");
//            }

     }
    }
    
}
