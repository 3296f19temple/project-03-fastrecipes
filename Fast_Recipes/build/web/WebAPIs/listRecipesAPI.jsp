<%@page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8"%> 

<%@page language="java" import="dbUtils.*" %>
<%@page language="java" import="model.recipe.*" %> 
<%@page language="java" import="view.RecipeView" %> 
<%@page language="java" import="com.google.gson.*" %>
<%@page language="java" import="java.sql.*" %>
<%
    {
   StringDataList strDataList = new StringDataList();

    System.out.println("*** Ready to get Db Connection.");
    DbConn dbc = new DbConn();
    strDataList.dbError = dbc.getErr(); // returns "" if connection is good, else db error msg.
    System.out.println("*** Db Error is this (empty string means all good): " + dbc.getErr());
    if (strDataList.dbError.length() == 0) { // if got good DB connection,
        try {
            String sql = "SELECT * FROM recipe";

            System.out.println("*** Ready to prepare statement. Sql is: " + sql);
            PreparedStatement stmt = dbc.getConn().prepareStatement(sql);

            System.out.println("*** Ready to execute the sql.");
            ResultSet results = stmt.executeQuery();
            while (results.next()) {
                System.out.println("*** Ready to extract one row from the result set.");
                strDataList.add(results);
            }
            results.close();
            stmt.close();
        } catch (Exception e) {
            System.out.println("*** Exception thrown, messages is: " + e.getMessage());
            StringData sd = new StringData();
            sd.errorMsg = "Exception thrown, messages is: " + e.getMessage();
            strDataList.add(sd);
        }
    }
        dbc.close(); // EVERY code path that opens a db connection, must also close it - no DB Conn leaks.
    Gson gson = new Gson();
    out.print(gson.toJson(strDataList).trim());
    }
    
    
    // This object (from the GSON library) can to convert between JSON <-> POJO (plain old java object) 

%>
