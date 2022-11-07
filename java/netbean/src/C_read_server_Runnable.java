import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class C_read_server_Runnable implements  Runnable{



    private String ip = "192.168.91.130";
    private int port  = 50011;
    private int id = 0 ; 
    private String str = "alexandre;le;11/05/2019;Y";
    
    public C_read_server_Runnable (int idd){
        id =idd ;
    }
    public C_read_server_Runnable (){
        
    }
    
    @Override
    public void run() {

        try {
           Socket socket_client = new Socket(ip,port);
           BufferedOutputStream out = new BufferedOutputStream(  socket_client.getOutputStream()  ) ;
           PrintWriter wrt = new PrintWriter(out) ;
           BufferedReader buffRead = new BufferedReader(new InputStreamReader(socket_client.getInputStream())) ;
           wrt.write("tok:112233445566@"+id+"*");
           wrt.flush();
           String s ;
                while ( ( s = buffRead.readLine() ) != null ) {

                    System.out.println("-"+s+"-");
                    str = s ;
                    if(s.isEmpty())
                        break;
                }
           
           buffRead.close();
           wrt.close();
           

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
