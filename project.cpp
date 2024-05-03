#include <iostream> 
#include<fstream> 
#include<string> 
#include<Windows.h>
 #include<conio.h>
 using namespace std; 
 
#define MAZE_WIDTH  83 
#define  MAZE_HEIGHT 30 
 
char car = 'C';
 int CarX = 2; 
int CarY = 1; 
char Level; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition; 
// Function to move the cursor at the desired x and y location given in the parameters
 void gotoxy(int x, int y) { 
 	CursorPosition.X = x; 
 	CursorPosition.Y = y; 
 	SetConsoleCursorPosition(console, CursorPosition); 
} 
 
// Function to whether there is a character present at the location x and y given in the parameters
 char getCharAtXY(int x, int y) { 
 	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
if (hConsole == INVALID_HANDLE_VALUE) { 
return '\0'; 
}
CONSOLE_SCREEN_BUFFER_INFO csbi; 
if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) { 
 	 	return '\0'; 
 	} 
 	COORD coord = { 
         static_cast<SHORT>(x),
         static_cast<SHORT>(y) }; 
 
 	// Ensure the coordinates are within bounds  
	if (coord.X < 0 || coord.X >= csbi.dwSize.X || coord.Y < 0 || coord.Y >= csbi.dwSize.Y) { 
 	 	return '\0'; 
 	} 
 	char buffer = '\0'; 
 	DWORD bytesRead; 
 	if (!ReadConsoleOutputCharacterA(hConsole, &buffer, 1, coord, &bytesRead)) {  
	 	cout << "Error reading console output." << endl;  	 	
                 return '\0';  
        // Return null character in case of an error or no character present 
 	} 
 	return buffer; 
} 
 
class Obstacle {
      public: 
 	int x;  	
        int y;  	
        char obs; 
 	Obstacle() { 
 	x = 0; 
        y = 0; 
        obs = ' '; 
}
Obstacle(int x, int y, char obs) { 
 	this->x = x;  	 
	this->y = y;  	 
	this->obs = obs; 
 	} 
}; 
  
 
class Queue{ public: 
 	Obstacle* queueArray;  
	int queueSize;  
	int front;  
	int rear;  	
         int numItems;  
	Queue(int s) 
 	{ 
 	 	queueArray = new Obstacle[s]; 
 	 	queueSize = s;  
	 	front = -1;  	 	
                rear = -1;  	
             	numItems = 0; 
 	} 

 
 	bool isFull(){ 
            if (numItems == queueSize) 
	 	return true; 
            else 
	 	return false; 
} 
 	void enqueue(Obstacle obs) {  
	 	if (isFull())  	 	 	
                    cout << "The queue is full.\n"; 
 	 	else { 
 	 	 	rear = (rear + 1);  	 	 
                 	queueArray[rear] = obs; 
 	 	 	numItems++; 
 	 	} 
 	} 
 
 	Obstacle dequeue() {  	 
	if (isEmpty())  	
 	 	cout << "The queue is empty.\n"; 
 	 	else { 
 	 	 	front = (front + 1);  	 	
                 	return queueArray[front]; 
 	 	} 
 	} 
 
 bool isEmpty() {  
     return front==-1; 
 	} 
void setobstaclelocation_and_generate(int n,int X,int Y,char ch) {  
	for (int i = 0; i < n; i++){  
	int x = rand() % X; 
        int y = rand() % Y; 
 	char obst = '!';  	
 	Obstacle obstacle(x, y, obst);  	
 	enqueue(obstacle); 
 	 	} 
 	 	for (int i = 0; i < n; i++){  	 	
 	            gotoxy(queueArray[i].x, queueArray[i].y);  	
 	 	    cout << queueArray[i].obs; 
 	 	} 
 	} 
 
void generateObstacle(int X, int Y, char ch){ 
  switch (ch) {   case 'E': 
 	 	 	setobstaclelocation_and_generate(10,X,Y,ch); 
 	 	 	break;  	
                  case 'M': 
 	 	 	setobstaclelocation_and_generate(20,X,Y,ch); 
 	 	 	break;  	 	
                  case 'H': 
 	 	 	setobstaclelocation_and_generate(30,X,Y,ch); 
 	 	 	break; 
 	 	} 
 	} 
}; 
 
 
class Coins 
{
public: 
 	Coins* next;  
	int x;  	
        int y; 
 	string powerup = "+"; 
 
 	Coins(){  	 	
           this->x = 0;  	
        	this->y = 0;  	 
	    next = nullptr; 
 	} 
}; 
 
 
class Coinslinklist 
{ public: 
 	Coins* Coinshead; 
 	Coins* currentCoin; 
 
