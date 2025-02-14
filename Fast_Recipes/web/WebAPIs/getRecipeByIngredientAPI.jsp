<%@page contentType="application/json; charset=UTF-8" pageEncoding="UTF-8"%> 

<%@page language="java" import="dbUtils.*" %>
<%@page language="java" import="model.recipe.*" %> 
<%@page language="java" import="view.RecipeView" %> 
<%@page language="java" import="com.google.gson.*" %>

<%

    // default constructor creates nice empty StringDataList with all fields "" (empty string, nothing null).
    StringDataList list = new StringDataList();

    String searchId = request.getParameter("recipeName");
    if (searchId == null) {
        list.dbError = "Cannot search for user - 'recipeName' most be supplied";
    } else {

        //DbConn dbc = new DbConn();
        //list.dbError = dbc.getErr(); // returns "" if connection is good, else db error msg.
        
    System.out.println("*** Ready to get Db Connection.");
    DbConn dbc = new DbConn();
    list.dbError = dbc.getErr(); // returns "" if connection is good, else db error msg.
    System.out.println("*** Db Error is this (empty string means all good): " + dbc.getErr());

        if (list.dbError.length() == 0) { // if got good DB connection,

            System.out.println("*** Ready to call allUsersAPI");
            list = DbMods.findByName(dbc, searchId);  
        }

        dbc.close(); // EVERY code path that opens a db connection, must also close it - no DB Conn leaks.
    }
    // This object (from the GSON library) can to convert between JSON <-> POJO (plain old java object) 
    Gson gson = new Gson();
    out.print(gson.toJson(list).trim());
%>