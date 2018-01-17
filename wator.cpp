#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Creating the objects for each of the objects
char water = '~';
char BruceShark = '^';
char Marlinfish = 'F';


class Grid
{
	public:
    	char object;
    	int ageLevel;
    	int hungerLevel;
    	bool handled;

	// Constructor for the Grid.
    Grid()
	{
    	object = water;
    	ageLevel = 0;
    	hungerLevel = 0;
   	}

	// Contstructor for types: MarlinFish and Sharks
    Grid(char type)
	{
		 if(type == water)
	  		{
			   	object = water;
			    ageLevel = 0;
			    hungerLevel = 0;
	   		}
   		else if (type == MarlinFish)
   			{
			    object = MarlinFish;
			    ageLevel = 0;
			    handled = true;
  			}
	    else
	   		{
			    object = BruceShark;
			    ageLevel = 0;
			    hungerLevel = 0;
			    handled = true;
	   		}
	}

};


int nFish = 30;
int nShark = 2;
int const width = 15;
int const height = 15;
int randomXPos = 0;
int randomYPos = 0;
int fishBreed = 4;
int sharkBreed = 6;


//creating the sea grid
void draw(vector<vector<Grid>> &sea )
{
	system("clear");

		for(int i = 0; i < height; i++)
	    {
	  
	        for(int j= 0; j < width; j++)
	            {
					cout << sea[j][i].object;
					
		    	}

			cout << endl;
	    }
	 
}

//METHOD -- Used to populate grid with MarlinFish and sharks.
void populate(vector<vector<Grid>> &sea , int nFish, int nShark)
{
	//Checking for available space for MarlinFish
	while (nFish > 0)
	{
	    randomXPos = rand() % width;
	    randomYPos = rand() % height;
	    if (sea[randomXPos][randomYPos].object == water)
	    {
			sea[randomXPos][randomYPos] = Grid(MarlinFish);
			--nFish;
	    }
	    	
	}
	//Checking for available space for sharks
	while (nShark > 0)
	{
	    randomXPos = rand() % width;
	    randomYPos = rand() % height;
	    if (sea[randomXPos][randomYPos].object == water)
	    {
			sea[randomXPos][randomYPos] = Grid(BruceShark);
			--nShark;
	    }
	}
}

