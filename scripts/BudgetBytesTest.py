# Created by Matthew Majewski (BigBadBoris) on 11/13/2019
# This script is made to web-scrape recipes from the website
# budgetbytes.com. The html is nicely organized into distinct
# classes, which make it easy to separate ingredient names,
# amounts, and units of each amount.

# To figure out how to parse the html tree of a website to
# extract the information you want, I recomend using the
# "inspect element" feature built-in to firefox. To use this,
# right-click on the relevant text/region on the page, and the
# firefox debugger will pop up, high-lighting the relevant
# portion of the html. Inside the debugger, you can also mouse
# over a portion of the html, and the relevant region in the
# webpage will be high-lighted as well.

import bs4
import requests
import re
from os import path


class Recipe:
    def __init__(self):
        self.name = "n/a"
        self.url = "n/a"
        self.img_url = "n/a"
        self.category = "n/a"
        self.prep_time = "-1"
        self.cook_time = "-1"
        self.num_servings = "-1"
        self.ingredients = []
        self.instructions = []


class Ingredient:
    def __init__(self):
        self.amount = "n/a"
        self.unit = "n/a"
        self.name = "n/a"


def print_recipe(recipe):
    print("Name: ", recipe.name)
    print("Prep Time: ", recipe.prep_time)
    print("Cook Time: ", recipe.cook_time)
    # print("Total Time: ", recipe.total_time)
    print("Servings: ", recipe.num_servings)
    print("Ingredients: ")
    for ingredient in recipe.ingredients:
        print("\tName: ", ingredient.name)
        print("\tAmount: ", ingredient.amount)
        print("\tUnit: ", ingredient.unit)
    print("Instructions: ")
    for step in recipe.instructions:
        print()
        print(step)


def get_recipe_name(soup, Recipe):
    element = soup.select('.wprm-recipe-name')
    if element == []:
        return
    Recipe.name = element[0].text


def get_recipe_time(soup, Recipe):
    # get prep time
    element = soup.select('.wprm-recipe-prep_time')
    if element == []:
        return
    Recipe.prep_time = element[0].text
    # get cook time
    element = soup.select('.wprm-recipe-cook_time')
    if element == []:
        return
    Recipe.cook_time = element[0].text
    # get total time
    # element = soup.select('.wprm-recipe-total_time')
    # if element == []:
    #     return
    # Recipe.total_time = element[0].text


def get_recipe_image(soup, Recipe):
    element = soup.select('.wprm-recipe-image')
    if element == []:
        return
    child = element[0].children
    img = next(child)
    try:
        url = img['data-lazy-src']
    except:
        return
    if url is None:
        return
    Recipe.img_url = url


def get_recipe_servings(soup, Recipe):
    element = soup.select('.wprm-recipe-servings')
    if element == []:
        return
    Recipe.num_servings = element[0].text


def get_recipe_instructions(soup, Recipe):
    elements = soup.select('.wprm-recipe-instruction')
    if elements == []:
        return
    for element in elements:
        Recipe.instructions.append(element.text)


def get_recipe_ingredients(soup, Recipe):
    top_elements = soup.select('.wprm-recipe-ingredient')
    if top_elements == []:
        return
    for top_element in top_elements:
        children = top_element.children
        ingredient = Ingredient()
        for child in children:
            if isinstance(child, str):
                continue
            current_class = child['class'][0]
            # do comparison here
            if current_class == 'wprm-recipe-ingredient-amount':
                ingredient.amount = child.text
                # print("\tingredient amount: ", child.text)
            elif current_class == 'wprm-recipe-ingredient-unit':
                ingredient.unit = child.text
                # print("\tingredient unit: ", child.text)
            elif current_class == 'wprm-recipe-ingredient-name':
                ingredient.name = child.text
                # print("\tingredient name: ", child.text)
        Recipe.ingredients.append(ingredient)


