import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class HTTP_Server_Runable implements  Runnable {
private int id = 0 ;
private Socket ts ;

    public HTTP_Server_Runable(Socket tts) {
        ts= tts ;

    }

    @Override
    public void run() {
        try{
 
                BufferedReader buffRead = new BufferedReader(new InputStreamReader(ts.getInputStream())) ;
                OutputStream client_output = ts.getOutputStream() ;
                OutPutPrinter output_client_print = new OutPutPrinter(client_output);
                String s ;
                while ( ( s = buffRead.readLine() ) != null ) {

                    System.out.println(s);
                    if(s.isEmpty())
                        break;

                    if(s.startsWith("GET")){
                        String id_str =" ";
                        /// id parsing
                        if(s.split("id%3D=").length > 1) {
                            id_str = s.split("id%3D=")[1];
                            if (id_str.contains("&&"))
                                id_str = id_str.split("&")[0];
                            else
                                id_str = id_str.split(" ")[0];
                            System.out.println("id est ->" + id_str + "<-");
                            id = Integer.parseInt(id_str) ;
                             C_read_server_Runnable C_th = new C_read_server_Runnable( id) ;
                            
                            Thread C_Thread = new Thread(C_th  );
                            C_Thread.start();
                           // String ligneC = C_th.getval();
                            String ligneC = "default;a;11/05/2000;Y" ;
                            System.out.println("ligne recu par le c"+ligneC);
                           try{
                               
                           String[] l = ligneC.split(";");
                            String[] d = l[2].split("/");
                            int anne = Integer.parseInt(d[2]);
                            int age = 2022 - anne ; //todo recup year better  
                            ArrayList<actyObj> actlst  = sqlconnector.getacty(age);
                            output_client_print.actyPage(actlst);
                            output_client_print.send();
                               
                               
                           }catch(Exception eer ){
                               output_client_print.erreur();
                               output_client_print.send();
                           }
                            
                            
                            
                            
                        }
                        ///end id parsing


                    }


                }
                System.out.println("id"+id);
                if(id ==0){
                    output_client_print.firstPage();
                    output_client_print.send();
                }
                else{

                }

                buffRead.close();
                output_client_print.close();

                ts.close();



        }catch (Exception e){
            e.printStackTrace();
        }
    }
}