 	Coinslinklist(){ 
 	 	Coinshead = nullptr;  	
   	currentCoin = nullptr; 
 	} 
 
 	 
void GenerateAndDisplayCoins(){ 
 	for (int i = 0; i < 20; i++){ 
	 	 	int x = rand() % MAZE_WIDTH; 
int y = rand() % MAZE_HEIGHT; 
	 	AddCoin(x, y); 
	 	} 
 	 	 	currentCoin = Coinshead;  
	 	 	while (currentCoin != NULL) { 
 	 	 	 	gotoxy(currentCoin->x, currentCoin->y);  
	 	 	 	cout << currentCoin->powerup;  	 	 	 
                          	currentCoin = currentCoin->next; 
 	 	 	} 
 	} 
void AddCoin(int x,int y) { 
 	 	Coins* newcoin = new Coins;  	 
         	newcoin->next = nullptr;  	 	
                newcoin->x = x;  	 	
                newcoin->y = y; 
                if (Coinshead==NULL) 
 	 	 	Coinshead=newcoin;  
	 	else{ 
 	 	 	currentCoin = Coinshead;  	

 	 	while (currentCoin->next!=NULL){  	 	
 	 	currentCoin = currentCoin->next; 
 	 	 	} 
 	 	 	currentCoin->next= newcoin; 
 	 	} 
 	} 
}; 
class node{ public: 
node* connection; 
string wallX="===="; string wallY = "|"; 
}; 
class Graph{ public: 
 	node** ConnectedNodes; 
 	int row, col; 
 
 	Graph(){  	 	
         this->row = 11;  	 
	this->col = 22; 
        ConnectedNodes = new node * [row];  
        for (int i = 0; i < row; i++){ 
 	 	 	ConnectedNodes[i] = new node[col]; 
 	 	} 
 	} 
 
 	void makeAndStoreMaze(){ 
// First I am going to make a random maze through a maze generation algorithm: "Binary Tree Algorithm" 
// Approach: go row-to-row from start of the nodes to the end, and assign them a connections either 'forward' or 'below' randomly. 
 	 	for (int i = 0; i < row - 1; i++){  
	 	 	for (int j = 0; j < col - 1; j++){ 
                                                                  
                           if (rand() % 2){ 
 	 	 	 	 	ConnectedNodes[i][j].connection = &ConnectedNodes[i][j + 1]; 
 	 	 	 	} 
 	 	 	 	else{ 
 	 	 	 	 	ConnectedNodes[i][j].connection = &ConnectedNodes[i + 1][j]; 
                                                                   } 
}//for 
}//for 
}//make and store maze void drawMaze(){ 
 	 	system("CLS"); 
 	 	for (int Y = 2, i = 0; Y <= MAZE_HEIGHT && i < row - 1; Y += 3, i++){  	 	 	
                     for (int X = 0, j = 0; X < MAZE_WIDTH && j < col - 1; X += 4, j++){  
	 	 	 	if (ConnectedNodes[i][j].connection == &ConnectedNodes[i][j + 1]){ 
 	 	 	 	 	if (rand() % 2 == 0){ 
 	 	 	 	 	 	gotoxy(X, Y); 
 	 	 	 	 	 	cout << ConnectedNodes[i][j].wallX; 
 	 	 	 	 	} 
 	 	 	 	 	else{ 
 	 	 	 	 	 	gotoxy(X - 2, Y); 
 	 	 	 	 	 	cout << ConnectedNodes[i][j].wallX; 
 	 	 	 	 	} 
 	 	 	 	}//if 
 	 	 	 	else if (ConnectedNodes[i][j].connection == &ConnectedNodes[i + 1][j]){ 
 	 	 	 	 	gotoxy(X, Y); 
 	 	 	 	 	cout << ConnectedNodes[i][j].wallY;;  	 	 	 	 	                 
                                        gotoxy(X, Y + 1); 
 	 	 	 	 	cout << ConnectedNodes[i][j].wallY;;  	 	 	 	 	
                                        gotoxy(X, Y + 2); 
 	 	 	 	 	cout << ConnectedNodes[i][j].wallY;; 
 	 	 	 	} 
 	 	 	}//for 
                                 }//for 
 	for (int i = 0; i <= MAZE_WIDTH; i++){  	 	
                for (int j = 0; j < 1; j++) {  	 	 	
                      gotoxy(MAZE_WIDTH - i, 0);
                      cout << "_";  	
 	 	      gotoxy(MAZE_WIDTH - i, MAZE_HEIGHT + 2);
                      cout << "_"; 
	 	 	} 
	 	} 
 	for (int i = 1; i <= MAZE_HEIGHT; i++) {  	 	 
	    for (int j = 0; j < 1; j++) {  	 	 	 	
                 gotoxy(j, i); cout << "|";  	 	 	 	
                 gotoxy(MAZE_WIDTH - j, i);
                cout << "|"; 
 	 	 	} 
 	 	} 
                gotoxy(CarX, CarY);
                            
