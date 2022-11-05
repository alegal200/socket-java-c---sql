import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class HTTP_Server_Runable implements  Runnable {
private int id = 0 ;

    @Override
    public void run() {
        try{
            int port_num = 8081 ;
            ServerSocket ss = new ServerSocket (port_num) ;
            while ( true ) {
                Socket ts = ss.accept () ;
                //       OutputStream out = ts.getOutputStream() ;
                //       InputStream in = ts.getInputStream() ;
                BufferedReader buffRead = new BufferedReader(new InputStreamReader(ts.getInputStream())) ;
                String s ;
                while ( ( s = buffRead.readLine() ) != null ) {

                    System.out.println(s);
                    if(s.isEmpty())
                        break;

                    if(s.startsWith("GET")){
                        String id_str =" ";
                        /// id parsing
                        if(s.split("id=").length > 1) {
                            id_str = s.split("id=")[1];
                            if (id_str.contains("&&"))
                                id_str = id_str.split("&&")[0];
                            else
                                id_str = id_str.split(" ")[0];
                            System.out.println("id est ->" + id_str + "<-");
                        }
                        ///end id parsing


                    }


                }
                OutputStream client_output = ts.getOutputStream() ;

                OutPutPrinter output_client_print = new OutPutPrinter(client_output);
                if(id ==0)
                    output_client_print.firstPage();
                else{

                }

                buffRead.close();
                output_client_print.close();

                ts.close();
            }


        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
