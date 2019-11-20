import bs4, requests

website = 'https://www.budgetbytes.com/post-sitemap1.xml'
website2 = 'https://www.budgetbytes.com/post-sitemap2.xml'

res1 = requests.get(website)
res2 = requests.get(website2)
soup1 = bs4.BeautifulSoup(res1.text, "html.parser")
soup2 = bs4.BeautifulSoup(res2.text, "html.parser")
urls1 = soup.select('url')
urls2 = soup2.select('url')
with open("budgetbytes-urls.txt", "w") as f:
    for url in urls1:
        f.write(url.loc.text)
        f.write("\n")
    for url in urls2:
        f.write(url.loc.text)
        f.write("\n")
print('done!')
