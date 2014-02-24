#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;
class LCG{
	static const int a = 1664525;
	static const int c = 1013904223;
	int seed;
	public:
		static const long m = 281474976710656;
		LCG(int seed){
			this->seed = seed;
		}
		int rand(int upperBound){
			int xNext;
			xNext = (seed*a+c)%m;
			seed = xNext;
			return abs(xNext%upperBound+1);
		}
};

class Cell{
	public:
		int type;//type: Corner ~ 0; Border ~ 1; Inner Cell ~2;
		int spec;//spec: none ~ 0; stop ~ 1; start ~ 2;
		std::vector<int> walls;//4 walls order: North at index 0, South ~ 1, W ~ 2, East ~ 3
		Cell(int type);
};

Cell::Cell(int type):walls(4,0){
	this->type = type;
}

class Maze{
	public:
		int row; 
		int col;
		std::vector< std::vector<Cell> > cells;
		Maze(int row, int col, LCG&);
		vector<int> startPos; 
		vector<int> stopPos;
		void printMaze();
		void updateMaze(int,LCG&);
	private:
		void buildCells();
		void pickStartStopPos(LCG&);
		void randWallOpen(LCG&);
};
Maze::Maze(int row, int col, LCG &lcg):cells(row, vector<Cell>(col,Cell(0))),startPos(2,0),stopPos(2,0){
	this->row = row;
	this->col = col;
	buildCells();
	pickStartStopPos(lcg);
	randWallOpen(lcg);
}
void Maze::updateMaze(int posibility, LCG &lcg){
	for(int i = 1; i < row - 1; i++){
		for(int j = 1; j < col -1; j++){
			for(int k = 0; k < 4; k++){
				int tmp = lcg.rand(100);
				if( tmp < posibility ){//build wall
	            	(cells[i][j].walls)[k] = 0;
					if(k == 0){
						(cells[i-1][j].walls)[1] = 0;
					}else if(k == 1){
						(cells[i][j+1].walls)[0] = 0;
					}else if(k == 2){
						(cells[i+1][j].walls)[3] = 0;
					}else if(k == 3){
						(cells[i][j-1].walls)[2] = 0;
					}
				}else if( tmp >= posibility ){//remove wall
	            	(cells[i][j].walls)[k] = 1;
					if(k == 0){
						(cells[i-1][j].walls)[1] = 1;
					}else if(k == 1){
						(cells[i][j+1].walls)[0] = 1;
					}else if(k == 2){
						(cells[i+1][j].walls)[3] = 1;
					}else if(k == 3){
						(cells[i][j-1].walls)[2] = 1;
					}
				}
			}
		}
	}
}
void Maze::randWallOpen(LCG &lcg){
	for(int i = 1; i < row -1; i++){
		for(int j = 1; j < col -1; j++){
			int tmp = lcg.rand(4);
            (cells[i][j].walls)[tmp-1] = 1;

			if(tmp == 1){
				(cells[i-1][j].walls)[1] = 1;
			}else if(tmp == 2){
				(cells[i][j+1].walls)[0] = 1;
			}else if(tmp == 3){
				(cells[i+1][j].walls)[3] = 1;
			}else if(tmp == 4){
				(cells[i][j-1].walls)[2] = 1;
			}
        }
	}
}
void Maze::pickStartStopPos(LCG &lcg){
	int start, stop;
	do{
		start = lcg.rand(2 * (col - 2) + 2 * (row - 2) );
		stop = lcg.rand(2 * (col - 2) + 2 * (row - 2) );
	}while(start == stop);

	int count = 1;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(cells[i][j].type == 1){
				if(count == stop) {
					cells[i][j].spec = 1;
					stopPos[0] = i;
					stopPos[1] = j;
					if(i == 0){
						(cells[i][j].walls)[0] = 1;
					}else if(i == row -1){
						(cells[i][j].walls)[1] = 1;
					}else if(j == 0){
						(cells[i][j].walls)[2] = 1;
					}else if(j == col-1){
						(cells[i][j].walls)[3] = 1;
					}

				}
				else if(count == start) {
					cells[i][j].spec = 2;
					startPos[0] = i;
					startPos[1] = j;
					//if(i == 0){
                    //	(cells[i][j].walls)[1] = 1;
                    //}else if(i == row -1){
                    //	(cells[i][j].walls)[1] = 1;
                    //}else if(j == 0){
                    //	(cells[i][j].walls)[1] = 1;
                    //}else if(j == col-1){
                    //	(cells[i][j].walls)[1] = 1;
                    //}
				} 
				count++;
			}
		}
	}
}
void Maze::buildCells(){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			Cell tmp(1);
			if( (i == 0 && j == 0) || (i == 0 && j == col-1) || (i == row-1 && j == 0) || (i == row-1 && j == col-1) ){//corner
				tmp.type = 0;
			}else if( (i == 0 && j != 0) && (i == 0 && j != col-1) ){// border cell on north 
				tmp.type = 1;
			}else if( (i != 0 && j == 0) && (i != row-1 && j == 0) ){// border cell on west 
				tmp.type = 1;
			}else if( (i != 0 && j == col-1) && (i != row-1 && j == col-1) ){// border cell on east
				tmp.type = 1;
			}else if( (i == row-1 && j != 0) && (i == row-1 && j != col-1) ){// border cell on north 
				tmp.type = 1;
			}else{//inner cell
				tmp.type = 2;	
			}
			cells[i][j]=tmp;
		}
	}
}

