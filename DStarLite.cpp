#include <stdio.h>
#include <vector>
#include <malloc.h>
#include <assert.h>
#include <algorithm>    
#include <iostream>
#include <stdlib.h>     /* calloc, exit, free */
#include <math.h>

#include "DStarLite.h"
#include "gridworld.h"
#include "globalVariables.h"

DStarLite::DStarLite(int rows_, int cols_){
		rows = rows_;
	    cols = cols_;
	 
		 //Allocate memory 
		 maze.resize(rows);
		 for(int i=0; i < rows; i++){
		   maze[i].resize(cols);
		 }
}

void DStarLite::initialise(int startX, int startY, int goalX, int goalY){
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   maze[i][j].g = INF;
			maze[i][j].rhs = INF;
			for(int k = 0; k < DIRECTIONS; k++) {
				maze[i][j].move[k] = 0;
				maze[i][j].predecessor[k] = 0;
				if(k == NORTH || k == EAST || k == WEST || k == SOUTH  )
				{
					maze[i][j].linkCost[k] = 1;	
				}
				else
				{
					maze[i][j].linkCost[k] = 1.414;
				}
				
				
	}
			}
		}
		//---------------------
	start = &maze[startY][startX];
	goal = &maze[goalY][goalX];
	
	goal->rhs = 0.0;
	U.clear();
	calcKey(goal);
	AddToProrityQueue(goal);
	
	//for debugging only
	//~ for(int i=0; i < rows; i++){
	   //~ for(int j=0; j < cols; j++){
		   //~ //cout << maze[i][j].g << ", ";
			//~ cout << maze[i][j].rhs << ", ";
			
		//~ }
		//~ cout << endl;
	//~ }
	
}
	/*if (cell.y == 0) {
		cell->move[NORTH] = 0;
		cell->move[NORTHEAST] = 0;
		cell->move[SOUTHWEST] = 0;
		cell->move[WEST] = 0;
		cell->move[NORTHWEST] = 0;
		if (cell.x == cols){
			cell->move[EAST] = 0;
			}
		else {
			if (maze[cell->y][cell->x+1]->type == 0) {
				cell->move[EAST] = maze[cell->y][cell->x+1];
				}
			}
			else {
				cell->move[EAST] = 0;
				}
		if (j == cols || i == rows) {
			cell->move[SOUTHEAST] = 0;
			}
		else {
			if (cell->type == 0) {
				cell->move[SOUTHEAST] = maze[cell->y+1][cell->x+1];
				}
				}
		if (i == rows) {
			cell->move[SOUTH] = 0;
			}
		else {
			if (cell->type == 0) {
				cell->move[SOUTH] = maze[cell->y+1][cell->x];
			}
		}
		}
}
*/
void DStarLite::SetSuccessors(LpaStarCell *cell){
	if (cell->y == 0) 
	{
		cell->move[NORTH] = 0;
	}
	else 
	{
		if (maze[cell->y-1][cell->x].type != '1') {
			cell->move[NORTH] = &maze[cell->y-1][cell->x];
		}
		else
		{
			cell->move[NORTH] = 0;
		}
	}
	if(cell->y <= 0 || cell->x == cols -1) 
		{
		cell->move[NORTHEAST] = 0;
		}
	else
	{
		if (maze[cell->y-1][cell->x+1].type != '1') 
			{
			cell->move[NORTHEAST] = &maze[cell->y-1][cell->x+1];
			}
		else 
			{
			cell->move[NORTHEAST] = 0;
			}
	}
	if (cell->x == cols -1)
	{
		cell->move[EAST] = 0;
	}
	else 
	{
		if ((maze[cell->y][cell->x+1].type) != '1') 
		{	
			cell->move[EAST] = &maze[cell->y][cell->x+1];
		}
		else 
			{
			cell->move[EAST] = 0;
			}
	}
	if (cell->y == rows-1 || cell->x == cols-1) 
	{
		cell->move[SOUTHEAST] = 0;
	}
	else
	{
		if (maze[cell->y+1][cell->x+1].type != '1') 
		{
			cell->move[SOUTHEAST] = &maze[cell->y+1][cell->x+1];
		}
		else 
		{
			cell->move[SOUTHEAST] = 0;
		}
	}
	if (cell->y == rows-1) 
		{
		cell->move[SOUTH] = 0;
		}
	else 
	{
		if (maze[cell->y+1][cell->x].type != '1')
			{
			cell->move[SOUTH] = &maze[cell->y+1][cell->x];
			}
		else 
		{
			cell->move[SOUTH] = 0;
		}
	}
	if (cell->y == rows-1 || cell->x <= 0 )
		{
		cell->move[SOUTHWEST] = 0;
		}
	else 
	{
		if(maze[cell->y+1][cell->x-1].type != '1') 
			{
			cell->move[SOUTHWEST] = &maze[cell->y+1][cell->x-1];
			}
		else 
		{
			cell->move[SOUTHWEST] = 0;
		}
	}
	if(cell->x <= 0)
		{
		cell->move[WEST] = 0;
		}
	else
	{
		if (maze[cell->y][cell->x-1].type != '1') 
			{
			cell->move[WEST] = &maze[cell->y][cell->x-1];
			}
		else{
			cell->move[WEST] = 0;
		}
	}
	if(cell->y <= 0 || cell->x <= 0) 
		{
		cell->move[NORTHWEST] = 0;
		}
	else 
	{
		if (maze[cell->y-1][cell->x-1].type != '1')
			{
			cell->move[NORTHWEST] = &maze[cell->y-1][cell->x-1];
			}
		else
		{
			cell->move[NORTHWEST] = 0;
		}
	}
}

