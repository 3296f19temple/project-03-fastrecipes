package model.recipe;

import dbUtils.FormatUtils;
import java.sql.ResultSet;


/* The purpose of this class is just to "bundle together" all the 
 * character data that the user might type in when they want to 
 * add a new Customer or edit an existing customer.  This String
 * data is "pre-validated" data, meaning they might have typed 
 * in a character string where a number was expected.
 * 
 * There are no getter or setter methods since we are not trying to
 * protect this data in any way.  We want to let the JSP page have
 * free access to put data in or take it out. */
public class StringData {

    //public String recipeId = "";
    public String recipeName = "";
    public String url = "";
    public String category = "";
    public String prepTime = "";
    public String cookTime = "";
    public String servingCount = "";   
    public String steps = "";
    public String errorMsg = "";

    // default constructor leaves all data members with empty string (Nothing null).
    public StringData() {
    }

    // overloaded constructor sets all data members by extracting from resultSet.
    public StringData(ResultSet results) {
        try {
            //this.recipeId = FormatUtils.formatInteger(results.getObject("recipe_id"));
            this.recipeName = FormatUtils.formatString(results.getObject("recipe_name"));
            this.url = FormatUtils.formatString(results.getObject("url"));
            this.category = FormatUtils.formatString(results.getObject("category"));
            this.prepTime = FormatUtils.formatInteger(results.getObject("prep_time"));
            this.cookTime = FormatUtils.formatInteger(results.getObject("cook_time"));
            this.servingCount = FormatUtils.formatInteger(results.getObject("serving_count"));            
        } catch (Exception e) {
            this.errorMsg = "Exception thrown in model.recipe.StringData (the constructor that takes a ResultSet): " + e.getMessage();
        }
    }

    public int getCharacterCount() {
        String s =  this.recipeName + this.url + this.category
                + this.prepTime + this.cookTime  + this.servingCount;
        return s.length();
    }

    public String toString() {
        return " Recipe Name: " + this.recipeName
                + ", url: " + this.url
                + ", Category: " + this.category
                + ", Prep Time: " + this.prepTime
                + ", Cook Time: " + this.cookTime
                + ", Serving Count: " + this.servingCount;
    }
}
