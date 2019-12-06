var TxtRotate = function(el, toRotate, period) {
  this.toRotate = toRotate;
  this.el = el;
  this.loopNum = 0;
  this.period = parseInt(period, 10) || 2000;
  this.txt = '';
  this.tick();
  this.isDeleting = false;
};

TxtRotate.prototype.tick = function() {
  var i = this.loopNum % this.toRotate.length;
  var fullTxt = this.toRotate[i];

  if (this.isDeleting) {
    this.txt = fullTxt.substring(0, this.txt.length - 1);
  } else {
    this.txt = fullTxt.substring(0, this.txt.length + 1);
  }

  this.el.innerHTML = '<span class="wrap">'+this.txt+'</span>';

  var that = this;
  var delta = 300 - Math.random() * 100;

  if (this.isDeleting) { delta /= 2; }

  if (!this.isDeleting && this.txt === fullTxt) {
    delta = this.period;
    this.isDeleting = true;
  } else if (this.isDeleting && this.txt === '') {
    this.isDeleting = false;
    this.loopNum++;
    delta = 500;
  }

  setTimeout(function() {
    that.tick();
  }, delta);
};

window.onload = function() {
  var elements = document.getElementsByClassName('txt-rotate');
  for (var i=0; i<elements.length; i++) {
    var toRotate = elements[i].getAttribute('data-rotate');
    var period = elements[i].getAttribute('data-period');
    if (toRotate) {
      new TxtRotate(elements[i], JSON.parse(toRotate), period);
    }
  }
  // INJECT CSS
  var css = document.createElement("style");
  css.type = "text/css";
  css.innerHTML = ".txt-rotate > .wrap { border-right: 0.08em solid #666 }";
  document.body.appendChild(css);
};
//end of fancy text

var search = {};

function my$(id) {
    return document.getElementById(id);
}

(function () { 
    search.findRecipeUI = function(id) {
        console.log(id);
        var contentDOM = document.getElementById(id);
        console.log(contentDOM);
        var content = `
            <div class='search'>
                <br/>
                Recipe Name <input type="text" id="findIngredient"/>
                &nbsp;
                <input type="button" value="Search" onclick="search.findRecipeByIngredient('findIngredient','msgArea')"/>
                <br/><br/>
                <div id="msgArea"></div> 
                
            </div>
            <image src = "icons/blackLogo.png" id = "home_logo" />
        `;
        contentDOM.innerHTML = content;
    };

    search.findRecipeByIngredient = function(inputIngredient, id) {
        var targetDOM = document.getElementById(id);
        targetDOM.innerHTML = "";

        var desiredName = escape(document.getElementById(inputIngredient).value);

        // the JS escape function cleans input so it can be used as a URL paramenter
        var myUrl = "WebAPIs/getRecipeByIngredientAPI.jsp?recipeName=" + desiredName;

        ajax({
            url: myUrl,
            successFn: success,
            errorId: id
        });


            function success(obj) {

                // var obj = JSON.parse(hreq.responseText); // this already done by function ajax...
                console.log(obj);
                if (!obj) {
                    targetDOM.innerHTML += "search.findRecipeByIngredient (success private fn): Http Request (from AJAX call) did not parse to an object.";
                    return;
                }

                if (obj.dbError.length > 0) {
                    targetDOM.innerHTML += "Database Error Encountered: " + obj.dbError;
                    return;
                } 

                else if (obj.RecipeList.length === 0 ) {
                    targetDOM.innerHTML = "No recipe with name " + desiredName + " was found.";
                } else {
                    var msg = "Found Recipe: " + obj.RecipeList[0].recipeName;
                    msg += "<br/> &nbsp; Category " +  obj.RecipeList[0].category;
                    msg += "<br/> &nbsp; Cook Time: " +  obj.RecipeList[0].cookTime;
                    msg += "<br/> &nbsp; Prep Time: " +  obj.RecipeList[0].prepTime;
                    msg += "<br/> &nbsp; Serving Count: " +  obj.RecipeList[0].servingCount;
                    msg += "<br/> <img src ='" +  obj.RecipeList[0].imageUrl + "'>";
                    targetDOM.innerHTML = msg;  
                }

            }
    };
}());