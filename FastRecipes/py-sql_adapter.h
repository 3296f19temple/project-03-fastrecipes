#pragma once

#include "Mysql_Connection.h"
#include "webscrape.h"

void pyToMysqlRecipe(Py_recipe& py_recipe, SQL_recipe& sql_recipe);

void insertFromDatFile(std::string filename);
