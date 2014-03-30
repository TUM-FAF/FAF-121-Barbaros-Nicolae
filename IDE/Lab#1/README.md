# IDE Laboratory Work #1

### Title: Command Line Interface. CLI Editor. Setting Server environment. Version Control Systems.

### Tasks with points:

In order to do other tasks, I had to create my own server, for each I used the Ubuntu VM (Virtual Machine).

   - #####Create your own server (ex. virtual machine)

    ```sh
    sudo apt-get install openssh-server     #Install an OpenSSH server
    sudo service ssh start                  #Start OpenSSH server
    ```


### Mandatory Tasks
   - **Connect to a remote server via SSH**

  I started my server and for connecting to it I will run the following commands in Git Bash

  ```sh
  ssh username@ip  #username, ip - VM ip 
  ```

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

### Tasks with points

#####Connect to server using public key.
   
To connect to the server first of all I have to create a public key by writing the following command

`ssh-keygen -t rsa` 

Next step is to authorize public key on the server by writing this command

`cat ~/.ssh/id_rsa.pub | ssh user@ip "cat - >> ~/.ssh/authorized_keys"`

- #####Create 2 more branches with at least one unique committed file per branch**

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

  
- #####Reset a branch to previous commit, reset a branch to some specific commit**

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

- #####Make your CLI text editor to highlight code.
   
    This one was really simple because  VIM has a built-in syntax highlighter, my job was to open google and to find the command
    
    `:syntax on/off` 
    
    And the result is this :

![EditorHighLight](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%231/EditorHighLight.png)

- #####Create a VCS alias.

  Aliases are very useful especially when we have long commands. Creating an alias we can do by writing the following command

  `git config --global alias.nico 'branche newbranch'  # creating a global alias called nico`

  How do this work? Simple, to create a new branch we must write 
  
  `git branche newbranch'

  With the help of created alias, now, we can write 
  
  `git nico # which is similar to git branche newbranch `

- #####Create a VCS hook 

   _ToDo_

- #####Master any CLI editor (VIM). Learn 10 commands' sets**
       
    - `o` - Begin a new line below the cursor and insert text

    - `all` - Begin a new line above the cursor and insert text

    - `ggguG` - lowercase all text

    - `?word` - search word from bottom to top

    - `/word` - search word from top to bottom

    - `:%s/$/word/g` - add word at the end of each line

    - `:%s/word1/word2/g` - replace word1  by word2 in all  the file

    - `:g/word/d`  - delete all lines containing word

    - `Ctrl+n ,Ctrl+p` - Auto-complete

    - `:Sex` - Split window and open integrated file explorer

    - `:args` - list files

    - `:ls` - list buffers


- #####Create a VCS merge conflict and solve it**
   
 My conflict will consist of the same file in two branches, but with conflicting changes in the same location of the file.

```sh
git checkout otherbranch   #switch to otherbranch branch
vim file.txt       #open file in vim
i                  #insert
This line was inserted from the 'otherranch' branch   #text to be inserted
:wq   #save, exit
cat file.txt  #show content from file.txt
git add file.txt 
git commit -m 'file.txt changed in the otherbranch branch'
```
Here we start the conflict

```sh
git checkout test   #switch to test branch
vim file.txt 
i
This line was inserted from the 'test' branch
:wq
cat file.txt
git add file.txt
git commit -m 'file.txt changed in the test branch

git checkout otherbranch   #switched to branch 'otherbranch'
git merge test    #Auto-merging file.txt 
```
Here comes the conflict message. Merge conflict in Readme. Automatic merge failed; fix conflicts and the commit the resutls

```sh
git status  # tells where are the conflicts

git commit
U   file.txt
fatal: 'commit' is not possible because you have unmerged files.
Please, fix them up in the work tree, and then use 'git add/rm ' as
appropriate to mark resolution and make a commit, or use 'git commit -a'.

```
Let's investigate. Git is forcing us to resolve the conflicts
```sh
cat file.txt

Git inserted:
<<<<<<< HEAD
to mark the beginning of the conflicting section from the master branch (where the HEAD reference is pointing).
Git also inserted:
=======
to mark the ending of the conflicting section from the master branch, and inserted:
>>>>>>> test
to mark the end of the conflicting section from the test branch.
```
Solve Conflicts
```sh
vim file.txt  
choose what we want to have in the conflicting section and saveoru updated version
git commit -a -m 'file.txt conflict solved'
```
![Picture](https://raw.githubusercontent.com/TUM-FAF/FAF-121-Barbaros-Nicolae/master/IDE/Lab%231/Conflict%20Resolved.png)
#### Conclusion:
 
 This laboratory work introduced me to a total new area of knowledge since all this was new for me .More than this, I am not a huge fun of console writing but with a little bit of hard working I managed to do more than 50 % of the tasks with points. Also this lab improved my skill for google searching.
 In the end I want to say, that I kind of liked it. :)
