/************************************************************
*	nQueen.cpp												*
*	Author: Jayant Gandhi									*
*	NetID: jg492											*
*	Created on: 3/9/2012									*
*	Last edited on: 6/9/2012								*
*	Due on: 6/9/2012										*
*															*
*	This is my .cpp file for the nQueen recursion project.	*
*	I included my class definition/implementation with the	*
*	driver file since this was a short project.				*
*************************************************************/

#include <iostream>

const int MAX_SIZE = 8;

class nBoard
{
public:
	nBoard ();
		//default constructor
		//postcondition: n set to 0 and board initialized
	nBoard (int size);
		//default constructor
		//postcondition: n set to int and board initialized
	~nBoard();
		//destructor
	void setN (int size);
		//function to set value of n
		//postcondition: n is set to int
	int getN () const;
		//function to return value of n
		//precondition: n has been initialized
	bool placeQueen (int row, int col);
		//function that determines a solution to the nQueen problem
		//starting at the (row,col) coordinate given and traversing
		//the board until the last column has been filled
		//postcondition: returns true if a solution is found and returns
		//				false if no solution can be found
	void printSolution () const;
		//function to print out the solved board to the screen
		//precondition: placeQueen must have been used to find a solution
		//				first, otherwise will just print the initialized board
private:
	bool checkAttack (int row, int col);
		//function that checks to see if a given spot is safe
		//it is used within the placeQueen(int,int) function
		//postcondition: returns true if a spot is safe (i.e. no previously placed
		//				queen can attack it) and returns false if it is not safe
	void initializeBoard ();
		//function that sets all spots on the board as empty (0)
		//postcondition: all values in the 2d array board are set to 0
	int n;
		//variable that marks the dimensions of the board and number of queens to be placed
	int board[MAX_SIZE][MAX_SIZE];
		//the two dimensional array that stores where a queen is placed
		//the dimensions are row and column respectively
};
//In the board array itself 0 will be empty spaces and 7 will signify a queen

int main(int argc, char *argv[] )
{
	int size;
	char temp;
	bool inputOK;
	bool done=false;

	if(argc >=2)
		inputOK=true;
	else
	{
		inputOK=false;
		std::cout<<"No command line argument for size of board."<<std::endl;
		std::cout<<"Please run program again with an integer (4-8) as a command line argument."<<std::endl;
		return 1;
	}
	size = *argv[1]-48; //convert the char to int
						//I used the ascii table numbers, is there a better way to do this?
	if((size<4)||(size>8))
	{
		inputOK=false;
		std::cout<<"Sorry I cannot use that number. Please include a number between 4 and 8 in the command line."<<std::endl;
		return 2;
	}
	else
		inputOK=true;
	if(inputOK==true)
	{
		nBoard myBoard(size);
		done=myBoard.placeQueen(0,0);
		if(done==true)
			myBoard.printSolution();
		else
			std::cout<<"Sorry, could not find a solution"<<std::endl;
	}
	return 0;
}

void nBoard::initializeBoard ()
{
	for (int i=0; i<MAX_SIZE; i++)
	{
		for (int j=0; j<MAX_SIZE; j++)
			board [i][j] = 0;
	}
}

nBoard::nBoard ()
{
	n=0;
	initializeBoard();
}

nBoard::nBoard (int size)
{
	setN(size);
	initializeBoard();
}

nBoard::~nBoard ()
{
	//no need to deallocate memory...
}


void nBoard::setN (int size)
{
	n=size;
}

int nBoard::getN () const
{
	return n;
}

bool nBoard::checkAttack(int row, int col)
{ 
	int i, j;
	if(col==0)//first column is always safe
	{
		//std::cout<<"safe"<<std::endl; **used in debugging
		return true;
	}
   
    for (i = 0; i < col; i++) //check row for queen
    {
        if (board[row][i]==7)
		{
			//std::cout<<"unsafe"<<std::endl; **used in debugging
            return false;
		}
    }
 
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) //check upper diagonal for queen
    {
        if (board[i][j]==7)
        {
			//std::cout<<"unsafe"<<std::endl; **used in debugging
            return false;
		}
    }

    for (i = row, j = col; j >= 0 && i < n; i++, j--) //check lower diagonal for queen
    {
        if (board[i][j]==7)
		{
			//std::cout<<"unsafe"<<std::endl; **used in debugging
            return false;
		}
    }
    return true;
}

bool nBoard::placeQueen (int row, int col)
{
    if (col >= n) //Once col reaches n a solution has been found
        return true;
 
    for (int i = 0; i < n; i++) //within this column test each row for a safe spot
    {
        if ( checkAttack( i, col) ) //check spot
        {
            board[i][col] = 7; //place a queen
			/*std::cout<<"Placed Queen #" << col+1 <<std::endl;
			//system ("PAUSE");									**used in debugging
			printSolution();
			*/

            if ( placeQueen(0, col + 1) == true )//move to next column using recursion
                return true;
 
            board[i][col] = 0; //if this spot does not ultimately lead to a solution remove queen
        }
    }

    return false; //default if function cannot reach col==n
				  //(should only happen for cases of n<4)
}

void nBoard::printSolution () const
{
	for (int i=0; i<n; i++)//cycle rows
	{
		for (int j=0; j<n; j++)//cycle columns
		{
			if (board[i][j]==7)
				std::cout<<"Q";
			else
				std::cout<<"-";
		}
		std::cout<<std::endl;
	}
}