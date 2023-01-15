
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
        System.out.println("sql part ");
        ArrayList<actyObj> actlst =  new  ArrayList<actyObj> ();
        try {
            
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/ALEXDB"+"?characterEncoding=utf8", "root", "rootmysql11"); //todo better load from a file ( here it is bc is a homework and not a realy project 
            PreparedStatement stmt = conn.prepareStatement("select * from date_acty left join activity on date_acty.acti_key  = activity.id where ? < max_age and ? > min_age;");
            stmt.setInt(1,age);
            stmt.setInt(2,age);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) 
                 actlst.add( new actyObj(rs.getString("id"),rs.getString("name"),rs.getString("date_start"),rs.getString("num_min")));
   
            
            conn.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return actlst;
    }
    
    
    public static void addDate(String id , String acty){
        
        try{
            System.out.println("sql avec :"+id +" et acti :"+acty);
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/ALEXDB"+"?characterEncoding=utf8", "root", "rootmysql11"); //todo better load from a file ( here it is bc is a homework and not a realy project 
            PreparedStatement stmt = conn.prepareStatement("insert into reservation (id_vac , id_date_acti) VALUES  (? , ?) ");
            stmt.setString(1,id);
            stmt.setString(2,acty);
            stmt.executeUpdate();            
            
            conn.close();
            
        }catch(Exception eeeeee){
            //eeeeee.printStackTrace();
        }
            return;
        
    }
    
}