bool check(vector<vector<Grid>> &sea , int x ,int y)
{

	if (x < 0 || x >= width)
	{
		if(x < 0)
		{
			x = width -1;
		}
		else
		{
			x = 0;
		}

	}

	if (y < 0 || y >= height)
	{
		if(y < 0)
		{
			y = height -1;
		}
		else
		{
			y = 0;
		}
	}

	if(sea[x][y].object == water)
	{
		return true;

	}
	// Stopping a BruceShark from overlapping another BruceShark. 
	if(sea[x][y].object == BruceShark)
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool checkFish(vector<vector<Grid>> &sea , int x ,int y)
{
	if (x < 0 || x >= width)
	{
		if(x < 0)
		{
			x = width -1;
		}
		else
		{
			x = 0;
		}
	}

	if (y < 0 || y >= height)
	{
		if(y < 0)
		{
			y = height -1;
		}
		else
		{
			y = 0;
		}
	}
	//If there is a MarlinFish close the BruceShark will go
	if(sea[x][y].object == MarlinFish)
	{
		return true;

	}
	else
	{
		return false;
	}


}
	
// Method for the next move of the MarlinFish
void moveFish(vector<vector<Grid>> &sea , int x ,int y)
{

	//creating variables for the next available position 
	bool up = check(sea, x , y -1 );
	bool down  = check(sea, x , y + 1 );
	bool left  = check(sea, x -1 , y);
	bool right  = check(sea, x +1, y);
	int move = 0;

	if(up || down || left || right)
	{
		move = 1;
	}

	if(move == 0)
	{
		sea[x][y].ageLevel++;
		sea[x][y].handled = true;
	}
	else	
	{   
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[x][newPos].ageLevel >= fishBreed)
				{
					sea[x][y] = Grid(MarlinFish);
					sea[x][newPos].ageLevel = 0;
					nFish++;
				}
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].ageLevel >= fishBreed)
				{
					sea[x][y] = Grid(MarlinFish);
					sea[x][newPos].ageLevel = 0;
					nFish++;
				}
			}
			else if (direction == 2 && left)
			{
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height - 1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[newPos][y].ageLevel >= fishBreed)
				{
					sea[x][y] = Grid(MarlinFish);
					sea[newPos][y].ageLevel = 0;
					nFish++;
				}		
			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = width - 1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[x][y] = Grid();
				move = 0;
				if(sea[newPos][y].ageLevel >= fishBreed)
				{
					sea[x][y] = Grid(MarlinFish);
					sea[newPos][y].ageLevel = 0;
					nFish++;
				}
			}
		}
	}
	
	
}
// Method for the next move of the BruceShark
void moveShark(vector<vector<Grid>> &sea , int x ,int y)
{
	//creating variables for the next available position 
	bool up = checkFish(sea, x , y -1 );
	bool down  = checkFish(sea, x , y + 1 );
	bool left  = checkFish(sea, x -1 , y);
	bool right  = checkFish(sea, x +1, y);
	int move = 0;
   	
	
	// VALIDATION -- if a BruceShark eats a MarlinFish
	if(up || down || left || right)
	{
		move = 1;
		
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y]; //moves the BruceShark or MarlinFish
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][newPos].hungerLevel = 0;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hungerLevel == 4)
				{
					sea[x][newPos] = Grid();
					nShark--;
				}
				
				if(sea[x][newPos].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[x][newPos].ageLevel = 0;
					sea[x][newPos].hungerLevel = 0;
					nShark++;
				}
				
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][newPos].hungerLevel = 0 ;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hungerLevel == 4)
				{
					sea[x][newPos]= Grid();
					nShark--;
				}
			
				if(sea[x][newPos].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[x][newPos].ageLevel = 0;
					sea[x][newPos].hungerLevel = 0;
					nShark++;
				}
				
			}
			else if (direction == 2 && left)
			{
			
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height -1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[newPos][y].hungerLevel = 0 ;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hungerLevel == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
					
				}
				
				if(sea[newPos][y].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[newPos][y].ageLevel = 0;
					sea[x][newPos].hungerLevel = 0;
					nShark++;
				}		

			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = 0;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[newPos][y].hungerLevel = 0;
				nFish--;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hungerLevel == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
				}

				if(sea[newPos][y].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[newPos][y].ageLevel = 0;
					sea[x][newPos].hungerLevel = 0;
					nShark++;
				}
			}	
	}
}
	else
	{
		up = check(sea, x , y -1 );
		down  = check(sea, x , y + 1 );
		left  = check(sea, x -1 , y);
		right  = check(sea, x +1, y);

		if(up || down || left || right)
		{
			move = 1;
		}
	}
	
	if(move == 0)
	{
		sea[x][y].ageLevel++;
		sea[x][y].hungerLevel++;

		if(sea[x][y].hungerLevel == 4)
				{
					sea[x][y] = Grid();
					nShark--;
				}

		sea[x][y].handled = true;
	}
	else
   	{
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && up)
			{
				int newPos = y - 1;
				if(newPos < 0)
				{
					newPos = width - 1;
				}
				sea[x][newPos] = sea[x][y]; //moves the BruceShark or MarlinFish
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][newPos].hungerLevel++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hungerLevel == 4)
				{
					sea[x][newPos] = Grid();
					nShark--;
				}
				
				if(sea[x][newPos].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[x][newPos].ageLevel = 0;
					nShark++;
				}
				
			}
			else if (direction == 1 && down)
			{
				int newPos = y + 1;
				if(newPos >= width)
				{
					newPos = 0;
				}
				sea[x][newPos] = sea[x][y];
				sea[x][newPos].handled = true;
				sea[x][newPos].ageLevel++;
				sea[x][newPos].hungerLevel++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[x][newPos].hungerLevel == 4)
				{
					sea[x][newPos]= Grid();
					nShark--;
				}
			
				if(sea[x][newPos].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[x][newPos].ageLevel = 0;
					nShark++;
				}
			
			}
			else if (direction == 2 && left)
			{
			
				int newPos = x - 1;
				if(newPos < 0)
				{
					newPos = height -1;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[newPos][y].hungerLevel++;
				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hungerLevel == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
					
				}
				

				
				if(sea[newPos][y].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[newPos][y].ageLevel = 0;
					nShark++;
				}		

			
			}
			else if (direction == 3 && right)
			{
				int newPos = x + 1 ;
				if(newPos >= height)
				{
					newPos = 0;
				}
				sea[newPos][y] = sea[x][y];
				sea[newPos][y].handled = true;
				sea[newPos][y].ageLevel++;
				sea[newPos][y].hungerLevel++;

				sea[x][y] = Grid();
				move = 0;

				if(sea[newPos][y].hungerLevel == 4)
				{
					sea[newPos][y]= Grid();
					nShark--;
				}

				
				if(sea[newPos][y].ageLevel >= sharkBreed)
				{
					sea[x][y] = Grid(BruceShark);
					sea[newPos][y].ageLevel = 0;
					nShark++;
				}
				
			}
		}
	}
	
}
void sim(vector<vector<Grid>> &sea )
{
	for(int i = 0; i < height; i++)
    {
        for(int j= 0; j < width; j++)
            {
            	if(sea[j][i].handled == false)
            	{
            		if(sea[j][i].object == MarlinFish)
	            	{
	            		//move MarlinFish
	            		moveFish(sea, j, i);
	            	}
	            	else if (sea[j][i].object == BruceShark)
	            	{
	            		moveShark(sea, j,i);
	            	}
	            	else
	            	{

	            	}
            	}
            }
    }
}
void resetFish(vector<vector<Grid>> &sea)
{
	for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
				sea[i][j].handled = false;
	    	}
    }
}

int main(void) 
{
	srand(time(NULL));
	vector<vector<Grid>> sea ;
	sea.resize(width);
	
	for( int i = 0; i < width; i++)
	{
		sea[i].resize(height);
	}
   	
	populate(sea, nFish, nShark);
	int i = 1;

	while(true)
	{
		

		resetFish(sea);
		draw(sea);
		sim(sea);
		cout << endl;
		cout << "_______WATOR Simulation______" << endl;

	 this_thread::sleep_for(chrono::milliseconds(400));

	}
}