def get_recipe_contents(soup, recipe):
    get_recipe_ingredients(soup, recipe)
    get_recipe_instructions(soup, recipe)
    get_recipe_name(soup, recipe)
    get_recipe_time(soup, recipe)
    get_recipe_servings(soup, recipe)
    get_recipe_image(soup, recipe)


def validate_recipe(recipe):
    if recipe.ingredients == []:
        return False
    if recipe.instructions == []:
        return False
    if recipe.name == "n/a":
        return False
    return True


def write_recipe_to_file(fileName, recipe):
    with open(fileName, 'a', encoding="utf-8") as f:
        f.write("name: ")
        f.write(recipe.name)
        f.write("\nurl: ")
        f.write(recipe.url)
        f.write("\nimg_url: ")
        f.write(recipe.img_url)
        f.write("\ncategory: ")
        f.write(recipe.category)
        f.write("\nprep_time: ")
        f.write(recipe.prep_time)
        f.write("\ncook_time: ")
        f.write(recipe.cook_time)
        f.write("\nnum_servings: ")
        f.write(recipe.num_servings)
        f.write("\ningredients:")
        for ingredient in recipe.ingredients:
            f.write("\n\tname: ")
            f.write(ingredient.name)
            f.write("\n\tamount: ")
            f.write(ingredient.amount)
            f.write("\n\tunit: ")
            f.write(ingredient.unit)
        f.write("\n")
        i = 0
        for instruction in recipe.instructions:
            f.write("step ")
            f.write(str(i))
            f.write(":\n")
            f.write(instruction)
            f.write("\n")
            i = i + 1
        f.write("\n---\n")
        print("wrote ", recipe.name)


def create_url_list_from_citemap():
    url_list = []
    website = 'https://www.budgetbytes.com/post-sitemap1.xml'
    website2 = 'https://www.budgetbytes.com/post-sitemap2.xml'
    res1 = requests.get(website)
    res2 = requests.get(website2)
    soup1 = bs4.BeautifulSoup(res1.text, "html.parser")
    soup2 = bs4.BeautifulSoup(res2.text, "html.parser")
    urls1 = soup1.select('url')
    urls2 = soup2.select('url')
    with open("budgetbytes-urls.txt", "w") as f:
        for url in urls1:
            f.write(url.loc.text)
            url_list.append(url.loc.text)
            f.write("\n")
        for url in urls2:
            f.write(url.loc.text)
            url_list.append(url.loc.text)
            f.write("\n")
    print("created budgetbytes-urls.txt from sitemap")
    return url_list


def download_all_html():
    with open("budgetbytes-urls.txt", "r") as f:
        i = 1
        for line in f:
            name = "BudgetBytes\\" + "BudgetBytes" + str(i) + ".html"
            if path.exists(name):
                continue
            res = requests.get(line.lstrip())
            with open(name, "w", encoding="utf-8") as f:
                f.write(res.text)
                print("wrote ", name)
            i = i + 1


def read_budgetbytes_html(filename, url_list):
    fi = "BudgetBytes\\" + filename
    with open(fi, "r", encoding="utf-8") as f:
        html_string = f.read()
        soup = bs4.BeautifulSoup(html_string, 'html.parser')
        # create new recipe object
        recipe = Recipe()
        # fill its contents
        get_recipe_contents(soup, recipe)
        # get number
        num_ls = re.findall('\d', filename)
        num = int(num_ls[0])
        # increment it by on
        num = num - 1
        # set this to the proper thing
        recipe.url = url_list[num]
        if validate_recipe(recipe):
            # write recipe to file
            print("writing", filename)
            write_recipe_to_file("recipes.dat", recipe)
        else:
            print(".....skipping ", filename)


# MAIN
url_list = create_url_list_from_citemap()
download_all_html()
with open("recipes.dat", "w") as f:
    pass
for i in range(len(url_list) - 1):
    name = "BudgetBytes" + str(i + 1) + ".html"
    read_budgetbytes_html(name, url_list)
print("ta-da!")
