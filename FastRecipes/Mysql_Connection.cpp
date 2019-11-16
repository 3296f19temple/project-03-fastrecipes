#include <stdlib.h>
#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include "Mysql_Connection.h"

const sql::SQLString server = "localhost:3306";
const sql::SQLString user = "root";
const sql::SQLString password = "password";
const sql::SQLString schema = "fast_recipes";

using namespace std;

void getRecipe(sql::SQLString rname) {

	cout << endl;

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = nullptr;
	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("\
			SELECT recipe_name, category, prep_time, cook_time, serving_count\
			FROM recipe\
			WHERE recipe_name = ?");

		pstmt->setString(1, rname);

		res = pstmt->executeQuery();

		while (res->next()) {
			cout << "Recipe: " << res->getString("recipe_name").c_str();
			cout << ", Category: " << res->getString("category").c_str();
			cout << ", Prep Time: " << res->getInt("prep_time");
			cout << ", Cook Time: " << res->getInt("cook_time");
			cout << ", Serving Coutn: " << res->getInt("serving_count");
			cout << "." << endl;
		}
		delete res;
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete res;
		delete pstmt;
		delete con;
	}
}

void insertRecipeTable(Recipe_Table recipe) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_recipe(?,?,?,?,?,?)");

		recipe.recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe.recipe_name);
		recipe.url.compare("") == 0 ?
			pstmt->setNull(2, sql::DataType::VARCHAR) :
			pstmt->setString(2, recipe.url);
		recipe.category.compare("") == 0 ?
			pstmt->setNull(3, sql::DataType::VARCHAR) :
			pstmt->setString(3, recipe.category);
		recipe.prep_time == NULL ?
			pstmt->setNull(4, sql::DataType::INTEGER) :
			pstmt->setInt(4, recipe.prep_time);
		recipe.cook_time == NULL ?
			pstmt->setNull(5, sql::DataType::INTEGER) :
			pstmt->setInt(5, recipe.cook_time);
		recipe.serving_count == NULL ?
			pstmt->setNull(6, sql::DataType::INTEGER) :
			pstmt->setInt(6, recipe.serving_count);

		pstmt->execute();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
	}
}

void insertIngredientTable(sql::SQLString recipe_name, Recipe_Ingredient_Table ingredient) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_recipe_ingredient(?,?,?,?)");

		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);
		ingredient.ingredient_name.compare("") == 0 ?
			pstmt->setNull(2, sql::DataType::VARCHAR) :
			pstmt->setString(2, ingredient.ingredient_name);
		ingredient.quantity == NULL ?
			pstmt->setNull(3, sql::DataType::INTEGER) :
			pstmt->setInt(3, ingredient.quantity);
		ingredient.unit.compare("") == 0 ?
			pstmt->setNull(4, sql::DataType::VARCHAR) :
			pstmt->setString(4, ingredient.ingredient_name);

		pstmt->execute();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
	}
}

void insertStepTable(sql::SQLString recipe_name, Step_Table step) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("CALL insert_step(?,?,?)");

		recipe_name.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, recipe_name);
		step.step_number == NULL ?
			pstmt->setNull(2, sql::DataType::INTEGER) :
			pstmt->setInt(2, step.step_number);
		step.instruction.compare("") == 0 ?
			pstmt->setNull(3, sql::DataType::VARCHAR) :
			pstmt->setString(3, step.instruction);


		pstmt->execute();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ")" << endl;
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
	}
}

void insertRecipe(Recipe recipe) {

	insertRecipeTable(recipe.recipe);
	for (Step_Table table : recipe.steps) {
		insertStepTable(recipe.recipe.recipe_name, table);
	}
	for (Recipe_Ingredient_Table ingredient : recipe.ingredients) {
		insertIngredientTable(recipe.recipe.recipe_name, ingredient);
	}
}

void Mysql_Connection_Tester() {
	Recipe_Table rt = { "scrambled eggs", "", "breakfast", 10, 10, 2 };
	Step_Table st1 = { 1, "break eggs and scramble" };
	Step_Table st2 = { 2, "fry in pan" };
	Recipe_Ingredient_Table rit1 = { "egg", 2, "eggs" };
	Recipe_Ingredient_Table rit2 = { "salt", 0.25, "tsp" };
	
	Recipe recipe = { rt, {st1, st2}, {rit1, rit2} };

	insertRecipe(recipe);
}
