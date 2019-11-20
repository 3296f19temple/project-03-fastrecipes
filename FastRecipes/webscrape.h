#pragma once

#include <string>
#include <vector>

class Py_ingredient {
public:
	Py_ingredient() :amount{-1}, unit{"n/a"}, name{"n.a"} {}
	// TODO: support fraction
	std::string amount;
	std::string unit;
	std::string name;
};

class Py_recipe {
public:
	Py_recipe() {
		name = "n/a";
		url = "n/a";
		img_url = "n/a";
		category = "n/a";
		prep_time = -1;
		cook_time = -1;
		num_servings = -1;
		ingredients;
		instructions;
	}

	std::string name;
	std::string url;
	std::string img_url;
	std::string category;
	int prep_time;
	int cook_time;
	int num_servings;
	std::vector<Py_ingredient> ingredients;
	std::vector<std::string> instructions;
};

void print_py_ingredient(const Py_ingredient& i);

void print_py_recipe(const Py_recipe& r);

bool read_recipe(std::ifstream& file, Py_recipe& recipe);

std::string ltrim(const std::string& s);

bool check_field(const std::string& name, std::ifstream& stream);

bool check_field(const std::string& name, std::ifstream& stream, bool error_check);

bool get_ingredient(std::ifstream& stream, Py_recipe& recipe);

bool get_instruction(std::ifstream& stream, Py_recipe& recipe);
