#include <stdlib.h>
#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#include "Mysql_Connection.h"

const std::string server = "localhost:3306";
const std::string user = "root";
const std::string password = "password";
const std::string schema = "fast_recipes";

using namespace std;

int getRecipe(sql::SQLString rname) {

	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;

		driver = get_driver_instance();
		con = driver->connect(server.c_str(), user.c_str(), password.c_str());
		con->setSchema(schema.c_str());

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
			cout << ", Serving Coutn: " << res->getInt("serving_count") << "." << endl;
		}

		delete res;
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		const std::string state = e.getSQLState().c_str();
		cout << ", SQLState: " << state << " )" << endl;
	}
	cout << endl;
	return 0;
}

int insertRecipe(Recipe recipe) {

	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::PreparedStatement* pstmt;

		driver = get_driver_instance();
		con = driver->connect(server.c_str(), user.c_str(), password.c_str());
		con->setSchema(schema.c_str());

		pstmt = con->prepareStatement("\
			INSERT INTO recipe\
			VALUES (DEFAULT, ?, ?, ?, ?, ?, ?)");
		if (recipe.recipe_name.compare("") == 0) {
			pstmt->setNull(1, sql::DataType::VARCHAR);
		}
		else {
			pstmt->setString(1, recipe.recipe_name);
		}
		if (recipe.url.compare("") == 0) {
			pstmt->setNull(2, sql::DataType::VARCHAR);
		}
		else {
			pstmt->setString(2, recipe.url);
		}
		if (recipe.category.compare("") == 0) {
			pstmt->setNull(3, sql::DataType::VARCHAR);
		}
		else {
			pstmt->setString(3, recipe.category);
		}
		if (recipe.prep_time == NULL) {
			pstmt->setNull(4, sql::DataType::INTEGER);
		}
		else {
			pstmt->setInt(4, recipe.prep_time);
		}
		if (recipe.cook_time == NULL) {
			pstmt->setNull(5, sql::DataType::INTEGER);
		}
		else {
			pstmt->setInt(5, recipe.cook_time);
		}
		if (recipe.serving_count == NULL) {
			pstmt->setNull(6, sql::DataType::INTEGER);
		}
		else {
			pstmt->setInt(6, recipe.serving_count);
		}

		pstmt->execute();

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException & e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ ")";
		cout << "# ERR: " << e.what();
		cout << ", SQLState: " << e.getSQLState().c_str() << " )" << endl;
	}
	cout << endl;
	return 0;
}

void Mysql_Connection_Tester() {
	Recipe recipe = {};
	recipe.recipe_name = "toast";
	recipe.category = "breakfast";
	recipe.prep_time = 2;
	recipe.cook_time = 5;
	recipe.serving_count = 2;

	insertRecipe(recipe);
	getRecipe(recipe.recipe_name);
}
