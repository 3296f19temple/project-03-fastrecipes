function home(id) {
    var content = `
    <br/>    
    <div id="insertArea">
        <table>
            <tr>
                <td>Ingredient</td>
                <td><input type="text"  id="ingredient" /></td>
                <td id="userEmailError" class="error"></td> 
            </tr>
            <tr>
                <td><button onclick="search()">Search</button></td>
                <td id="recordError" class="error"></td>
                <td></td>
            </tr>
        </table>
    </div>
    `;
    document.getElementById(id).innerHTML = content;
}
