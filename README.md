# Project Chess
 > Authors: [Matthew Cao](https://github.com/sidechara), [Erumise Iriafen](https://github.com/eiriafen), [Derek Lee](https://github.com/dcl28), [Anderson Wang](https://github.com/Anderson123g
)

Note: I re-uploaded the code for this project to my own public repository because it was originally privately owned by my university organization.

## Project Description
A traditional two-player chess game
 * [importance] The project in itself is interesting to us because we all enjoy playing chess. We want to recreate the game using code to deepen our understanding of both programming and chess. Through this project, we will also learn how to cooperate and work simultaneously on code using git to strengthen our team working skills in programming.
 * [languages/tools] C++ using bitboards or a type of graph/array data structure, SDL or another type of graphics library
 * [input/output] User interacts with GUI in a windowed screen, dragging chess pieces across to move them, clicking buttons in menus
 * [features] ~~Saving/loading,~~ undoing, player versus player, player versus ai
 
## User Interface Specification
### Navigation Diagram
This diagram represents the navigation between screens in the GUI
![Mind Maps (2)](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/d0c925db-111b-4827-b4d0-b1a29dfae974)
### Screen Layouts
![titleMockup](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/02a03ec3-53cb-457d-b036-dd489ba961f5)
![player-CPUMockup](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/b2dc5025-4660-4400-93d1-7802061c5321)
![boardSelectMockup](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/beadc288-f410-4ad8-b111-b15c51855a9f)
![gamemodeMockup](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/c791133c-e785-458a-870a-35164b406325)
![gameMockup](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/c0bf1850-634b-41ab-9d0b-47e110242182)
## Class Diagram
This diagram represents the relations between classes.
The low levels include Piece and Square along with the enumerations while the high levels include the printer class and Game
![Chess UML drawio](https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/0608bfad-7b20-4038-9944-0e9741bf8c69)

The implementation for the game screen and its associated information displays, which was originally planned to be in Screens.cpp, was outsourced to two new classes, GameScreen.cpp and DisplayInfo.cpp. This is an application of the single-responsibility principle, which states that each class should only have one primary responsibility. This change allows Screens.cpp to focus on switching between screens, preventing it from becoming cluttered with too many miscellaneous member variables/functions.

Furthermore, the addition of these two classes represents the application of the Liskov substitution principle. Both derive from classes defined in the gtkmm UI interface, Gtk::Box and Gtk::DrawingArea respectively, and were intended to extend their abilities without interfering with the original functionality. The program in Screens.cpp can smoothly use GameScreen and DisplayInfo objects using Gtk::Widget pointers (an even more generic class) without creating errors.

The interface PlayerEngine was also removed, in line with the interface segregation principle. As the coding progressed, we realized that the human player would not need a makeMove() method, as the UI to allow the player to move pieces is already in place. Therefore, we removed the interface to prevent HumanPlayer from implementing methods that it would not use.

Functions were added to Square and PieceSet to expand their capabilities while maintaining the single responsibility principle, open closed principle, and dependency inversion principle. The SRP and OCP are maintained through the functions' simplicity and ease of building upon while the DIP is maintained as the functions rely only upon interface and not implementation.

By incorporating color enumerations into the Piece class, I used the Single Responsibility Principle (SRP). This ensures that only the Piece class is responsible for managing the color of the piece and not by other classes.

I used the Open/Closed Principle by adding helper functions to the Piece class to help with the extension of future piece types. Although at first it may seem like I am violating the OCP by modifying the Piece class, these changes are necessary to allow for easier and more efficient extensions. For example, if we wanted to add new piece types with different valid moves in future, the added functions make it easier to create and implement the new types, hence making the Piece class more open to extension.

 ## Screenshots
<img width="1278" alt="menu" src="https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/994372cb-706e-4f92-8176-a47e6fce8a6c">
<img width="1277" alt="player" src="https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/bd93338e-dafb-45e1-83bf-9462fc51b840">
<img width="1276" alt="options" src="https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/27ef17c9-6101-4ee7-86b0-1bdcfcc745e5">
<img width="1276" alt="game" src="https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/af0fe806-baa8-4fd5-bc46-f221798af9a5">
<img width="1279" alt="quit" src="https://github.com/cs100/final-project-zcao051-dlee502-awang245-eiria001/assets/165974058/3235dbfe-3d13-4958-a06b-fad046655559">

 ## Installation/Usage
Download the source code (header and source folders). To install gtkmm 4.0 (the GUI toolkit used for this project), follow the instructions for your operating system here https://www.gtkmm.org/en/download.html. The installation instructions for Windows are located on this page: https://wiki.gnome.org/Projects/gtkmm/MSWindows Note that you must first have installed MSYS2 for Windows. Then, open your preferred shell and enter the commands on the linked page to install the compiler, gtkmm4 libs, and pkg-config.

Once gtkmm-4.0 has been installed, navigate to the folder containing the source files, and compile the project using the following (note that the CMakeLists.txt file is only for compiling the tests):
```
g++ chess.cpp Screens.cpp GameScreen.cpp DisplayInfo.cpp Board.cpp PieceSet.cpp Piece.cpp Square.cpp King.cpp Queen.cpp Rook.cpp Bishop.cpp Knight.cpp Pawn.cpp Game.cpp Move.cpp ComputerPlayer.cpp resources.c -o chess `pkg-config --cflags --libs gtkmm-4.0`
```

This should have created an executable in the same folder. Move the executable to the folder labeled “chessBin” and run it to launch the game.
 ## Testing
Tested using the googletest submodule which can be run using `cmake .` and `make`
