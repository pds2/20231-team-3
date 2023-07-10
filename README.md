# Team 3 | Library System  

<p>The terminal-based library program is a command-line application for managing library operations. It allows tasks such as adding books, searching, checking out, and returning books, as well as managing user accounts. It provides an efficient interface for librarians and patrons to interact with the library system.</p>

![Frame 3](https://github.com/pds2/20231-team-3/assets/66080424/7c4acf26-bac7-455e-9d8e-6f37d27dee24)

<h3>User Stories</h3>
<ul>
  <li>As a very eclectic reader, I want to be able to consult the books I want to rent by categories, so that I don't have to read description by description of the books until I find a book that I like.</li>
  <li>As someone who loves synopses, I want to be able to read the description of books before I choose them, so I would have an idea of what they are about before I read them.</li>
  <li>As a warehouse librarian, I want the system to be able to register new books and remove any books that I need, such as the availability query, so that I no longer need to use analogue or manual methods to do so.</li>
  <li>As an attendant librarian, I want to be able to consult a book in a simple graphical interface, such as changing its availability status, quantity, etc., so that a rented book will not be available in the system.</li>
  <li>As a manager of a library system, I want to be able to know who rented a book, what time, when it will have to be returned, contact number, address and fine, if any, all through a graphical interface as well, because that way I can have control of the integrity of books in general and for security purposes as well.</li>
  <li>As an executive director of the project, I want the system to have a login screen, where given a specific login this user has specific permissions and rights, so that it is impossible for a user who wants to rent a book not to be able to register or delete a book for example, then messing with the system.</li>
</ul>

<h3>Participants</h3>
<ul>
  <li>Lucas Rezende</li>
  <li>Lucas Wiermann</li>
  <li>Mateus Ryan</li>
  <li>Victória Reis</li>
  <li>Pedro Alexandria</li>
</ul>

# :computer: Environment Setup
In order to set your environment up to run the code here, first install all requirements.
Obs: Use the command consistent with your operating system, the examples given were done in ubuntu and arch

### Linux Setup

Ubuntu:
```shell
sudo apt-get install sqlite3 libsqlite3-dev
```
Arch:
```shell
sudo pacman -S sqlite
```

Then, with this library installed and making sure that the C++ dependencies are also on your computer, download the .zip of this project.
In your terminal, access the project folder, after that type:
```shell
make
```

After that, the program will be compiled in a file called "biblioteca". Then, type:
```shell
./bin/biblioteca
```
That way you can use the program and its features.

### MacOS Setup
<p>macOS:</p>
<p>Install Xcode: Download and install Xcode, which includes the Clang compiler and other tools required for C++ development. Xcode is available from the App Store or the Apple website.</p>

Install Homebrew:
```shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Install SQLite3:
```shell
brew install sqlite3
```
Download the Project: Download the .zip file of the project and extract it to a directory of your choice.

Compiling and Running the Program:
```shell
g++ -o biblioteca main.cpp -lsqlite3
```
```shell
./bin/biblioteca
```
That way you can use the program and its features.

<h3>Navegating the program</h3>
<ul>
  <li>Once the program starts, you will be presented with a menu that offers a variety of options to perform different tasks. These tasks include adding books, searching for specific books, renting books, returning books, and managing user accounts, among others.
To interact with the program, simply use the corresponding keys or input commands for the menu options that correspond to the action you want to take. For example, if you want to add a book, you would select the option associated with adding books.
As you navigate through the program, carefully follow the instructions that are displayed on the screen. These instructions will guide you on how to input data, make selections, and complete various operations within the program.
By following the menu options and instructions, you can effectively interact with the program and perform the desired actions efficiently.</li>
</ul>
