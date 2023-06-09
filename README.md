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

### Requirements
<ol>
  <li>C++ compiler</li>
  <li>SQLite3</li>
  <li>Git</li>
</ol>

# :computer: Environment Setup
To set up your environment and run the code, follow these steps:
<ol>
  <li>Clone this repository to your local machine.</li>
  <li>Navigate to the project directory on your system.</li>
</ol>

### Linux Setup

#### Ubuntu

<p>Install the required dependencies by running the following command:</p>

```shell
sudo apt-get install sqlite3 libsqlite3-dev
```

#### Arch

<p>Install the required dependencies by running the following command:</p>

```shell
sudo pacman -S sqlite
```

Once the dependencies are installed, open your terminal, navigate to the project folder, and run the following commands:

```shell
make
```

```shell
./bin/biblioteca
```

That way you can use the program and its features.

### MacOS Setup
#### MacOS
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

# :pencil2: System features
<ul>
  <li>Once the program starts, you will be presented with a menu that offers a variety of options to perform different tasks. These tasks include adding books, searching for specific books, renting books, returning books, and managing user accounts, among others.
To interact with the program, simply use the corresponding keys or input commands for the menu options that correspond to the action you want to take. For example, if you want to add a book, you would select the option associated with adding books.
As you navigate through the program, carefully follow the instructions that are displayed on the screen. These instructions will guide you on how to input data, make selections, and complete various operations within the program.
By following the menu options and instructions, you can effectively interact with the program and perform the desired actions efficiently.</li>
</ul>

### User features
<ul>
  <li>Book Borrowing: Customers can borrow books from the library as long as they have not reached the maximum book limit and the books are available.</li>
  <li>Book Return: Patrons can return borrowed books to the library when they are finished reading them.</li>
  <li>Book Ratings: Customers can rate the books they have read, providing a score from 0 to 5. The rating contributes to the library's book rating average.</li>
</ul>

### Librarian features
<ul>
  <li>Book Loan: The librarian can loan a book to a user. It checks that the book is available and that the user has not reached the maximum borrowed book limit. It then records loan information such as the lease date and return date.</li>

<li>Book Returns: The librarian can receive the return of a book borrowed by a user. It verifies that the book is associated with the user and updates the borrowing information, marking the book as available again.</li>
</ul>

### Administrator features
<ul>
  <li>Insert Book: The administrator can insert a new book in the library collection. It provides the book information such as title, author, genre, etc., and the book is added to the holding database.</li>

  <li>Remove Book: The administrator can remove a book from the library's collection. Before removing the book, the administrator checks if the book is currently on loan. If the book is on loan, an exception is thrown to say that the book cannot be removed. Otherwise, the book is deleted from the holdings database.</li>

  <li>Load Books: Administrator can load a list of books from a file. Books are read from the archive, information is extracted, and each book is added to the holding database.</li>
</ul>

### OBS: The part below is only visual, because our group could not connect the frontend and the backend, but feel free to see the webpage working!

# Tutorial de Instalação da Biblioteca Crow em C++ :books: :hammer:
### Instalação da biblioteca Crow :inbox_tray:

<ul>
  <li>Abra o terminal ou prompt de comando no seu sistema operacional.</li>
  <li>Certifique-se de ter o CMake instalado. Você pode verificar digitando cmake --version no terminal. Se não estiver instalado, você pode baixá-lo em: https://cmake.org/download/.</li>
  <li>Faça o download da biblioteca Crow. Você pode obtê-la no repositório oficial do Crow no GitHub: ipkn/crow.</li>
  <li>Descompacte o arquivo que você baixou e acesse o diretório raiz do Crow.</li>
  <li>Abra o terminal ou prompt de comando no seu sistema operacional.</li>
</ul>  

### Compilação e Construção do Projeto :wrench:

<ul>
  <li>Dentro do diretório raiz do Crow, crie um diretório chamado "build" (ou qualquer outro nome que você preferir) para realizar a construção.</li>
  <li>Acesse o diretório "build" que você acabou de criar.</li>
  <li>Execute o comando cmake .. para gerar os arquivos de construção do CMake.</li>
  <li>Em seguida, execute o comando make (ou mingw32-make se estiver usando o MinGW no Windows) para compilar o projeto..</li>
</ul>  

### Executando o Arquivo Crow :arrow_forward:

<ul>
  <li>No terminal, Digite o seguinte comando no terminal: g++ frontend/example.cpp.</li>
  <li>Após a conclusão da compilação, você terá um arquivo executável na pasta raíz, ou seja, dentro de pasta nenhuma :) . Neste caso, o arquivo será chamado a.out.</li>
  <li>Depois digite o seguinte comando no terminal: ./a.out e assim você vai começar a estanciar o site.</li>
  <li>O Crow usará um determinado endereço IP e porta para hospedar seu aplicativo da web. Por padrão, o endereço IP é "localhost" e a porta é "8080".</li>
  <li>No terminal, será exibido um link que você pode clicar para acessar o aplicativo em seu navegador.</li>
  <li>Clique no link exibido no terminal para abrir a página no seu navegador padrão.</li>
</ul> 

### Parando de Hospedar a Página :stop_button:

<ul>
  <li>Para parar de hospedar a página, volte ao terminal onde o Crow está sendo executado.</li>
  <li>Pressione Control + C no terminal para interromper a execução do Crow.</li>
  <li>Agora você instalou a biblioteca Crow, compilou o arquivo example.cpp localizado na pasta frontend, e executou o aplicativo usando o Crow em C++. Acesse a página clicando no link exibido no terminal e pare a execução pressionando Control + C no terminal.</li>
</ul> 

### Para ver as imagens do site 😙:

<ul>
  <li>Basta navegar até pasta frontend.</li>
  <li>E acessar a pasta frontend images.</li>
</ul> 
