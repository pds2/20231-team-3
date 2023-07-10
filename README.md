<h1>Team 3</h1>

<p>The terminal-based library program is a command-line application for managing library operations. It allows tasks such as adding books, searching, checking out, and returning books, as well as managing user accounts. It provides an efficient interface for librarians and patrons to interact with the library system.</p>

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

# Environment Setup
In order to set your environment up to run the code here, first install all requirements.
Obs: Use the command consistent with your operating system, the examples given were done in ubuntu and arch

Ubuntu:
```shell
sudo apt-get install sqlite3 libsqlite3-dev
```
Arch:
```shell
sudo pacman -S sqlite
```

Then, with this library installed and making sure that the C++ dependencies are also on your computer, download the .zip of this project.
