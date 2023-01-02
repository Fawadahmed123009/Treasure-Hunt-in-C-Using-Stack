#include<iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define N 10
#define M 10
using namespace std;

class stnode {
public:
	int data;
	stnode* next;
	stnode()
	{
		data = 0;
		next = NULL;
	}
	stnode(int val)
	{
		data = val;
		next = NULL;
	}
};

class stack {
private:
	stnode* top;
	int counter;
	int size;
public:
	stack()
	{
		size = 10;
		top = NULL;
	}
	stack(int s)
	{
		size = s;
	}
	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		else
			return false;
	}
	void push(int val)
	{
		if (counter >= size)
		{
			return;
		}
		stnode* temp = new stnode(val);
		temp->next = top;
		top = temp;
		counter++;
	}
	int pop()
	{
		int x;
		if (isEmpty()) {

		}
		else
		{
			x = top->data;
			stnode* temp = top;
			top = top->next;
			counter--;
			delete temp;
		}
		return x;
	}
	int st_top()
	{
		if (top == NULL)
		{
			return -1;
		}
		else
		{
			return top->data;
		}
	}
};

class room {
private:
	int traesure_room = 0;
	int k = 0;              // for room check
	int T = 0;             //treasure
	int death_devil = 0;     //for death_devil message
	string room_name = " ";      // for treasure room name
	int death_portal = 0;
	stack x_cor;            //store x-coordinate from which user move
	stack y_cor;           //store y-coordinate from which user move
	stack tempx;
	stack tempy;
	stack num_of_room; //for total num_of_room of rooms
public:
	void Main_menu()
	{
		int n;
		cout << "\n\t\t------------Welcome To Treasue Hunt Game---------------\n\n";
		cout << "Enter 1 , 2 or 3 \n";
		cout << "-> To play game enter 1\n";
		cout << "-> To see instructions enter 2\n";
		cout << "-> To exit enter 3\n";
		cin >> n;
		cout << "\n\t\t\t---------------Thank you-----------------";

		if (n == 1)
		{
			system("cls");
			Input();
		}
		else if (n == 2)
		{
			system("cls");
			cout << "X indicates => a forbidden cell (Wall)\n";
			cout << "D=> Devil, G=> Gasper, T=> Treasure\n";
			cout << "P=> Portal teleports the user randomly to another room to a random cell.\n";
			cout << "To move the asterik for iterative code use arrow keys \n";
			cout << "To move the asterik for recursive code use w for up,s for down,a for left,d for right\n";
			cout << "Press 1 to go back to Main Menu\n";
			cin >> n;
			system("cls");
			Main_menu();
		}
		else if (n == 3)
		{
			cout << "\nGame exit\nHave a nice day!!";
		}
	}

	void mini_menu(char** arr, int rows, int cols, int x, int y)
	{
		int choice;
		cout << "1) Recurssive \n";
		cout << "2) Iterative\n";
		cin >> choice;
		if (choice == 1)
			Map(arr, rows, cols, x, y);
		else if (choice == 2)
			Map_itr(arr, rows, cols, x, y);
	}

	void Input()
	{

		string line;
		string mis;
		fstream mainfile;

		mainfile.open("hauntedhouse.txt", std::ios::in);

		if (!mainfile.is_open())
		{
			std::cout << "Error opening the roomfile\n";
		}

		char rooms;
		mainfile >> rooms;

		srand(time(0));

		int total_room = rooms - '0'; // store total number of rooms present in hauntedhouse.txt

		char row_file, col_file;
		char misc;
		char xaxis, yaxis;
		int currentroom = 1;

		int k = rand() % total_room;
		while (k != 0)
		{
			currentroom++;
			mainfile >> mis;
			k--;
		}
		if (traesure_room == 0)
		{
			mainfile >> line;
		}
		else                      // find treasure room
		{
			line = room_name;
		}

		fstream roomfile;

		roomfile.open(line, std::ios::in);
		// opening room roomfile
		if (!roomfile.is_open())
		{
			std::cout << "Error opening the roomfile\n";
		}

		roomfile >> row_file;
		roomfile >> misc;
		roomfile >> col_file;

		roomfile >> xaxis;
		roomfile >> misc;
		roomfile >> yaxis;

		int x = xaxis - '0';
		int y = yaxis - '0';



		int rows = row_file - '0';       //store total number of rows in room file    
		int cols = col_file - '0';      //store total number of columns in room file

		char** arr = new char* [rows];

		for (int i = 0; i < rows; i++)      // initializes **arr
		{
			arr[i] = new char[cols];
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				roomfile >> arr[i][j];                          //remove 0 and print space
				if (arr[i][j] == '0')
				{
					arr[i][j] = ' ';
				}
			}
		}

