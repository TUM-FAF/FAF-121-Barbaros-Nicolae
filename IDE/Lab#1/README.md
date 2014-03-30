# IDE Laboratory Work #1

### Title: Command Line Interface. CLI Editor. Setting Server environment. Version Control Systems.

### Tasks with points:
    In order to do other tasks, I had to create my own server, for each I used the Ubuntu VM (Virtual Machine).

   -**Create your own server (ex. virtual machine)

    ```sh
    sudo apt-get install openssh-server     #Install an OpenSSH server
    sudo service ssh start                  #Start OpenSSH server
    ```


#### Mandatory Tasks
   - **Connect to a remote server via SSH**

  I started my server and for connecting to it I will run the following commands in Git Bash

  ```sh
  ssh username@ip# username, ip - VM ip 

   - **Initialize a repository on server**
   
  `git init`   # initializing a local repository in the desired location
   - **Create a file in repository folder, write in your name, save and commit it**
  I am using vim for creating the text file and writing my name into it.

    ```sh
   mkdir Nico                    #create a folder
   vim name.txt                  #editor to create a text file
   i                             #insert some text
   Barbaros Nicolae              #name
   :wp                           #write and exit
   git add text.txt              #add the file to folder
   git commit -m "text file with my name"
   ```
 git@github.com:NicoBarbaros/IDE-labs.git
#### Tasks with points:

   - **Create 2 more branches with at least one unique committed file per branch**

   Commands:
  ```sh
  git init                     #initializing
  touch master.txt             #creates a file    
  git add master.txt           #adds file to master
  git commit -m  "commit to master branch"
  git branch otherbranch       #creates otherbranch
  git branch -a                #display branches and shows the one you are in now
  git chekout otherbranch      #switched to otherbranch
  touch otherbranch.txt        #creats another file
  git add otherbranch.txt      #adds this file on otherbranch
  git commit -m 'commit to otherbranch branch'
  ```
  By switching to otherbranch branch I will see that both of my files will be displayed (master.txt and otherbranch.txt) while if I am switching to the master only the master.txt will be displayed.

  
   - **Reset a branch to previous commit, reset a branch to some specific commit**

     - Reset a branch to previous commit:

       `git reset --hard HEAD`   - HEAD is the last commit ID in  current branch

     - Reset a branch to some specific commit:

       ```sh
       git log             #displays all commits, find here the commit to reset
       git reset --hard ID   #ID = commit ID
       ```
   - **Restore a reset branch back to its previous state**
      ```sh
      git reflog          #copy ID of the commit
      git reset --hard ID
      ```

  - **Make your CLI text editor to highlight code.
    This one was really simple because  VIM has a built-in syntax highlighter, my job was to open google and to find the command
    `:syntax on/off` 
    And the result is this :
    (ScreenShoot)

  -**Create a VCS alias.
  Aliases are very useful especially when we have long commands. Creating an alias we can do by writing the following command

  `git config --global alias.nico 'branche newbranch'  # creating a global alias called nico

  How do this work? Simple, to create a new branch we must write 
  `git branche newbranch'

  With the help of created alias, now, we can write 
  `git nico` # which is similar to git branche newbranch

   -**Create a VCS hook 
   _ToDo_

   - **Master any CLI editor (VIM). Learn 10 commands' sets**
       
       ** `o` - Begin a new line below the cursor and insert text
       ** `all` - Begin a new line above the cursor and insert text
       ** `ggguG` - lowercase all text
       ** `?word` - search _word_ from bottom to top
       ** `/word` - search _word_ from top to bottom
       ** `:%s/$/word/g` - add _word_ at the end of each line
       ** `:%s/word1/word2/g` - replace _word1_ by _word2_ in all the file
       ** `:g/word/d`  - delete all lines containing _word_
       ** `Ctrl+n ,Ctrl+p` - Auto-complete
       ** `:Sex` - Split window and open integrated file explorer
       ** `:args` - list files
       ** `:ls` - list buffers

   - **Create a VCS merge conflict and solve it**
   _ToDo_

     
#### Conclusion:
 
 This laboratory work introduced me to a total new area of knowledge since all this was new for me .More than this, I am not a huge fun of console writing but with a little bit of hard working I managed to do more than 50 % of the tasks with points. Also this lab improved my skill for google searching.
 In the end I want to say, that I kind of liked it. :)