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
    recipe_name VARCHAR(255) NOT NULL,
	step_number INT NOT NULL,
    instruction TEXT,
    CONSTRAINT pk_step PRIMARY KEY (recipe_name, step_number),
    CONSTRAINT fk_step_recipe FOREIGN KEY (recipe_name) REFERENCES recipe(recipe_name) ON DELETE CASCADE);

CREATE TABLE ingredient (
	recipe_name VARCHAR(255) NOT NULL,
    ingredient_name VARCHAR(255) NOT NULL,
    quantity NUMERIC(6, 2),
    unit VARCHAR(65),
    CONSTRAINT pk_ingredient PRIMARY KEY (recipe_name, ingredient_name),
    CONSTRAINT fk_ingredient_recipe FOREIGN KEY (recipe_name) REFERENCES recipe(recipe_name) ON DELETE CASCADE);

DROP PROCEDURE get_recipe_table;

DELIMITER $$
CREATE PROCEDURE get_recipe_table (IN get_recipe_name VARCHAR(255))
BEGIN
    DECLARE recipe_name VARCHAR(255);
    DECLARE url VARCHAR(2047);
    DECLARE category VARCHAR(63);
	DECLARE prep_time INT;
	DECLARE cook_time INT;
	DECLARE serving_count INT;

    SELECT recipe_name, url, category, prep_time, cook_time, serving_count
    INTO recipe_name, url, category, prep_time, cook_time, serving_count
    FROM recipe
    WHERE recipe_name = get_recipe_name;
END $$

CREATE PROCEDURE insert_recipe(
	IN new_recipe_name VARCHAR(255),
	IN new_url VARCHAR(2047),
    IN new_category VARCHAR(63),
	IN new_prep_time INT,
	IN new_cook_time INT,
	IN new_serving_count INT)
BEGIN
INSERT INTO recipe
VALUES (new_recipe_name, new_url, new_category, new_prep_time, new_cook_time, new_serving_count);
/* // Using this method would prevent attempting to insert a duplicate record
    SELECT new_recipe_name, new_url, new_category, new_prep_time, new_cook_time, new_serving_count
    FROM dual
    WHERE NOT EXISTS (
		SELECT *
        FROM recipe
        WHERE recipe_name = new_recipe_name);
*/
END$$

CREATE PROCEDURE insert_step(
    IN new_recipe_name VARCHAR(255),
    IN new_step_number INT,
    IN new_instruction TEXT)
BEGIN
INSERT INTO step
VALUES (new_recipe_name, new_step_number, new_instruction);
/* // Using this method would prevent attempting to insert a duplicate record
    SELECT new_recipe_name, new_step_number, new_instruction
    FROM dual
    WHERE NOT EXISTS (
        SELECT *
        FROM step
        WHERE recipe_name = new_recipe_name AND step_number = new_step_number);
*/
END$$

CREATE PROCEDURE insert_ingredient(
	IN new_recipe_name VARCHAR(255),
    IN new_ingredient_name VARCHAR(255),
    IN new_quantity DECIMAL(6,2),
    IN new_unit VARCHAR(255))
BEGIN
INSERT INTO ingredient
VALUES (new_recipe_name, new_ingredient_name, new_quantity, new_unit);
/* // Using this method would prevent attempting to insert a duplicate record
	SELECT new_recipe_name, new_ingredient_name, new_quantity, new_unit
    FROM dual
	WHERE NOT EXISTS (
		SELECT *
        FROM ingredient
        WHERE recipe_name = new_recipe_name AND ingredient_name = new_ingredient_name);
*/
END$$

CREATE PROCEDURE delete_recipe(
    IN del_recipe_name VARCHAR(255))
BEGIN
    DELETE FROM recipe WHERE recipe_name = del_recipe_name;
END$$
DELIMITER ;

# DROP SCHEMA fast_recipes;