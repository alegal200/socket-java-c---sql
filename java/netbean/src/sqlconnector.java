
import java.sql.Array;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;


public class sqlconnector {
   
public sqlconnector(){

}
    
    /**
     *
     * @param age
     * @return
     */
    public static ArrayList<actyObj>  getacty(int age ){
        ArrayList<actyObj> actlst =  new  ArrayList<actyObj> ();
        try {
            
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/ALEXDB"+"?characterEncoding=utf8", "root", "rootmysql11");
            PreparedStatement stmt = conn.prepareStatement("select * from date_acty left join activity on date_acty.acti_key  = activity.id where ? < max_age and ? > min_age;");
            stmt.setInt(1,age);
            stmt.setInt(2,age);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                 actlst.add( new actyObj(rs.getString("id"),rs.getString("name"),rs.getString("date_start"),rs.getString("num_min")));
             }
             
            
        } catch (Exception ex) {
            // handle the error
        }
        return actlst;
    }
    
}
