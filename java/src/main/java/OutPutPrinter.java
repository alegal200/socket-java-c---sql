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
    }
    private void endPage() throws IOException {
        o.write("\r\n\r\n".getBytes());
        o.flush();
    }
    public void close() throws IOException  {
        o.close();
    }

    public void  firstPage() throws IOException {
        this.startPage();
        o.write("<b>id du vac :</b>".getBytes());
        o.write("<textarea></textarea>".getBytes());
        o.write("<button>send</button>".getBytes());
        this.endPage();

    }










}
