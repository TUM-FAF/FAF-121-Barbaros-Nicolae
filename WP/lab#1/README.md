# Windows Programming
###### student gr. FAF-121: Barbaroș Nicolae

# Topic: WIN32 API programming basics


## Intro:
  - **Purpose:**
    - Event-driven programming (message-oriented)
    - API
    - Windows Application development
  - **Additional Purposes:**
    - Additional taks done for fun


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
  - **Programming language and PSG:**
    - C++
    - [Geotechnical Software Services C++ Programming Style Guidelines](http://geosoft.no/development/cppstyle.html)


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

I still need a lot of , to get used to it in order to write everything according to the PSG

#The Application Creation Steps

For the development of this app I've read chapters from  Charlez Petzold's Windows Programming 5th edition.During the process of development I used MSDN and [Zetcode](http://www.zetcode.com/).

As my working enviroment I used CodeBlocks and started my works as a win32 GUI frame program.

So, here is the output of my application

![Result](https://raw.github.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/WP/lab%231/photo.png)

1. Text Editor on the left for inputing the message
2. List Box on the right for outputing the message
3. Send button for sending message from Tex Editor to the List Box
4. Delete button for deleting message from the List Box
5. Custom Font button for switching to a font created by me for message text from List Box
6. Default Font button for switching to the default system font for message text from List Box
7. Close button for clossing the application with a Custom Font created
8. There is an resize handler and a restriction for width/height on resizing 
9. There are 3 behaviors for Minimize/Maximize/Close button
10. Added 2 static text with created font and colors on a changed main window background color

##Conclusion

This laboratory work was a real enjoyable challenge for me since  Win32 API was quite new for me (I used it when I created the window for my OpenGL applications but then Win32 was not reason for me to find out what every line of code is doing). Working with the messages and manipulating the parameters helped me to create a window and some child elements . Also this experience gave me an image of Windows API, and how it is structured, even if it didn't covered any advanced topics.

The harder was and  still is for me to find how to change a button's background color .hence I will struggle more to find how to do it for lab#2 .

As for result I wanted to be something colorful and I think my goal was achived.

