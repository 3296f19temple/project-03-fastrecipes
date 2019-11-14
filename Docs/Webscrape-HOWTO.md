# HOW TO WEBSCRAPE USING PYTHON

## Requirements 

- `Requests` module (for fetching html from the web). 
  - download using pip:  `pip install requests`
- `Beautiful Soup` module (for parsing html)
  - download using pip: `pip install bs4`
  
## Using requests to fetch a webpage
```Python
import requests

webpage = "https://www.google.com"
res = requests.get(webpage)
html_string = res.text

```
## Useful bs4 commands parse html 

| method                     | match                                                             |
|----------------------------|-------------------------------------------------------------------|
| soup.select('div')         | All elements named `<div>`                                        |
| soup.select('#author')     | The element with an `id` attribute of `author`                    |
| soup.select('.notice')     | All elements that use CSS `class` attr named `notice`             |
| soup.select('div span')    | All elements named `<span>` that are within element named `<div>` |
| soup.select('input[name]') | All elements named `<input>` that have a `name` attr w/ any value |

## Example HTML Parsing

```Python

```
