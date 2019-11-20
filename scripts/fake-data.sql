INSERT INTO recipe
VALUES
	('steak', NULL, 'dinner', 20, 8, 1),
    ('salad', NULL, 'all', 20, 0, 4),
    ('cake', NULL, 'dessert', 20, 60, 8);

INSERT INTO step
VALUES
	('steak', 1, 'light grill'),
    ('steak', 2, 'cook for 3 minutes per side, flipping once'),
    ('salad', 1, 'add ingredients to bowl'),
    ('salad', 2, 'toss'),
    ('cake', 1, 'add dry ingredients to bowl and mix'),
    ('cake', 2, 'add wet ingredients to seperate bowl and mix just enought to form uniform mixture'),
    ('cake', 3, 'add dry ingredients to wet and stir gently, just enough to form uniform mixture'),
    ('cake', 4, 'pour into cake pan'),
    ('cake', 5, 'bake for one hour at 375');

INSERT INTO ingredient
VALUES
	('steak', 'steak', 1, 'steak'),
    ('steak', 'salt', 3, 'tsps'),
    ('salad', 'lettuce', 4, 'cups'),
    ('salad', 'spinach', 4, 'cups'),
    ('salad', 'dressing', 0.5, 'cups'),
    ('cake', 'flour', 2, 'cups'),
    ('cake', 'sugar', 0.25, 'cups'),
    ('cake', 'milk', 2, 'cups'),
    ('cake', 'egg', 1, 'egg'),
    ('cake', 'salt', 0.5, 'tsp');
