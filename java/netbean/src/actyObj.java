
public class actyObj {

  
    private String name ;
    private String date_start;
    private String num_min ;
    private String id ;
    
       
    public actyObj(String is ,String  n , String  da , String  min) {
            id = is ;
            name = n ;
            date_start = da ;
            num_min = min ;
    }
    
    
      /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return the date_start
     */
    public String getDate_start() {
        return date_start;
    }

    /**
     * @param date_start the date_start to set
     */
    public void setDate_start(String date_start) {
        this.date_start = date_start;
    }

    /**
     * @return the num_min
     */
    public String getNum_min() {
        return num_min;
    }

    /**
     * @param num_min the num_min to set
     */
    public void setNum_min(String num_min) {
        this.num_min = num_min;
    }

    public String getid() {
        return id ;
     }
    
    
}
