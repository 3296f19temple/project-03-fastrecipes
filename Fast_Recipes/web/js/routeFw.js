// Sally's JS naming convention: every JS file shall be named the same as the 
// single function or object that is defined within the JS file. This helps you 
// organize and find your code.

"use strict";

function routeFw(params) {

    var fw = {}; // creating and adorning this object to be passed back to the HTML page.

    // Providing a parameter object instead of a parameter list is good software design. 
    // It makes the call to the function be more self documenting and order of parameters 
    // does not matter. 

    // Here's how you can either accept a preference or set a default value in one line of code. 
    // For example, if the params object has a startingPath property, you use that, otherwise, you set it to /home.
    var startingPath = params.startingPath || '/home';
    var contentId = params.contentId || "view";

    if (!params.routeArray || params.routeArray[0]) {
        alert("parameter object must specify array 'routeArray' with at least one element");
        return; 
    }

    // Declare a (private) array to store our routes.
    var routes = params.routeArray;

    // private function that will be called whenever a link is clicked (or href changed)
    function router() { // private function

        console.log("location.hash (the link that was clicked) is " + location.hash);
        // prints something like #/home

        // remove leading # from string that holds the clicked link
        var path = location.hash.slice(1) || '/';
        console.log('path (with no #) is ' + path);
        // prints something like /home

        // Use the url like an index (JS associative array notation) to find 
        // the desired content and place it in the content area.
        // If a link is clicked for which a route was never set, give error message.
        if (!routes[path]) {
            document.getElementById(contentId).innerHTML = "Error: path '" + path +
                    "' was never added to the routing.";
        } else {
            routes[path](contentId);
        }
    }

    fw.printRoutes = function () {
        console.log("routes will be printed on the next line ");

        // if you console.log an object (by itself), you'll be able to see all of it's 
        // contents (don't precede with character string and concatenate).
        console.log(routes);
    };

    // Whenever a link is clicked (or window.location.hash changes), 
    // invoke function router (defined below).
    window.addEventListener('hashchange', router);

    // Make sure there's always a change upon refreshing the page. 
    // This is so you never see empty content upon page refresh.
    window.location.hash = "/xxx";

    // content for when page is first rendered.
    window.location.hash = startingPath;

    return fw;
}