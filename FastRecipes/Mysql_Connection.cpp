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

int getRecipe(sql::SQLString rname) {

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
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete res;
		delete pstmt;
		delete con;
		return 1;
	}


	return 0;
}

int insertRecipe(Recipe_Table recipe) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("INSERT INTO recipe\
			VALUES (DEFAULT, ?, ?, ?, ?, ?, ?)");

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
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
		return 1;
	}


	return 0;
}

int insertIngredient(sql::SQLString ingredient) {

	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("INSERT INTO ingredient\
		VALUES (DEFAULT, ?)");

		ingredient.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, ingredient);

		pstmt->execute();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
		return 1;
	}
	return 0;
}

int insertStep(Step_Table step) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::PreparedStatement* pstmt = nullptr;

	try {
		driver = get_driver_instance();
		con = driver->connect(server, user, password);
		con->setSchema(schema);

		pstmt = con->prepareStatement("INSERT INTO recipe\
			VALUES (DEFAULT, ?, ?)");

		step.instruction.compare("") == 0 ?
			pstmt->setNull(1, sql::DataType::VARCHAR) :
			pstmt->setString(1, step.instruction);
		step.step_number == NULL ?
			pstmt->setNull(2, sql::DataType::INTEGER) :
			pstmt->setInt(2, step.step_number);

		pstmt->execute();
		delete pstmt;
		delete con;
	} 
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		cout << ", SQLErrorCode: " << e.getErrorCode() << " )" << endl;
		delete pstmt;
		delete con;
		return 1;
	}
}

void Mysql_Connection_Tester() {
	Recipe_Table recipe = {};
	recipe.recipe_name = "toast";
	recipe.category = "breakfast";
	recipe.prep_time = 2;
	recipe.cook_time = 5;
	recipe.serving_count = 2;

	insertRecipe(recipe);
	getRecipe(recipe.recipe_name);
}
