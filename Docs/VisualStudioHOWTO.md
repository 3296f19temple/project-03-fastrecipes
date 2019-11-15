# Setting Up Visual Studio


## Adding Source and Library files to Project
1. Navigate to the solution file located at
   `FastRecipes\FastRecipes.sln`
2. Click on solution file and open it in Visual Studio
3. Open up the `Solution Explorer` tab (you can find it in `View`)
4. On the top of the solution explorer (where all the icons
   are), click on the `show all files` button (looks like three
   files).
5. Nagivate to the Source files.
6. high-light all the `.cpp` and `.h` files, right-click, and
   select `Include in Project`.
7. Do the same thing you did in step 6 for all of the `.h` and
   `.dll` files in `x64\Debug`, `x64\Debug\include`, and
   `x64\Debug\lib` folders.
   
## Setting Up Path

1. Right-Click on the `FastRecipes` solution in the solution
   explorer. Then click on `properties` (at the very bottom).
2. This will open up the properties view. Navigate to the
   `Linker` section on the left, and click on the sub-heading
   `General` (use the arrow to the left of linker to show
   sub-headings).
4. Enter the following into the **"Additional Library
   Directories"** section: `$(SolutionDir)x64\Debug\lib\`
5. Then go to the `C/C++` section, and click on the `General`
   sub-section.
6. Enter the following into the **"Additional Include
   Directories"** folder: `$(SolutionDir)x64\Debug\include\`
7. Ok, most annoying part. navigate back to the `Input`
   sub-heading in the `Linker` section. 
8. You will need to enter **ALL** of the following into the
   **Additional Dependencies** section:
   - `libcrypto.lib;libssl.lib;mysqlcppconn.lib;mysqlcppcon8.lib;mysqlcppconn8-static.lib;mysqlcppconn-static.lib;`
