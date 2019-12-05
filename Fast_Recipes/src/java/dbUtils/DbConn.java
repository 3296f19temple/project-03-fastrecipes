package dbUtils;

import java.sql.DriverManager;
import java.sql.Connection;
import java.util.Properties;

/**
 * Wrapper class for database connection. Constructor opens connection. Close
 * method closes connection.
 */
public class DbConn {

    private String errMsg = ""; // will remain "" unless error getting connection
    private java.sql.Connection conn = null;

    public DbConn() {
        String DB_URL = "jdbc:mysql://localhost:3306/fast_recipes";
        String User = "root";
        String Password = "password";

        try {
            String DRIVER = "com.mysql.jdbc.Driver";
            Class.forName(DRIVER);
            try {
                // Assume you are running from home using tunneling...
                String url = "jdbc:mysql://localhost:3306/fast_recipes";
                Properties prop = new Properties();
                prop.setProperty("user", "root");
                prop.setProperty("password", "password");
                prop.setProperty("characterEncoding", "latin1");
                prop.setProperty("useConfigs", "maxPerformance");
                prop.setProperty("useSSL", "false");
                this.conn = DriverManager.getConnection(url, prop);

            } catch (Exception e) { // cant get the connection
                recordError("Problem getting connection:" + e.getMessage());
                
            }
        } catch (Exception e) { // cant get the driver...
            recordError("Problem getting driver:" + e.getMessage());
        }
        //System.out.println("Finished the connection");
    } // method

    private void recordError(String errorMsg) {
        this.errMsg = errorMsg;
        System.out.println("Error in DbConn. " + errorMsg);
    }

    /* Returns database connection for use in SQL classes.  */
    public Connection getConn() {
        return this.conn;
    }

    /* Returns database connection error message or "" if there is none.  */
    public String getErr() {
        return this.errMsg;
    }

    /**
     * Close database connection.
     */
    public void close() {

        if (conn != null) {
            try {
                conn.close();
            } // try
            catch (Exception e) {
                // Don't care if connection was already closed. Do nothing.
            } // catch
        } // if
    } // method

    // This method gets run when GC (garbage collection) runs 
    // and we are never sure when this might happen, but still it's better than 
    // nothing to try to be sure that all db connections are closed when 
    // the dbConn object is no longer referenced. Maybe we can get the IT 
    // Administrator to set the GC to run more often.
    protected void finalize() {
        this.close(); // 
    }

} // class