/*
void DStarLite::SetPredecessors(LpaStarCell *cell){
	if (cell->y == 0) 
	{
		cell->predecessor[NORTH] = 0;
	}
	else 
	{
		if (maze[cell->y-1][cell->x].type == '0' && cell->move[NORTH] == NULL) {
			cell->predecessor[NORTH] = &maze[cell->y-1][cell->x];
		}
		else
		{
			cell->predecessor[NORTH] = 0;
		}
	}
	if(cell->y <= 0 || cell->x == cols -1) 
		{
		cell->predecessor[NORTHEAST] = 0;
		}
	else
	{
		if (maze[cell->y-1][cell->x+1].type == '0' && cell->move[NORTHEAST] == NULL) 
			{
			cell->predecessor[NORTHEAST] = &maze[cell->y-1][cell->x+1];
			}
		else 
			{
			cell->predecessor[NORTHEAST] = 0;
			}
	}
	if (cell->x == cols -1)
	{
		cell->predecessor[EAST] = 0;
	}
	else 
	{
		if ((maze[cell->y][cell->x+1].type) == '0' && cell->move[EAST] == NULL) 
		{	
			cell->predecessor[EAST] = &maze[cell->y][cell->x+1];
		}
		else 
			{
			cell->predecessor[EAST] = 0;
			}
	}
	if (cell->y == rows-1 || cell->x == cols-1) 
	{
		cell->predecessor[SOUTHEAST] = 0;
	}
	else
	{
		if (maze[cell->y+1][cell->x+1].type == '0' && cell->move[SOUTHEAST] == NULL) 
		{
			cell->predecessor[SOUTHEAST] = &maze[cell->y+1][cell->x+1];
		}
		else 
		{
			cell->predecessor[SOUTHEAST] = 0;
		}
	}
	if (cell->y == rows-1) 
		{
		cell->predecessor[SOUTH] = 0;
		}
	else 
	{
		if (maze[cell->y+1][cell->x].type == '0' && cell->move[SOUTH] == NULL)
			{
			cell->predecessor[SOUTH] = &maze[cell->y+1][cell->x];
			}
		else 
		{
			cell->predecessor[SOUTH] = 0;
		}
	}
	if (cell->y == rows-1 || cell->x <= 0 )
		{
		cell->predecessor[SOUTHWEST] = 0;
		}
	else 
	{
		if(maze[cell->y+1][cell->x-1].type == '0' && cell->move[SOUTHWEST] == NULL ) 
			{
			cell->predecessor[SOUTHWEST] = &maze[cell->y+1][cell->x-1];
			}
		else 
		{
			cell->predecessor[SOUTHWEST] = 0;
		}
	}
	if(cell->x <= 0)
		{
		cell->predecessor[WEST] = 0;
		}
	else
	{
		if (maze[cell->y][cell->x-1].type == '0' && cell->move[WEST] == NULL) 
			{
			cout << "setting west predecessor" << endl;
			cell->predecessor[WEST] = &maze[cell->y][cell->x-1];
			}
		else{
			cell->predecessor[WEST] = 0;
		}
	}
	if(cell->y <= 0 || cell->x <= 0) 
		{
		cell->predecessor[NORTHWEST] = 0;
		}
	else 
	{
		if (maze[cell->y-1][cell->x-1].type == '0' && cell->move[NORTHWEST] == NULL)
			{
			cell->predecessor[NORTHWEST] = &maze[cell->y-1][cell->x-1];
			}
		else
		{
			cell->predecessor[NORTHWEST] = 0;
		}
	}
}
*/