                cout << "C"; 
 	 	gotoxy(MAZE_WIDTH, MAZE_HEIGHT + 1);
                cout << "E";       
                gotoxy(88, 10); 
 	 	cout << "Movement: W A S D";  	 	
                gotoxy(88, 12); 
 	 	cout << "Press 0 to exit to Main Menu"; 
 	 	return; 
 	} 
}; 
 
string SelectLevel(){ 
 system("CLS");  
int input;  
string name; 
                 
cout << "\n\n\n\n\n\t\t\tEnter Player name: \n"; 
 	cin >> name; 
cout << "\n\n\n\n\n\t\t\tChoose a Level\n\n\n\t\t\t"; cout << "\n\t\t\t1-Easy\n\t\t\t2-Medium\n\t\t\t3-Hard\n\n\n\t\t\t"; cin >> input; 
switch (input) 
 	{ 
 	case 1:  
	 	Level = 'E';  
	 	return name;  	 	
                break; 
 
 	case 2:  	 	
                Level = 'M';  	 	
                return name;  	 	
                 break; 
 
 	case 3:  	 	
             Level = 'H';  	
         	return name;  	 
        	break; 
 
 
 	default: 
            cout << "Wrong Choice...\nEnter again";  
           return SelectLevel(); 
 	} 
} 
 
 
void ShowLeadersBoard(){ 
      system("CLS");
   fstream file("LeadersBoard.txt"); 
   string temp; 
   cout << "\t\tLEADERSHIP BOARD\n"; 
while (!file.eof()){ 
	 	getline(file, temp); 
                 cout << temp << "\n"; 
 	}//while 
}//show leadership board 
 
void MoveDataToFile(string name, int score){  
	fstream file("LeadersBoard.txt", ios::app);  	
         file << "\n";  	
        file << name << "\t\t\t\t\t" << score; 
   }//move data to file 
 
