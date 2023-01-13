import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class server_Socket {


    public server_Socket() {
        try {
            ServerSocket ss = new ServerSocket(8080);
            ExecutorService executor = Executors.newFixedThreadPool(2);
            while (true) {
                System.out.println("En attente d'un nouvelle connexion");
                Socket ts = ss.accept();
                System.out.println("Nouvelle connexion");
                HTTP_Server_Runable w = new HTTP_Server_Runable(ts);
                executor.execute(w);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }


    }
}
