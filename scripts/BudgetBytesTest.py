# Created by Matthew Majewski (BigBadBoris) on 11/13/2019
# This script is made to web-scrape recipes from the website
# budgetbytes.com. The html is nicely organized into distinct 
# classes, which make it easy to separate ingredient names, 
# amounts, and units of each amount. 

# To figure out how to parse the html tree of a website to extract the
# information you want, I recomend using the "inspect element" feature
# built-in to firefox. To use this, right-click on the relevant
# text/region on the page, and the firefox debugger will pop up,
# high-lighting the relevant portion of the html. Inside the debugger,
# you can also mouse over a portion of the html, and the relevant
# region in the webpage will be high-lighted as well.

import bs4 
import requests 

webpage = 'https://www.budgetbytes.com/sweet-potato-biscuits/'

# fetch webpage
res = requests.get(webpage)
html_string = res.text

soup = bs4.BeautifulSoup(html_string, 'html.parser')
top_elements = soup.select('.wprm-recipe-ingredient')

for top_element in top_elements:
    children = top_element.children
    for child in children:
        if isinstance(child, str):
            continue
        current_class = child['class'][0]
        # do comparison here
        if current_class == 'wprm-recipe-ingredient-amount':
            print("\tingredient amount: ", child.text)
        elif current_class == 'wprm-recipe-ingredient-unit':
            print("\tingredient unit: ", child.text)
        elif current_class == 'wprm-recipe-ingredient-name':
            print("\tingredient name: ", child.text)
    print()


class Recipe:
    def __init__(self):
        self.name = "n/a"
        self.category = "n/a"
        self.prep_time = "n/a"
        self.cook_time = "n/a"
        self.total_time = "n/a"
        self.num_servings = "n/a"
        self.ingredients = []
        self.instructions = ""


class Ingredient:
    def __init__(self):
        self.amount = "n/a"
        self.unit = "n/a"
        self.name = "n/a"