double DStarLite::minValue(double g_, double rhs_){
	if(g_ <= rhs_){
		return g_;
	} else {
		return rhs_;
	}	
}

int DStarLite::maxValue(int v1, int v2){
	
	if(v1 >= v2){
		return v1;
	} else {
		return v2;
	}	
}

double DStarLite::calc_H(int x, int y)
{
	
	int diffY = abs(start->y - y);
	int diffX = abs(start->x - x);
	
	//maze[y][x].h = (double)maxValue(diffY, diffX);
	return (double)maxValue(diffY, diffX);
}

void DStarLite::updateManhattonHValues()
{
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   maze[i][j].h = calc_H(j, i);
		}
	}
	
	start->h = calc_H(start->x, start->y);
	goal->h = calc_H(goal->x, goal->y);
}

double DStarLite::calc_EH(int x, int y)
{
	
	int diffY = abs(start->y - y);
	int diffX = abs(start->x - x);

	return sqrt(pow(diffY, 2) + pow(diffX, 2));
}

void DStarLite::updateEuclideanHValues () 
{
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   maze[i][j].h = calc_EH(j, i);
		}
	}
	
	start->h = calc_EH(start->x, start->y);
	goal->h = calc_EH(goal->x, goal->y);
}

void DStarLite::calcKey(int x, int y){
	double key1, key2;
	
	key2 = minValue(maze[y][x].g, maze[y][x].rhs);
	key1 = key2 + maze[y][x].h;
}


void DStarLite::calcKey(LpaStarCell *cell){
	double key1, key2;
	
	key2 = minValue(cell->g, cell->rhs);
	key1 = key2 + cell->h;
	
	cell->key[0] = key1;
	cell->key[1] = key2;
}

void DStarLite::updateAllKeyValues()
{	
	for(int i=0; i < rows; i++)
	{
	   for(int j=0; j < cols; j++)
	   {
		   calcKey(&maze[i][j]);
		}
	}
	
	calcKey(start);
	calcKey(goal);
}

//checkig highest priority of two cells, returns 1 if cell1 is higher priority than cell2, otherwise 0
int DStarLite::IsKeyLessThanOrEqual(LpaStarCell *cell1, LpaStarCell *cell2)
{
	if(cell1->key[0] < cell2->key[0]) 
	{
		return 1;
	}
	else if(cell1->key[0] == cell2->key[0] && cell1->key[1] <= cell2->key[1])
	{
		return 1;
	} 
	return 0;
}

