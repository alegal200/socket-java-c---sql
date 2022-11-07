import java.io.IOException;
import java.io.OutputStream;

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



/*
<!DOCTYPE html>
<html>
<body>

<h1>VACANCIER FINDER</h1>

<b>id du vac :</b>
<form  method="GET">
    <input  name="id=">
    <input type="submit" value="Send">
<form>

</body>
</html>


 */






}