void CheckMovement(int &Score) 
{ 
 	// Movement Check  
	while (1){  	 	
          if (_kbhit()) {  	 
	 	char ch = _getch(); 
 	 	 	if (ch == 'A' || ch == 'a'){  	 
	 	 	if (getCharAtXY(CarX - 1, CarY) == ' '){ 
 	 	 	 	 	gotoxy(CarX, CarY);  	 
	 	 	 	        cout << " ";  	 	 	 	
 	                                CarX -= 1; 
 	 	 	 	 	gotoxy(CarX, CarY); 
	 	                        cout << "C"; 
	 	                        Score++; 
                         }
            else if (getCharAtXY(CarX - 1, CarY) == 'E'){ 
	 	gotoxy(0, MAZE_HEIGHT + 20); 
	 	 	cout << "\n\nYou Won"; 
	 	 	CarX = 2; 
 	 	 	CarY = 1;
  	 	 	_getch();
  	 	 	 return; 
 	 	 	 	} 
 	   else if (getCharAtXY(CarX - 1, CarY) == '!'){ 
 	 	 	 	 	gotoxy(CarX, CarY);  	 
         	 	 	 	cout << " ";
  	 	 	 	 	CarX -= 1; 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << "C";
  	 	 	 	 	Score -= 5; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX - 1, CarY) == '+'){ 
 	 	 	 	 	gotoxy(CarX, CarY);  	 
                  	 	 	cout << " ";  
	 	 	 	 	CarX -= 1; 
 	 	 	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score += 10; 
 	 	 	 	} 
 	 	 	} 
 	 	 	 
                          else if (ch == 'S' || ch == 's'){ 
                                 if (getCharAtXY(CarX, CarY + 1) == ' '){ 
                                    gotoxy(CarX, CarY);    
                                    cout << " "; 
 	                            CarY += 1;
                        	 	gotoxy(CarX, CarY);  	 
                                	cout << "C"; 
 	 	 	 	 	Score++; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX, CarY + 1) == 'E'){ 
 	 	 	 	 	gotoxy(MAZE_WIDTH, MAZE_HEIGHT + 1);  
	 	 	 	 	cout << "\n\n\t\t\t\tYOU WON"; 
 	 	 	 	 	CarX = 2;  	 	 
                   	 	 	CarY = 1; 
 	 	 	 	 	_getch();  
	 	 	 	 	return; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX, CarY + 1) == '!'){ 
 	 	 	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << " ";  	 
	 	 	 	        CarY += 1; 
 	 	 	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score -= 5; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX, CarY + 1) == '+'){ 
 	 	 	 	 	gotoxy(CarX, CarY);  	 	 	 	
                                 	cout << " "; 
 	 	 	 	 	CarY += 1; 
	 	                        gotoxy(CarX, CarY); 
                                        cout << "C"; Score += 10; } } else if (ch == 'D' || ch == 'd'){ 
	 	                     if (getCharAtXY(CarX + 1, CarY) == ' '){ 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << " ";
  	 	 	 	 	CarX += 1; 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score++; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX + 1, CarY) == 'E'){ 
 	 	 	 	 	gotoxy(MAZE_WIDTH, MAZE_HEIGHT + 1); 
 	 	 	 	 	cout << "\n\nYOU WON"; 
 	 	 	 	 	CarX = 2;
  	 	 	 	 	CarY = 1; 
 	 	 	 	 	_getch();  
	 	 	 	 	return; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX + 1, CarY) == '!'){ 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << " ";  	
 	 	 	 	         CarX += 1; 
 	 	 	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score -= 5;} 
                                   else if (getCharAtXY(CarX + 1, CarY) == '+'){ 
                                      gotoxy(CarX, CarY); cout << " "; 
                                      CarX += 1; 
	 	                      gotoxy(CarX, CarY); 
	 	 	              cout << "C"; 
	 	 	              Score += 10; 
 	 	 	 	} 
 	 	 	} 
 	 	 	else if (ch == 'W' || ch == 'w'){  
	 	 	 	if (getCharAtXY(CarX, CarY - 1) == ' '){ 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << " ";  
	 	 	 	 	CarY -= 1; 
 	 	 	 	 	gotoxy(CarX, CarY);
  	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score++; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX, CarY - 1) == 'E'){ 
 	 	 	 	 	gotoxy(MAZE_WIDTH, MAZE_HEIGHT + 1);  	 	 	 
                            	 	cout << "\n\n\t\t\tYOU WON"; 
 	 	 	 	 	CarX = 2;  
	 	 	 	 	CarY = 1;  
	 	 	 	 	_getch();  
	 	 	 	 	return; 
 	 	 	 	} 
 	 	 	 	else if (getCharAtXY(CarX, CarY - 1) == '!'){ 
 	 	 	 	 	gotoxy(CarX, CarY);  	 	 	 	 
                                	cout << " "; 
	                         	CarY -= 1; 
                                        gotoxy(CarX, CarY); cout << "C"; 
                                        Score -= 5; 
                                     } 
	 	else if (getCharAtXY(CarX, CarY - 1) == '+'){ 
	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << " ";
  	 	 	 	 	CarY -= 1; 
 	 	 	 	 	gotoxy(CarX, CarY); 
 	 	 	 	 	cout << "C"; 
 	 	 	 	 	Score += 10; 
 	 	 	 	} 
 	 	 	} 
 	 	 	else if (ch == '0'){ 
 	 	 	 	CarX = 2;  	 	 	 	
                                CarY = 1; 
 	 	 	 	MainMenu(); 
 	 	 	} 
 	 	 	gotoxy(88, 4); cout << "Score: " << Score; 
 	 	} 
 	} 
}//check movement 
 
void StartGame(string name){ 
 	Graph Maze; 
 	Queue obstacleQueue(50);  
	Coinslinklist powerUps;  	
        int Score = 0; 
        Maze.makeAndStoreMaze(); 
        Maze.drawMaze(); 
        obstacleQueue.generateObstacle(MAZE_WIDTH, MAZE_HEIGHT, Level);
        powerUps.GenerateAndDisplayCoins(); 
        CheckMovement(Score); 
        MoveDataToFile(name, Score);  
        cout << "\n\t\t\tData Moved to file\n"; 
 	_getch(); 
 	MainMenu(); 
} 
 
void MainMenu(){ 
 	system("CLS");  	
        string name;  	
        int input;  	
        cout << "\n\n\n\n\n\t\t\tWELCOME TO THE MAZE GAME\n"; 
       	cout << "\n\t\t\t1-Play Game\n\t\t\t2-View LeaderBoard\n\t\t\t3-Exit Game\n\n\n\t\t\t";  
	cin >> input;  	switch (input){  	
        case 1: 
 	 	name = SelectLevel(); 
 	 	StartGame(name); 
 	 	_getch(); 
 	 	MainMenu();  	 
	break;  
	case 2: 
 	 	ShowLeadersBoard();  
	 	_getch(); 
 	        MainMenu();  
     	break; 
       case 3: 
 	       exit(0);  	
         break; 
      default: 
	 	cout << "Wrong Choice...\nEnter again"; 
 	 	MainMenu(); 
 	} 
} 
int main() 
{ 
 	MainMenu(); 
 	return 0; 
} 
