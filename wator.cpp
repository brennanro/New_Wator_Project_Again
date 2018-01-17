/*Rónán Brennan
  Wator Project
  28/12/2017
*/





#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;


char water = '~'; //water and it's symbol used for the grid
char BruceShark = '^'; //Shark and it's symbol
char MarlinFish = 'F'; //Fish and it's symbol


class Grid
{
	public:
    	char object; //object: water, fish or shark
    	int ageLevel; // age of shark or fish
    	int hungerLevel; //hunger of shark or fished
    	bool handled; // handled can be true or false (boolean)

	
    Grid() // water constructed in grid
	{
    	object = water;
    	ageLevel = 0;
    	hungerLevel = 0;
   	}

	
    Grid(char type) //Allows for Fish and Sharks in grid
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


int numberOfFish = 25; //Fish starting in Grid
int numberOfSharks = 4; //Sharks Starting in Grid
int const width = 20; //Width of Grid
int const height = 20; //Height of grid
int randomWidthPosition = 0; //For object position in grid (width) (random)
int randomHeightPosition = 0; //For object position in grid (height) (random)
int movesToBreedFish = 4; //Moves for fish to breed
int movesToBreedShark = 8; //Moves for Shark to breed



void createGrid(vector<vector<Grid>> &ocean ) //Making Ocean (Grid)
{
	

		for(int i = 0; i < height; i++)
	    {
	  
	        for(int j= 0; j < width; j++)
	            {
					cout << ocean[j][i].object;//nested for loop while i and j are less than width and height
					
		    	}

			cout << endl;
	    }
	 
}


void fill(vector<vector<Grid>> &ocean , int numberOfFish, int numberOfSharks) //fills the ocean with fish and Sharks
{
	
	while (numberOfFish > 0) 
	{
	    randomWidthPosition = rand() % width;
	    randomHeightPosition = rand() % height;
	    if (ocean[randomWidthPosition][randomHeightPosition].object == water)
	    {
			ocean[randomWidthPosition][randomHeightPosition] = Grid(MarlinFish);
			--numberOfFish;
	    } //Checks for space for fish and puts them in where space appears (where space is water not shark)
	    	
	}

	while (numberOfSharks > 0)
	{
	    randomWidthPosition = rand() % width;
	    randomHeightPosition = rand() % height;
	    if (ocean[randomWidthPosition][randomHeightPosition].object == water)
	    {
			ocean[randomWidthPosition][randomHeightPosition] = Grid(BruceShark);
			--numberOfSharks;
	    } //same as fish explanation except shark
	}
}

bool checkArea(vector<vector<Grid>> &ocean , int x ,int y) // check surrounding area
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
	 
	if(ocean[x][y].object == BruceShark) //shark can't eat shark
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool checkFishArea(vector<vector<Grid>> &ocean , int x ,int y) //check Fish in surrounding area
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
	
	if(ocean[x][y].object == MarlinFish) //shark will try eat fish
	{
		return true;

	}
	else
	{
		return false;
	}


}
	

void moveMarlinFish(vector<vector<Grid>> &ocean , int x ,int y) //picks direction for fish to move 
{

	bool forward = checkArea(ocean, x , y -1 );
	bool back  = checkArea(ocean, x , y + 1 );
	bool left  = checkArea(ocean, x -1 , y);
	bool right  = checkArea(ocean, x +1, y);
	int move = 0;

	if(forward || back || left || right)  //fish can move
	{
		move = 1;
	}

	if(move == 0) //fish can't move
	{
		ocean[x][y].ageLevel++;
		ocean[x][y].handled = true;
	}
	else	
	{   
		
		while (move > 0)
		{
			int direction = rand() % 4; //picks random place for fish to move

			if (direction == 0 && forward) //forward
			{
				int nextPosition = y - 1;
				if(nextPosition < 0)
				{
					nextPosition = width - 1;
				}
				ocean[x][nextPosition] = ocean[x][y]; //new position
				ocean[x][nextPosition].handled = true;
				ocean[x][nextPosition].ageLevel++; //fish gets older
				ocean[x][y] = Grid();
				move = 0;
				if(ocean[x][nextPosition].ageLevel >= movesToBreedFish) //fish will breed if greater than number of moves needed to breed
				{
					ocean[x][y] = Grid(MarlinFish);
					ocean[x][nextPosition].ageLevel = 0;
					numberOfFish++;
				}
			}
			else if (direction == 1 && back) //similar to forward except back
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
			else if (direction == 2 && left)//similar again
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
			else if (direction == 3 && right) //and again
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

void moveBruceShark(vector<vector<Grid>> &ocean , int x ,int y) //when a shark eats a fish
{
	
	bool forward = checkFishArea(ocean, x , y -1 );
	bool back  = checkFishArea(ocean, x , y + 1 );
	bool left  = checkFishArea(ocean, x -1 , y);
	bool right  = checkFishArea(ocean, x +1, y);
	int move = 0;
   	
	
	
	if(forward || back || left || right)
	{
		move = 1;
		
		
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
				ocean[x][nextPosition].hungerLevel = 0; //shark also has hunger level. Resets to zero when fish is eaten
				numberOfFish--;
				ocean[x][y] = Grid();
				move = 0;

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
	else //if shark moves to water instead of fish
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

		if(ocean[x][y].hungerLevel == 5)
				{
					ocean[x][y] = Grid();
					numberOfSharks--;
				}

		ocean[x][y].handled = true;
	}
	else
   	{
		
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
				ocean[x][nextPosition].hungerLevel++;
				ocean[x][y] = Grid();
				move = 0;

				if(ocean[x][nextPosition].hungerLevel == 5)
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

				if(ocean[x][nextPosition].hungerLevel == 5)
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

				if(ocean[nextPosition][y].hungerLevel == 5)
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

				if(ocean[nextPosition][y].hungerLevel == 5)
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
void allowMovement(vector<vector<Grid>> &ocean ) //if fish and shark has not been handled (==false) move fish and Shark
{
	for(int i = 0; i < height; i++)
    {
        for(int j= 0; j < width; j++)
            {
            	if(ocean[j][i].handled == false)
            	{
            		if(ocean[j][i].object == MarlinFish)
	            	{
	            		
	            		moveMarlinFish(ocean, j, i);
	            	}
	            	else if (ocean[j][i].object == BruceShark)
	            	{
	            		moveBruceShark(ocean, j,i);
	            	}
	            	else
	            	{

	            	}
            	}
            }
    }
}
void reconstructMarlinFish(vector<vector<Grid>> &ocean)
{
	for(int i = 0; i < width; i++)
    {
        for(int j= 0; j < height; j++)
            {
				ocean[i][j].handled = false; //reconstructs marlin fish
	    	}
    }
}

int main(void) //creates and fills ocean and carries out Wator Simulation
{
	srand(time(NULL));
	vector<vector<Grid>> ocean ;
	ocean.resize(width);
	
	for( int i = 0; i < width; i++)
	{
		ocean[i].resize(height);
	}
   	
	fill(ocean, numberOfFish, numberOfSharks);
	

	while(true)  
	{
		

		reconstructMarlinFish(ocean);
		createGrid(ocean);
		allowMovement(ocean);
		this_thread::sleep_for(chrono::milliseconds(250)); //sleeps for 250ms

	}
}
