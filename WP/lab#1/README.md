# Windows Programming
###### student gr. FAF-121: Barbaroș Nicolae

# Topic: WIN32 API programming basics
## Intro
### Purpose
* Event-driven programming (message-oriented)
* API
* Windows applications development

### Additional Purposes
 * Additional taks done for fun

## Executed Tasks:
  - **Mandatory Tasks:**
    - Create a Windows application
    - Choose a _Programming Style Guideline_ that you'll follow
    - Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
    - Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
    - Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
  - **Tasks With Points:**
    - Make elements to fit window on resize **(1 pt)**
    _(hint: you can limit minimal window width and height)_
    - Make elements to interact or change other elements (1 pt for 2 different interactions) **(0-2 pt)** _(ex. on button click, change text element color or position)_
    - Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space **(1 pt)**
    - Write your own PSG (you can take existent one and modify it) and argue why it is better (for you) **(1 pt)**

## Theoretical Work:
 -**Programming language and PSG**
  * C++
  * [Geotechnical Software Services C++ Programming Style Guidelines](http://geosoft.no/development/cppstyle.html).
I am going to make some more additional changes to this PSG.

##PSG

I am going to make small changes into PSG 

**Comments**
```
    //Flag for checking
    int font = 1;

    //Declare Windows procedure
    LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
```

As you can see , my line of comment is written above the line of code , and between a line of code and a line of comment there is always a blank line left.A comment must start with an upper case.

**Case Blocks**

The case statement should have the following form:

```
   case do:
      {
      
      }
      
    break;
```

**Curly Braces**

Position of curly braces after any statement ,class.

```
   for (int i ; i < 0 ; i++ )
    {
  
    }
```  

I still need a lot of getting used to in order to write everything accoring to the PSG
