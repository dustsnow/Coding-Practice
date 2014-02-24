#include <math.h>
#include "lcg.h"
#include <vector>
#include <iostream>
using namespace std;

class Cell{
	public:
		int type;//type: Corner ~ 0; Border ~ 1; Inner Cell ~2;
		int spec;//spec: none ~ 0; stop ~ 1; start ~ 2;
		std::vector<int> walls;//4 walls order: North at index 0, East ~ 1, S ~ 2, W ~ 3
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
				if( tmp < posibility ){//have wall
	            	(cells[i][j].walls)[k] = 0;
					if(k == 0){
						(cells[i-1][j].walls)[2] = 0;
					}else if(k == 1){
						(cells[i][j+1].walls)[3] = 0;
					}else if(k == 2){
						(cells[i+1][j].walls)[0] = 0;
					}else if(k == 3){
						(cells[i][j-1].walls)[1] = 0;
					}
				}else if( tmp >= posibility ){//remove wall
	            	(cells[i][j].walls)[k] = 1;
					if(k == 0){
						(cells[i-1][j].walls)[2] = 1;
					}else if(k == 1){
						(cells[i][j+1].walls)[3] = 1;
					}else if(k == 2){
						(cells[i+1][j].walls)[0] = 1;
					}else if(k == 3){
						(cells[i][j-1].walls)[1] = 1;
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
				(cells[i-1][j].walls)[2] = 1;
			}else if(tmp == 2){
				(cells[i][j+1].walls)[3] = 1;
			}else if(tmp == 3){
				(cells[i+1][j].walls)[0] = 1;
			}else if(tmp == 4){
				(cells[i][j-1].walls)[1] = 1;
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
						(cells[i][j].walls)[2] = 1;
					}else if(j == 0){
						(cells[i][j].walls)[3] = 1;
					}else if(j == col-1){
						(cells[i][j].walls)[1] = 1;
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
			if( (cells[i][j].walls)[3] == 0 ){
			   cout << " |" << (cells[i][j].type);
			}else{
			   cout << "  " << (cells[i][j].type); 
			}
			if( (cells[i][j].walls)[1] == 0 ){
			   cout << " | ";
			}else{
			   cout << "   ";
			}
		}
		cout << "\n";
		for(int j = 0; j < col; j++){
			if( (cells[i][j].walls)[2] == 0 ){
			    cout << "   -  ";
			}
		}
		cout << "\n";
		cout << "\n";
	}
}
