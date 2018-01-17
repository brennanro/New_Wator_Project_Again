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
char MarlinFish = 'F';


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


int numberOfFish = 30;
int numberOfSharks = 2;
int const width = 15;
int const height = 15;
int randomWidthPosition = 0;
int randomHeightPosition = 0;
int movesToBreedFish = 4;
int movesToBreedShark = 6;


//creating the ocean grid
void createGrid(vector<vector<Grid>> &ocean )
{
	system("clear");

		for(int i = 0; i < height; i++)
	    {
	  
	        for(int j= 0; j < width; j++)
	            {
					cout << ocean[j][i].object;
					
		    	}

			cout << endl;
	    }
	 
}

//METHOD -- Used to fill grid with MarlinFish and sharks.
void fill(vector<vector<Grid>> &ocean , int numberOfFish, int numberOfSharks)
{
	//Checking for available space for MarlinFish
	while (numberOfFish > 0)
	{
	    randomWidthPosition = rand() % width;
	    randomHeightPosition = rand() % height;
	    if (ocean[randomWidthPosition][randomHeightPosition].object == water)
	    {
			ocean[randomWidthPosition][randomHeightPosition] = Grid(MarlinFish);
			--numberOfFish;
	    }
	    	
	}
	//Checking for available space for sharks
	while (numberOfSharks > 0)
	{
	    randomWidthPosition = rand() % width;
	    randomHeightPosition = rand() % height;
	    if (ocean[randomWidthPosition][randomHeightPosition].object == water)
	    {
			ocean[randomWidthPosition][randomHeightPosition] = Grid(BruceShark);
			--numberOfSharks;
	    }
	}
}

bool checkArea(vector<vector<Grid>> &ocean , int x ,int y)
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

	if(ocean[x][y].object == water)
	{
		return true;

	}
	// Stopping a BruceShark from overlapping another BruceShark. 
	if(ocean[x][y].object == BruceShark)
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool checkFishArea(vector<vector<Grid>> &ocean , int x ,int y)
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
	if(ocean[x][y].object == MarlinFish)
	{
		return true;

	}
	else
	{
		return false;
	}


}
	