void Maze::printMaze(){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if( (cells[i][j].walls)[0] == 0 ){
				 cout << "   -  ";
			}
		}
		cout << "\n";
		for(int j = 0; j < col; j++){
			if( (cells[i][j].walls)[2] == 0 ){
			   if(startPos[0] == i && startPos[1] == j) cout << " | ~";
			   else{ cout << " | ";}
			}else{
			   if(startPos[0] == i && startPos[1] == j) cout << "   1";
			   else{ cout << "    ";}
			}
			if( (cells[i][j].walls)[3] == 0 ){
			   cout << " | ";
			}else{
			   cout << "   ";
			}
		}
		cout << "\n";
		for(int j = 0; j < col; j++){
			if( (cells[i][j].walls)[1] == 0 ){
			    cout << "   -  ";
			}
		}
		cout << "\n";
		cout << "\n";
	}
}
class Robot{
	public:
		vector<int> startPos;
		vector<int> currentPos;
		int orien;//orientation
		Robot(vector<int> startPos);
		void makeTurn();
		void makeMove();
		bool checkRightWall(Maze&);
		bool checkFrontWall(Maze&);
};
Robot::Robot(vector<int> startPos){
	this->startPos = startPos;
	this->currentPos = startPos;
	this->orien = 3;
}
void Robot::makeMove(){
	if(this->orien == 0){
		this->currentPos[0] = this->currentPos[0] -1;
	}else if(this->orien == 1){
		this->currentPos[0] = this->currentPos[0] +1;
	}else if(this->orien == 2){
		this->currentPos[1] = this->currentPos[1] -1;
	}else if(this->orien == 3){
		this->currentPos[1] = this->currentPos[1] +1 ;
	}

}
// return true if open
bool Robot::checkRightWall(Maze &maze){
	if(this->orien == 0){
		 return (maze.cells[this->startPos[0]][this->startPos[1]].walls)[3] == 1;
	}else if(this->orien == 1){
		 return (maze.cells[this->startPos[0]][this->startPos[1]].walls)[2] == 1;
	}else if(this->orien == 2){
		 return (maze.cells[this->startPos[0]][this->startPos[1]].walls)[0] == 1;
	}else if(this->orien == 3){
		 return (maze.cells[this->startPos[0]][this->startPos[1]].walls)[1] == 1;
	}else{
		return false;
	}
}
// return true if open
bool Robot::checkFrontWall(Maze & maze){
	 return (maze.cells[this->currentPos[0]][this->currentPos[1]].walls)[this->orien] == 1;
}
void Robot::makeTurn(){
	switch (this->orien){
		case 0:
			this->orien = 3;
			break;
		case 1:
			this->orien = 2;
			break;
		case 2:
			this->orien = 0;
			break;
		case 3:
			this->orien = 1;
			break;
	}
}

int main(int argc, char** argv){
	//int seed = atoi(argv[1]);//random number generator seed
	//int M = atoi(argv[2]);//row of maze
	//int N = atoi(argv[3]);//col of maze
	//int possibility = atoi(argv[4]);
	//int maxMoves = atoi(argv[5]);
	// int seed, M, N, possibility, maxMoves;
	// cout << "Seed: ";
	// cin >> seed;
	// cout << "M: ";
	// cin >> M;
	// cout << "N: ";
	// cin >> N;
	// cout << "Possibility: ";
	// cin >> possibility;
	// cout << "Maximum Moves: ";
	// cin >> maxMoves;

	int seed = 999; int M = 10; int N = 10; int possibility = 50; int maxMoves = 1000;
	LCG lcg(seed);
	Maze maze(M,N,lcg);
	bool success = false; 
	bool fail = false;
	Robot robot(maze.startPos);
	int moves = 0;
	while(!(success || fail)){
		if( (robot.currentPos[0] == (maze.stopPos)[0]) && (robot.currentPos[1] == (maze.stopPos)[1])){
			success = true;
			break;
		} else if( moves >= maxMoves){
			fail = true;
			break;
		}
		//maze.printMaze();
		//getchar();
		//std::cout << "Current Orientation: " << robot.orien << std::endl;
		//std::cout << "Current Position: " << robot.currentPos[0]<< " "  << robot.currentPos[1]<< std::endl;
		//std::cout << "Goal Position: " << (maze.stopPos)[0]<< " "  << (maze.stopPos)[1]<< std::endl;
		if( robot.checkRightWall(maze) ){//if right wall is open
			robot.makeTurn();
		}else if( robot.checkFrontWall(maze) ){//if front is open
			robot.makeMove();
		}else{
			robot.makeTurn();
		}
		moves++;
		maze.updateMaze(possibility,lcg);
	}
	if( success ){
		cout << "Robbie got our of the maze in "<< moves << " moves" << endl;
	}else if(fail){
		cout << "Robbie was trapped in the maze" << endl;
	}
	return 0;
}
