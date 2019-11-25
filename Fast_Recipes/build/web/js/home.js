function home(id) {
    var content = `
      <p>
        Welcome to Fast Recipes...
        To search for a recipe, click on the 'Search' link at the top right of 
        of this page. Once on the search page, type in an ingredient that you'd 
        like to cook with and press search. We will them return a recipe 
        containing that ingredient for you. 
      </p>
      <p>
        Thank you for using Fast Recipes. Happy cooking!
      </p>
      <image src = "icons/blackLogo.png" id = "home_logo" />
    `;
    document.getElementById(id).innerHTML = content;
}