		num_of_room.push(total_room);
		mini_menu(arr, rows, cols, x, y);                // calling mini menu which ask user for recurrsive or iterative approch

		roomfile.close();
		mainfile.close();

	}

	void gasper()
	{
		bool flag = false;
		string line;
		string mis;
		fstream mainfile;

		mainfile.open("hauntedhouse.txt", ios::in);

		if (!mainfile.is_open())
		{
			std::cout << "Error opening the roomfile\n";
		}

		char rooms;
		mainfile >> rooms;

		srand(time(0));

		int total_room = rooms - '0';

		int k = total_room;
		while (k != 0 && flag == false)
		{
			mainfile >> line;

			std::fstream roomfile;

			roomfile.open(line, std::ios::in);

			if (!roomfile.is_open())
			{
				std::cout << "Error opening the roomfile\n";
			}
			char row_file = ' ', col_file = ' ';
			char misc = ' ';
			char xaxis = ' ', yaxis = ' ';
			int currentroom = 1;

			roomfile >> row_file;
			roomfile >> misc;
			roomfile >> col_file;

			roomfile >> xaxis;
			roomfile >> misc;
			roomfile >> yaxis;

			int x = xaxis - '0';
			int y = yaxis - '0';

			int rows = row_file - '0';
			int cols = col_file - '0';

			char** arr = new char* [rows];

			for (int i = 0; i < rows; i++)
			{
				arr[i] = new char[cols];
			}

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					roomfile >> arr[i][j];
					if (arr[i][j] == '0')
					{
						arr[i][j] = ' ';
					}
					if (arr[i][j] == 'T')
					{
						flag = true;
					}
				}
			}
			k--;
			roomfile.close();

		}

		traesure_room++;
		room_name = line;

		Input();

		mainfile.close();

	}
	void showroom(int total_room, string currentroom)
	{
		cout << "Total number of rooms : " << total_room << "\n";
		cout << "Current Room " << currentroom << "\n";

	}

	void Exit()
	{
		if (death_devil != 0)                          // if player reach Devil
		{
			death_devil = 0;
			cout << "Devil kill you \n";
		}
		else if (T > 0)
		{                                        // if player reach Treasure
			T = 0;
			sort();
			coordinates();
			cout << "You got the treasure \n";
		}
		else if (death_portal > 0)
		{                                        // if player reach portal 
			death_portal = 0;
			cout << "Bad Luck\n";
		}
	}

	void sort()
	{
		if (!x_cor.isEmpty())
		{
			tempx.push(x_cor.pop());
			tempy.push(y_cor.pop());
			sort();
		}
		else
		{
			return;
		}
	}

	void coordinates()                       // print path of player choose by user
	{
		if (!tempx.isEmpty())
		{
			std::cout << "(" << tempx.pop() << ", " << tempy.pop() << ") \n";
			coordinates();
		}
		else
		{
			return;
		}
	}


	void Map(char** arr, int rows, int cols, int x, int y)
	{

		x_cor.push(x);
		y_cor.push(y);

		if (arr[x][y] == 'P')
		{
			static int checker = 0;
			srand(time(0));
			int d = num_of_room.st_top() - 1;
			int t = rand() % num_of_room.st_top();
			int row_file = (rand() % d) + 1;
			if (checker == 0)
			{
				checker = 1000;
				if (row_file == 1)
				{
					death_portal++;
					Exit();
				}
				else
				{
					Input();
				}
			}
			else
			{
				Input();
			}

		}
		else if (arr[x][y] == 'T')
		{
			T++;
			k++;
			T++;
			Exit();
		}
		else if (arr[x][y] == 'G')
		{
			gasper();
		}

		else if (arr[x][y] == 'D')
		{
			death_devil++;
			k++;
			Exit();
		}
		else if (k == 0)
		{
			char** temp = new char* [rows];

			for (int i = 0; i < rows; i++)
			{
				temp[i] = new char[cols];
				for (int j = 0; j < cols; j++)
				{
					if (i == x && j == y)
					{
						temp[i][j] = '*';
					}
					else
					{
						temp[i][j] = arr[i][j];
					}
				}
			}

			system("cls");

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					std::cout << temp[i][j] << "   ";
				}
				std::cout << "\n";
			}

			std::cout << "\n";


			char c ;
			if (true)
			{
				switch ((c = _getch()))
				{
				case 'w':
					if (x > 0)
					{
						x = x - 1;
						if (arr[x][y] == 'X')
						{
							x = x + 1;
						}
					}
					Map(arr, rows, cols, x, y);
					break;
				case 's':
					if (x < rows - 1)
					{
						x = x + 1;
						if (arr[x][y] == 'X')
						{
							x = x - 1;
						}
					}
					Map(arr, rows, cols, x, y);
					break;
				case 'a':
					if (y > 0)
					{
						y = y - 1;
						if (arr[x][y] == 'X')
						{
							y = y + 1;
						}
					}
					Map(arr, rows, cols, x, y);
					break;
				case 'd':
					if (y < cols - 1)
					{
						y = y + 1;
						if (arr[x][y] == 'X')
						{
							y = y - 1;
						}
					}
					Map(arr, rows, cols, x, y);
					break;
				default:
					break;
				}
			}
		}
	}

	void Portal()
	{
		static int checker = 0;
		srand(time(0));
		int d = num_of_room.st_top() - 1;
		int t = rand() % num_of_room.st_top();
		int row_file = (rand() % d) + 1;
		if (checker == 0)
		{
			checker = 1000;
			if (row_file == 1)
			{
				death_portal++;
				Exit();
			}
			else
			{
				Input();
			}
		}
		else
		{
			Input();
		}
	}


	void asterikmove(char** arr, int rows, int cols, int x, int y)
	{
		char** temp = new char* [rows];

		for (int i = 0; i < rows; i++)
		{
			temp[i] = new char[cols];
			for (int j = 0; j < cols; j++)
			{
				if (i == x && j == y)
				{
					temp[i][j] = '*';
				}
				else
				{
					temp[i][j] = arr[i][j];
				}
			}
		}

		system("cls");

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << temp[i][j] << "   ";
			}
			cout << "\n";
		}

		cout << "\n";
	}



	void Map_itr(char** arr, int rows, int cols, int x, int y)
	{
		if (k == 0 && T == 0)
		{

			asterikmove(arr, rows, cols, x, y);

			char chec = ' ';
			while (true)
			{
				chec = ' ';
				switch ((chec = _getch()))
				{
				case KEY_UP:
					if (x > 0)
					{
						x = x - 1;
						x_cor.push(x);
						y_cor.push(y);
						if (arr[x][y] == 'X')
						{
							x = x + 1;
						}
						if (arr[x][y] == 'P')
						{
							Portal();
						}
						if (arr[x][y] == 'T')
						{
							k++;
							T=T+2;
							Exit();

						}
						if (arr[x][y] == 'G')
						{
							gasper();
						}
						if (arr[x][y] == 'D')
						{
							death_devil++;
							k++;
							Exit();
						}
					}
					asterikmove(arr, rows, cols, x, y);
					break;
				case KEY_DOWN:
					if (x < rows - 1)
					{
						x = x + 1;
						x_cor.push(x);
						y_cor.push(y);
						if (arr[x][y] == 'X')
						{
							x = x - 1;
						}
						else if (arr[x][y] == 'P')
						{
							Portal();
						}
						else if (arr[x][y] == 'T')
						{
							k++;
							T=T+2;
							Exit();
						}
						else if (arr[x][y] == 'G')
						{
							gasper();
						}
						else if (arr[x][y] == 'D')
						{
							death_devil++;
							k++;
							Exit();
						}
					}
					asterikmove(arr, rows, cols, x, y);
					break;
				case KEY_LEFT:
					if (y > 0)
					{
						y = y - 1;
						x_cor.push(x);
						y_cor.push(y);
						if (arr[x][y] == 'X')
						{
							y = y + 1;
						}
						else if (arr[x][y] == 'P')
						{
							Portal();
						}
						else if (arr[x][y] == 'T')
						{
							k++;
							T=T+2;
							Exit();
						}
						else if (arr[x][y] == 'G')
						{
							gasper();
						}
						else if (arr[x][y] == 'D')
						{
							death_devil++;
							k++;
							Exit();
						}
					}
					asterikmove(arr, rows, cols, x, y);
					break;
				case KEY_RIGHT:
					if (y < cols - 1)
					{
						y = y + 1;
						x_cor.push(x);
						y_cor.push(y);
						if (arr[x][y] == 'X')
						{
							y = y - 1;
						}
						else if (arr[x][y] == 'P')
						{
							Portal();
						}
						else if (arr[x][y] == 'T')
						{
							k++;
							T = T + 2;
							Exit();
						}
						else if (arr[x][y] == 'G')
						{
							gasper();
						}
						else if (arr[x][y] == 'D')
						{
							death_devil++;
							k++;
							Exit();
						}
					}
					asterikmove(arr, rows, cols, x, y);
					break;
				default:
					break;
				}
			}
		}
	}

};

int main()
{
	room obj;
	obj.Main_menu();
}