void DStarLite::AddToProrityQueue(LpaStarCell *cell) 
{
	if (U.empty())
	{
		U.push_back(cell);
	}
	else 
	{
		vector<LpaStarCell *>::iterator ptr; 
		for (ptr = U.begin(); ptr != U.end(); ++ptr) 
		{
		
			if (IsKeyLessThanOrEqual(*ptr, cell) == 1) 
			{
				if (ptr == U.end())
				{
					U.push_back(cell);
					break;
				}
				else
				{
					U.insert(ptr,cell);
					break;
				}
			} 
		}
		if (ptr == U.end()) {
			U.push_back(cell);
		}

	}
	vector<LpaStarCell *>::iterator ptr2; 
	for (ptr2 = U.begin(); ptr2 != U.end(); ++ptr2) { 
		//cout << "iterator ptr 2 " << (*ptr2)->y << "," << (*ptr2)->x << endl;
	}
	if (U.size() > max_queue_length) {
		max_queue_length = U.size();
	}
}
int DStarLite:: getOppositeDirection(int direction) {
	if (direction < 4) {
		return direction + 4;
	}
	else {
		return direction - 4;
	}
}


void DStarLite::SetPredecessors(LpaStarCell *cell)
{
	if (cell->y == 0) 
	{
		cell->predecessor[NORTH] = 0;
	}
	else 
	{
		if (maze[cell->y-1][cell->x].type != '1' )
	    {
			cell->predecessor[NORTH] = &maze[cell->y-1][cell->x];
		}
		else
		{
			cell->predecessor[NORTH] = 0;
		}
	}
	if(cell->y <= 0 || cell->x == cols -1) 
		{
		cell->predecessor[NORTHEAST] = 0;
		}
	else
	{
		if (maze[cell->y-1][cell->x+1].type != '1' ) 
			{
			cell->predecessor[NORTHEAST] = &maze[cell->y-1][cell->x+1];
			}
		else 
			{
			cell->predecessor[NORTHEAST] = 0;
			}
	}
	if (cell->x == cols -1)
	{
		cell->predecessor[EAST] = 0;
	}
	else 
	{
		if ((maze[cell->y][cell->x+1].type) != '1' ) 
		{	
			cell->predecessor[EAST] = &maze[cell->y][cell->x+1];
		}
		else 
			{
			cell->predecessor[EAST] = 0;
			}
	}
	if (cell->y == rows-1 || cell->x == cols-1) 
	{
		cell->predecessor[SOUTHEAST] = 0;
	}
	else
	{
		if (maze[cell->y+1][cell->x+1].type != '1' ) 
		{
			cell->predecessor[SOUTHEAST] = &maze[cell->y+1][cell->x+1];
		}
		else 
		{
			cell->predecessor[SOUTHEAST] = 0;
		}
	}
	if (cell->y == rows-1) 
		{
		cell->predecessor[SOUTH] = 0;
		}
	else 
	{
		if (maze[cell->y+1][cell->x].type != '1' )
			{
			cell->predecessor[SOUTH] = &maze[cell->y+1][cell->x];
			}
		else 
		{
			cell->predecessor[SOUTH] = 0;
		}
	}
	if (cell->y == rows-1 || cell->x <= 0 )
		{
		cell->predecessor[SOUTHWEST] = 0;
		}
	else 
	{
		if(maze[cell->y+1][cell->x-1].type != '1'  ) 
			{
			cell->predecessor[SOUTHWEST] = &maze[cell->y+1][cell->x-1];
			}
		else 
		{
			cell->predecessor[SOUTHWEST] = 0;
		}
	}
	if(cell->x <= 0)
		{
		cell->predecessor[WEST] = 0;
		}
	else
	{
		if (maze[cell->y][cell->x-1].type != '1' ) 
			{
			cell->predecessor[WEST] = &maze[cell->y][cell->x-1];
			}
		else{
			cell->predecessor[WEST] = 0;
		}
	}
	if(cell->y <= 0 || cell->x <= 0) 
		{
		cell->predecessor[NORTHWEST] = 0;
		}
	else 
	{
		if (maze[cell->y-1][cell->x-1].type != '1' )
			{
			cell->predecessor[NORTHWEST] = &maze[cell->y-1][cell->x-1];
			}
		else
		{
			cell->predecessor[NORTHWEST] = 0;
		}
	}
}



LpaStarCell* DStarLite:: getLowestKey(){

	vector<LpaStarCell *>::reverse_iterator ptr = U.rbegin() ; 
	return *ptr; 
 }

