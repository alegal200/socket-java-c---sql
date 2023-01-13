import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class C_read_server {



    private String ip = "192.168.91.130";
    private int port  = 50011;
    private int id = 0 ; 
    private String str = "";
    
    public C_read_server (int idd){
        id =idd ;
        exec();
    }
    
    private void exec() {

        try {
           Socket socket_client = new Socket(ip,port);
           BufferedOutputStream out = new BufferedOutputStream(  socket_client.getOutputStream()  ) ;
           PrintWriter wrt = new PrintWriter(out) ;       
           InputStream inputStream = socket_client.getInputStream();
           wrt.write("tok:112233445566@"+id+"*");
           wrt.flush();
           String s;          
           byte[] array = new byte[500];
           inputStream.read(array);       
           String data = new String(array);
           str = data ;

           inputStream.close();
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
    
        /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

     public String getval() {
         return str ; 
    }
    
}
