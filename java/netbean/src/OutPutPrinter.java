import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;

public class OutPutPrinter {
    private OutputStream o ;
    public OutPutPrinter(OutputStream out){
        o = out ;
    }

    private void startPage() throws IOException {
        o.write("HTTP/1.1 200 ok \r\n".getBytes());
        o.write("\r\n".getBytes());
        o.write("<!DOCTYPE html>".getBytes());
        o.write("<html>".getBytes());
        o.write("<body>".getBytes());
        o.write("<h1>VACANCIER FINDER</h1>".getBytes());


        //o.write("".getBytes());
    }
    private void endPage() throws IOException {
        o.write("</body>".getBytes());
        o.write("</html>".getBytes());
        o.write("\r\n\r\n".getBytes());
        o.flush();
    }
    public void close() throws IOException  {
        o.close();
    }

    public void  firstPage() throws IOException {
        this.startPage();
        o.write("<p>id du vac :</p>".getBytes());
        o.write("<form  method=\"GET\">".getBytes());
        o.write("<input  name=\"id=\">".getBytes());
        o.write("<input type=\"submit\" value=\"Send\">".getBytes());
        o.write("<form>".getBytes());

        this.endPage();

    }


public    void actyPage(ArrayList<actyObj> actlst) throws IOException {
    
        this.startPage();
        o.write("<table>".getBytes());
        o.write("<tr>".getBytes());
        o.write("<th>id</th>".getBytes()); 
        o.write("<th>Nom</th>".getBytes()); 
        o.write("<th>Date </th>".getBytes()); 
        o.write("<th>temps en min</th>".getBytes());
        o.write("<th>s'inscrire</th>".getBytes());
        o.write("</tr>".getBytes());    
        for(int i = 0 ; i <actlst.size() ; i++ ){
            o.write("<tr>".getBytes());
            o.write(("<td>"+actlst.get(i).getid()+"</td>").getBytes());
            o.write(("<td>"+actlst.get(i).getName()+"</td>").getBytes());
            o.write(("<td>"+actlst.get(i).getDate_start()+"</td>").getBytes());
            o.write(("<td>"+actlst.get(i).getNum_min()+"</td>").getBytes());
            o.write(("<td>").getBytes());
            o.write("<form  method=\"POST\">".getBytes());
            o.write("<input type=\"submit\" value=\"Send\">".getBytes());
            o.write(("<td>").getBytes()); 
            o.write("<form>".getBytes());
            o.write(("</td>").getBytes());
            
            
            o.write("</tr>".getBytes());
        }


        o.write("</table>".getBytes());

        this.endPage();
    }



    public void erreur() throws IOException {
        
        o.write("HTTP/1.1 898 id introuvable \r\n".getBytes());
        o.write("\r\n".getBytes());
        o.write("<!DOCTYPE html>".getBytes());
        o.write("<html>".getBytes());
        o.write("<body>".getBytes());
        o.write("<h1>VACANCIER FINDER</h1>".getBytes());
        o.write("<p>erreur du vac</p>".getBytes());
        this.endPage();

        
    }

    




}