void DStarLite::AddToVector(LpaStarCell* cell , vector<LpaStarCell*>& v )
{
	vector<LpaStarCell*>::iterator it = v.begin();
		
	for( ; it != v.end();++it)
	{
		if(*it == cell )
		{
			break;
		}
	}
	if(it == v.end())
	{
		v.push_back(cell);
	}
}

void DStarLite:: UpdateVertex(LpaStarCell *cell) {
	double temprhs = cell->rhs;
	state_expansions = state_expansions + 1;
	if(cell != goal) {
		SetSuccessors(cell);
		for (int i = 0; i < DIRECTIONS; i++){
			vertex_count = vertex_count + 1;
			if (cell->move[i] != 0)
			{
				//predecessor value is set
				temprhs = sum(cell->move[i]->g, cell->linkCost[i]);
				if (temprhs < cell->rhs) {
					cell->rhs = temprhs;
					//cout <<"set rhs  " << cell->x << cell->y << cell->rhs <<',' << cell->g <<endl;
				}
			}
		}
		RemoveFromPriorityCell(cell);
		if (cell->g != cell->rhs)
		{
			calcKey(cell);
			AddToProrityQueue(cell);
		}
	}
}


bool DStarLite:: FindShortestPath()
{	
	vertex_count = 0;
	state_expansions = 0;
	max_queue_length = 0;

	while (U.empty() == false)
	{
	LpaStarCell *cell = getLowestKey(); //vertex with highest priority
	calcKey(start);
	if (IsKeyLessThanOrEqual(start, cell) == 0 || start->rhs != start->g) 
	{	
		U.pop_back();
		if (cell->g > cell->rhs) 
		{
		cell->g = cell->rhs;
		SetPredecessors(cell);
		for (int i = 0; i < DIRECTIONS; i++) 
			{
			//cout << "for i in directions" << endl;
			//cout << cell->move[i] << endl;
			if (cell->predecessor[i] != 0) 
				{
					
					SetSuccessors(cell->predecessor[i]);
					//cell->predecessor[i]->move[getOppositeDirection(i)] = cell;
					UpdateVertex(cell->predecessor[i]);
				}
			}
		}
	else 
		{
		cell->g = INF;
		SetPredecessors(cell);
		for (int i = 0; i < DIRECTIONS; i++){
			if(cell->predecessor[i] != NULL)
			{
			UpdateVertex(cell->predecessor[i]);
			}
		}
		UpdateVertex(cell);
		}
	}
	else 
		{
		break;

		}
}	
	cout << "Vertex accesses is equal to " << vertex_count << endl;
	cout << "Number of state expansions is " << state_expansions << endl;
	cout << "Max queue length is " << max_queue_length << endl;
	cout << "The path length is " << start->g << endl;
	return start->g != INF;
}