// Method for the next move of the MarlinFish
void moveFish(vector<vector<Grid>> &ocean , int x ,int y)
{

	//creating variables for the next available position 
	bool forward = checkArea(ocean, x , y -1 );
	bool back  = checkArea(ocean, x , y + 1 );
	bool left  = checkArea(ocean, x -1 , y);
	bool right  = checkArea(ocean, x +1, y);
	int move = 0;

	if(forward || back || left || right)
	{
		move = 1;
	}

	if(move == 0)
	{
		ocean[x][y].ageLevel++;
		ocean[x][y].handled = true;
	}
	else	
	{   
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && forward)
			{
				int nextPosition = y - 1;
				if(nextPosition < 0)
				{
					nextPosition = width - 1;
				}
				ocean[x][nextPosition] = ocean[x][y];
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][y] = Grid();
				move = 0;
				if(ocean[x][nextPosition].ageLevel >= movesToBreedFish)
				{
					ocean[x][y] = Grid(MarlinFish);
					ocean[x][nextPosition].ageLevel = 0;
					numberOfFish++;
				}
			}
			else if (direction == 1 && back)
			{
				int nextPosition = y + 1;
				if(nextPosition >= width)
				{
					nextPosition = 0;
				}
				ocean[x][nextPosition] = ocean[x][y];
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].ageLevel >= movesToBreedFish)
				{
					ocean[x][y] = Grid(MarlinFish);
					ocean[x][nextPosition].ageLevel = 0;
					numberOfFish++;
				}
			}
			else if (direction == 2 && left)
			{
				int nextPosition = x - 1;
				if(nextPosition < 0)
				{
					nextPosition = height - 1;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[x][y] = Grid();
				move = 0;
				if(ocean[nextPosition][y].ageLevel >= movesToBreedFish)
				{
					ocean[x][y] = Grid(MarlinFish);
					ocean[nextPosition][y].ageLevel = 0;
					numberOfFish++;
				}		
			}
			else if (direction == 3 && right)
			{
				int nextPosition = x + 1 ;
				if(nextPosition >= height)
				{
					nextPosition = width - 1;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[x][y] = Grid();
				move = 0;
				if(ocean[nextPosition][y].ageLevel >= movesToBreedFish)
				{
					ocean[x][y] = Grid(MarlinFish);
					ocean[nextPosition][y].ageLevel = 0;
					numberOfFish++;
				}
			}
		}
	}
	
	
}
// Method for the next move of the BruceShark
void moveShark(vector<vector<Grid>> &ocean , int x ,int y)
{
	//creating variables for the next available position 
	bool forward = checkFishArea(ocean, x , y -1 );
	bool back  = checkFishArea(ocean, x , y + 1 );
	bool left  = checkFishArea(ocean, x -1 , y);
	bool right  = checkFishArea(ocean, x +1, y);
	int move = 0;
   	
	
	// VALIDATION -- if a BruceShark eats a MarlinFish
	if(forward || back || left || right)
	{
		move = 1;
		
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && forward)
			{
				int nextPosition = y - 1;
				if(nextPosition < 0)
				{
					nextPosition = width - 1;
				}
				ocean[x][nextPosition] = ocean[x][y]; //moves the BruceShark or MarlinFish
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][nextPosition].hungerLevel = 0;
				numberOfFish--;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].hungerLevel == 4)
				{
					ocean[x][nextPosition] = Grid();
					numberOfSharks--;
				}
				
				if(ocean[x][nextPosition].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[x][nextPosition].ageLevel = 0;
					ocean[x][nextPosition].hungerLevel = 0;
					numberOfSharks++;
				}
				
			}
			else if (direction == 1 && back)
			{
				int nextPosition = y + 1;
				if(nextPosition >= width)
				{
					nextPosition = 0;
				}
				ocean[x][nextPosition] = ocean[x][y];
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][nextPosition].hungerLevel = 0 ;
				numberOfFish--;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].hungerLevel == 4)
				{
					ocean[x][nextPosition]= Grid();
					numberOfSharks--;
				}
			
				if(ocean[x][nextPosition].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[x][nextPosition].ageLevel = 0;
					ocean[x][nextPosition].hungerLevel = 0;
					numberOfSharks++;
				}
				
			}
			else if (direction == 2 && left)
			{
			
				int nextPosition = x - 1;
				if(nextPosition < 0)
				{
					nextPosition = height -1;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[nextPosition][y].hungerLevel = 0 ;
				numberOfFish--;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[nextPosition][y].hungerLevel == 4)
				{
					ocean[nextPosition][y]= Grid();
					numberOfSharks--;
					
				}
				
				if(ocean[nextPosition][y].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[nextPosition][y].ageLevel = 0;
					ocean[x][nextPosition].hungerLevel = 0;
					numberOfSharks++;
				}		

			}
			else if (direction == 3 && right)
			{
				int nextPosition = x + 1 ;
				if(nextPosition >= height)
				{
					nextPosition = 0;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[nextPosition][y].hungerLevel = 0;
				numberOfFish--;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[nextPosition][y].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[nextPosition][y].ageLevel = 0;
					ocean[x][nextPosition].hungerLevel = 0;
					numberOfSharks++;
				}
			}	
	}
}
	else
	{
		forward = checkArea(ocean, x , y -1 );
		back  = checkArea(ocean, x , y + 1 );
		left  = checkArea(ocean, x -1 , y);
		right  = checkArea(ocean, x +1, y);

		if(forward || back || left || right)
		{
			move = 1;
		}
	}
	
	if(move == 0)
	{
		ocean[x][y].ageLevel++;
		ocean[x][y].hungerLevel++;

		if(ocean[x][y].hungerLevel == 4)
				{
					ocean[x][y] = Grid();
					numberOfSharks--;
				}

		ocean[x][y].handled = true;
	}
	else
   	{
		//creating this varible to make a random move.
		while (move > 0)
		{
			int direction = rand() % 4; 

			if (direction == 0 && forward)
			{
				int nextPosition = y - 1;
				if(nextPosition < 0)
				{
					nextPosition = width - 1;
				}
				ocean[x][nextPosition] = ocean[x][y]; //moves the BruceShark or MarlinFish
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][nextPosition].hungerLevel++;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].hungerLevel == 4)
				{
					ocean[x][nextPosition] = Grid();
					numberOfSharks--;
				}
				
				if(ocean[x][nextPosition].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[x][nextPosition].ageLevel = 0;
					numberOfSharks++;
				}
				
			}
			else if (direction == 1 && back)
			{
				int nextPosition = y + 1;
				if(nextPosition >= width)
				{
					nextPosition = 0;
				}
				ocean[x][nextPosition] = ocean[x][y];
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++;
				ocean[x][nextPosition].hungerLevel++;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].hungerLevel == 4)
				{
					ocean[x][nextPosition]= Grid();
					numberOfSharks--;
				}
			
				if(ocean[x][nextPosition].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[x][nextPosition].ageLevel = 0;
					numberOfSharks++;
				}
			
			}
			else if (direction == 2 && left)
			{
			
				int nextPosition = x - 1;
				if(nextPosition < 0)
				{
					nextPosition = height -1;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[nextPosition][y].hungerLevel++;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[nextPosition][y].hungerLevel == 4)
				{
					ocean[nextPosition][y]= Grid();
					numberOfSharks--;
					
				}
				

				
				if(ocean[nextPosition][y].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[nextPosition][y].ageLevel = 0;
					numberOfSharks++;
				}		

			
			}
			else if (direction == 3 && right)
			{
				int nextPosition = x + 1 ;
				if(nextPosition >= height)
				{
					nextPosition = 0;
				}
				ocean[nextPosition][y] = ocean[x][y];
				ocean[nextPosition][y].handled = true;
				ocean[nextPosition][y].ageLevel++;
				ocean[nextPosition][y].hungerLevel++;

				ocean[x][y] = Grid();
				move = 0;

				if(ocean[nextPosition][y].hungerLevel == 4)
				{
					ocean[nextPosition][y]= Grid();
					numberOfSharks--;
				}

				
				if(ocean[nextPosition][y].ageLevel >= movesToBreedShark)
				{
					ocean[x][y] = Grid(BruceShark);
					ocean[nextPosition][y].ageLevel = 0;
					numberOfSharks++;
				}
				
			}
		}
	}
	
}
void allowMovement(vector<vector<Grid>> &ocean )
{
	for(int i = 0; i < height; i++)
    {
        for(int j= 0; j < width; j++)
            {
            	if(ocean[j][i].handled == false)
            	{
            		if(ocean[j][i].object == MarlinFish)
	            	{
	            		//move MarlinFish
	            		moveFish(ocean, j, i);
	            	}
	            	else if (ocean[j][i].object == BruceShark)
	            	{
	            		moveShark(ocean, j,i);
	            	}
	            	else
	            	{

	            	}
            	}
            }
    }
}
void resetFish(vector<vector<Grid>> &ocean)
{
	for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
				ocean[i][j].handled = false;
	    	}
    }
}

int main(void) 
{
	srand(time(NULL));
	vector<vector<Grid>> ocean ;
	ocean.resize(width);
	
	for( int i = 0; i < width; i++)
	{
		ocean[i].resize(height);
	}
   	
	fill(ocean, numberOfFish, numberOfSharks);
	int i = 1;

	while(true)
	{
		

		resetFish(ocean);
		createGrid(ocean);
		allowMovement(ocean);
		this_thread::sleep_for(chrono::milliseconds(250));

	}
}
