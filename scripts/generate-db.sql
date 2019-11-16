CREATE SCHEMA fast_recipes;

USE fast_recipes;

CREATE TABLE recipe (
    recipe_name VARCHAR(255) NOT NULL,
    url VARCHAR(2047),
    category VARCHAR(63),
	prep_time INT,
	cook_time INT,
	serving_count INT,
    CONSTRAINT pk_recipe PRIMARY KEY (recipe_name));

CREATE TABLE step (
    recipe_name INT NOT NULL,
	step_number INT NOT NULL,
    instruction TEXT,
    CONSTRAINT pk_step PRIMARY KEY (recipe_name, step_number),
    CONSTRAINT fk_step_recipe FOREIGN KEY (recipe_name) REFERENCES recipe(recipe_name));

CREATE TABLE recipe_has_ingredient (
	recipe_name VARCHAR(255) NOT NULL,
    ingredient_name VARCHAR(255) NOT NULL,
    quantity NUMERIC(6, 2),
    unit VARCHAR(65),
    CONSTRAINT pk_recipe_has_ingredient PRIMARY KEY (recipe_name, ingredient_name),
    CONSTRAINT fk_recipe_ingredient FOREIGN KEY	(recipe_name) REFERENCES recipe(recipe_name));

DELIMITER $$
CREATE PROCEDURE insert_recipe (
	IN new_recipe_name VARCHAR(255),
    IN new_url VARCHAR(2047),
    IN new_category VARCHAR(63),
	IN new_prep_time INT,
	IN new_cook_time INT,
	IN new_serving_count INT)
BEGIN
    INSERT INTO recipe
    SELECT new_recipe_name, new_url, new_category, new_prep_time, new_cook_time, new_serving_count
    FROM dual
    WHERE NOT EXISTS (
		SELECT *
        FROM recipe
        WHERE recipe_name = new_recipe_name);
END$$
DELIMITER ;


# DROP SCHEMA fast_recipes;