bool DStarLite::Replan(GridWorld* new_world)
{
	
	if(start != goal)
	{
		vector<LpaStarCell*> updatedNodes;
		for(int i=0; i < new_world->getGridWorldRows(); i++)
		{	
		for(int j=0; j < new_world->getGridWorldCols(); j++)
			{
				if (maze[i][j].type != new_world->getMapTypeValue(i,j))
				{	
					LpaStarCell* cell = &maze[i][j];
					cell->type = new_world->getMapTypeValue(i,j);
					cell->g = INF;
					cell->rhs = INF ;  

							
					SetSuccessors(cell);
					for(int k = 0; k< DIRECTIONS; k++)
					{	
						if (cell->move[k] != NULL) 
						{	
							if(cell->move[k] != goal)   
							{
								//cell->move[k]->rhs = INF;
								
								//cell->move[k]->predecessor[getOppositeDirection(k)] = cell;
								//SetPredecessors(cell->move[k]);
								cell->move[k]->rhs = INF;   
								cell->move[k]->g = INF;
							}
							
							//SetPredecessors(cell->move[k]);
							//AddToVector(cell->move[k],updatedNodes);
							
						}
					}
					AddToVector(cell,updatedNodes);
					//UpdateVertex(cell);
				}
			}
		}
    	if( false == updatedNodes.empty())
		{
			for( vector<LpaStarCell*>::iterator it = updatedNodes.begin() ; it != updatedNodes.end();++it)
			{
				LpaStarCell *cell = *it;
				UpdateVertex(cell);
			}
			updatedNodes.clear();
			while( false == U.empty())
			{
				 AddToVector( getLowestKey(),updatedNodes);
				 U.pop_back();
			}
            start->rhs = INF;
			start->g = INF;
			for( vector<LpaStarCell*>::iterator it = updatedNodes.begin() ; it != updatedNodes.end();++it)
			{
				LpaStarCell *cell = *it;
				calcKey(cell);
				AddToProrityQueue(cell);
			}
			FindShortestPath();
		}
		if(start->g != INF)
		{
			
			//move forward
			LpaStarCell* toMove = NULL;
			double lowestCost = INF;
			for( int i = 0; i < DIRECTIONS ; i++ )
			{
				if(start->move[i] != NULL && start->move[i]->g < lowestCost  )
				{
					toMove = start->move[i];
					lowestCost = toMove->g;
				}
			}
			if(toMove != NULL)
			{
				cout << "replan 3" << endl;
				if(start != NULL)
				{
					start->type = '0';
				}
				start = toMove;
                start->type = '6';
				vertex s = 	new_world->getStartVertex();
			    if( (s.row != -1) && (s.col != -1) )
				{
				//set current START VERTEX to an ordinary TRAVERSABLE CELL
					new_world->setMapTypeValue(s.row, s.col, '0'); 
					//new_world->initialiseMapConnections(); 
					//ok, proceed
				} 
				else
				{
					cout << "invalid START vertex" << endl;
					//break;
				}
			    updateManhattonHValues();

				new_world->setMapTypeValue(start->y, start->x,'6');
			    s.row = start->y;
				s.col = start->x;
				new_world->setStartVertex(s);
			}
		
		}
	}
	return start->g != INF;
}


void DStarLite:: RemoveFromPriorityCell(LpaStarCell *cell) {
	for (vector<LpaStarCell *>::iterator it = U.begin(); it != U.end(); ++it){
		if (cell == *it) {
			U.erase(it);
			break;
		}
	}
}

double DStarLite:: sum(double a, double b){
		if(a == INF || b == INF){
			return INF;
		}else{
			return (a+b);
		}
    }

void DStarLite:: unitTesting()
{
	cout << "Calling unit testing" << endl;
	U.clear();
 	/*/aze[2][2].g = INF;
	maze[2][2].rhs = 0;
	maze[2][2].key[0] = 1;
	maze[2][2].key[1] = 1;
	//calcKey(&maze[2][2]);
	AddToProrityQueue(&maze[2][2]);
	cout << maze[2][2].key[0] << endl;
	cout << maze[2][2].key[1] << endl;
*/
	cout << "Calling unit testing" << endl;
	maze[2][1].g = INF;
	maze[2][1].rhs = 1;
	maze[2][1].key[0] = 2;
	maze[2][1].key[1] = 2;
	//calcKey(&maze[2][1]);
	AddToProrityQueue(&maze[2][1]);
	cout << maze[2][1].key[0] << endl;
	cout << maze[2][2].key[1] << endl;

	maze[2][2].g = INF;
	maze[2][2].rhs = 0;
	maze[2][2].key[0] = 1;
	maze[2][2].key[1] = 1;
	AddToProrityQueue(&maze[2][2]);

	int cell1 = IsKeyLessThanOrEqual(&maze[2][2], &maze[2][1]);
	cout << cell1 << endl;


	/*cout << "Calling unit testing" << endl;
	maze[2][0].g = INF;
	maze[2][0].rhs = 2;
	calcKey(&maze[2][0]);
	AddToProrityQueue(&maze[2][0]);
	cout << maze[2][0].key[0] << endl;
	cout << maze[2][2].key[1] << endl;

	cout << U[0]->y << U[0]->x << endl;
	cout << U[1]->y << U[1]->x << endl;
	cout << U[2]->y << U[2]->x << endl;*/

	LpaStarCell* cell =  getLowestKey();
	cout << "results = " << cell->y << "," << cell->x << endl;
}