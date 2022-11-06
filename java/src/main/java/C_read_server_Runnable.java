import java.io.BufferedOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class C_read_server_Runnable implements  Runnable{

    private String ip = "192.168.220.128";
    private int port  = 50011;

    @Override
    public void run() {

        try {
           Socket socket_client = new Socket(ip,port);
           BufferedOutputStream out = new BufferedOutputStream(  socket_client.getOutputStream()  ) ;
           PrintWriter wrt = new PrintWriter(out) ;
           wrt.write("hello test");
           wrt.flush();
           wrt.close();
           socket_client.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }
}
