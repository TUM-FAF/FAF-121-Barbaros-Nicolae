
###### student gr. FAF-121: Barbaroș Nicolae
#

## Unity App development
  - **Unity 3D**

### Prerequisites:
  - IDE: MonoDevelop
  - Language:C#

### Mandatory 
  - Create and application that will learn you the basic of debugging and testing using MonoDeveloper and Unity3D

### Tasks With Points:
  - Debug an application. At some point you'll have bugs (ex. null pointer exception). Set breakpoints and/or watchers. Find out buggy variables. (1pt)
  - Create a class that will test your application (2pt)


## Screenshots
App on Start
![Screenshot1](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%234/pictures/Screenshot_5.png)
It's a simple app with4 buttons. 

First button is for debugging types, so we have 3 types of debug Log, Error, Warn 
It will show the type of debugging by condition, so if we comment 2 out of 3 defines and let only the level_Log our event will take this condition

            [System.Diagnostics.Conditional("DEBUG_LEVEL_LOG")]	
 
...and the output will be 

            "This is a log with formatting: 12.1"


The next 3 buttons are for tests.

A look into debugger
 ![Screenshot1](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%234/pictures/Screenshot_1.png)
 
 I have a class in a class also a structure in that class so ass you can see just by holding the cursor on the object class you can get into the class and see the variables. 
 ![Screenshot2](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%234/pictures/Screenshot_2.png)
 
Even more!you can directly edit the variables from this spot
 ![Screenshot3](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%234/pictures/Screenshot_3.png)
 
or from debugger
 ![Screenshot4](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%234/pictures/Screenshot_4.png)
 
## Development

Testing and debugging is a very powerful "weapon" for Unity.  By writing this class I was able to test with help of assert which verifies your input in the Inspector (Unity), for example assert in a string is to be a string not a null, or if a given number or situation in your app is as you expected.

Hopefully I will have enough points from previous labs. For this one I am out of ideas)
