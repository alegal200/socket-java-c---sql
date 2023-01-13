import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.*;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        System.out.println("slt bg alex");
        server_Socket s = new server_Socket();
         // Thread serverThread = new Thread(new HTTP_Server_Runable());
         // serverThread.start();
   //     C_read_server  ct= new  C_read_server(8); 
     //   System.out.println("**-"+ct.getval() );
     /*
       ArrayList<actyObj> actlst  = sqlconnector.getacty(18);
       
       for (int i=0; i<actlst.size() ;i++) {
            System.out.println("-> "+actlst.get(i).getName());
        }
*/
    }
}

