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
                   // if(s.isEmpty())
                   //     break;

                    if(s.startsWith("GET")){
                        String id_str =" ";
                        /// id parsing
                        if(s.split("id%3D=").length > 1) {
                            id_str = s.split("id%3D=")[1];
                            if (id_str.contains("&&"))
                                id_str = id_str.split("&")[0];
                            else
                                id_str = id_str.split(" ")[0];
                            id = Integer.parseInt(id_str) ;
                            C_read_server C_th = new C_read_server( id) ;
                            String ligneC = C_th.getval();                         
                            System.out.println("ligne recu par le c"+ligneC);
                           try{
                               
                            String[] l = ligneC.split(";");
                            String[] d = l[2].split("/");
                            int anne = Integer.parseInt(d[2]);
                            int age = 2023 - anne ; //todo recup year 2023 better  
                            ArrayList<actyObj> actlst  = sqlconnector.getacty(age);
                            output_client_print.actyPage(actlst,id);
                            output_client_print.send();   
                               
                           }catch(Exception eer ){
                               output_client_print.erreursend();
                              
                           }
    
                            
                        }
                        ///end id parsing
                        if(id ==0){
                            output_client_print.firstPage();
                            output_client_print.send();
                        }


                    }
                    else  if(s.startsWith("POST")){
                        try{
                            String id_str =" ";
                         if(s.split("=").length > 1) {
                             String act_str= s.split("=")[1];
                             act_str= act_str.split("pers")[0];
                             id_str = s.split("=")[2];
                              id_str= id_str.split(" ")[0];
                            //id = Integer.parseInt(id_str) ;
                             id = Integer.parseInt(id_str) ;
                            C_read_server C_th = new C_read_server( id) ;
                            String ligneC = C_th.getval();  
                            String[] l = ligneC.split(";");
                            String[] d = l[2].split("/");
                            int anne = Integer.parseInt(d[2]);
                            int age = 2023 - anne ; //todo recup year 2023 better  
                            if(  !( l[3].startsWith("Y") || l[3].startsWith("y") ) )
                                throw new Exception("errr");
                            ArrayList<actyObj> actlst  = sqlconnector.getacty(age);
                             for (int i = 0; i < actlst.size(); i++) {
                                
                                 if(actlst.get(i).getid().equals(act_str)){
                                     System.out.println("POST de l acti:"+act_str+" et id personne"+id_str );
                                     sqlconnector.addDate(id_str,act_str);
                                     output_client_print.execpage(); 
                                 }
                                 
                             }
                            
                             
                             
                               
                         }
                        // else
                            // output_client_print.erreursend();
                        }catch(Exception esp){
                             output_client_print.personnenotherepage(); 
                        }
                     
                     }
                    
                         
                
                }
                 
                
                

                buffRead.close();
                output_client_print.close();

                ts.close();



        }catch (Exception e){
            
            try{
             OutputStream client_output = ts.getOutputStream() ;
             OutPutPrinter output_client_print = new OutPutPrinter(client_output);
             output_client_print.erreurgeneralsend();
             ts.close();
            }
            catch(Exception exp){
                exp.printStackTrace();
            }
        }
    }
}


