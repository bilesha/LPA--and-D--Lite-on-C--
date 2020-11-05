#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* calloc, exit, free */
#include <math.h>  //sqrt, pow

#include "LPAstar.h"
#include "gridworld.h"


 LpaStar::LpaStar(int rows_, int cols_){
		rows = rows_;
	    cols = cols_;
	 
		 //Allocate memory 
		 maze.resize(rows);
		 for(int i=0; i < rows; i++){
		   maze[i].resize(cols);
		 }
}

void LpaStar::initialise(int startX, int startY, int goalX, int goalY){
	for(int i=0; i < rows; i++)
	{
	   for(int j=0; j < cols; j++)
	   {
		   	maze[i][j].g = INF;
			maze[i][j].rhs = INF;
			for(int k = 0; k < DIRECTIONS; k++) 
			{
				maze[i][j].move[k] = 0;
				maze[i][j].predecessor[k] = 0;
				if(k == NORTH || k == EAST || k == SOUTH || k == WEST )
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
	
	start->rhs = 0.0;
	U.clear();
	AddToProrityQueue(start);
	//maze[startY][startX].g = goal->g;
	//maze[goal->y][startX].rhs = goal->rhs;
	calcKey(start);
	//AddToProrityQueue(start);
	//---------------------
	
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
void LpaStar::SetSuccessors(LpaStarCell *cell){
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

void LpaStar::SetPredecessors(LpaStarCell *cell){
	if (cell->y == 0) 
	{
		cell->predecessor[NORTH] = 0;
	}
	else 
	{
		if (maze[cell->y-1][cell->x].type != '1' ) {
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
		if (maze[cell->y-1][cell->x+1].type != '1') 
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
		if ((maze[cell->y][cell->x+1].type) != '1') 
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
		if (maze[cell->y+1][cell->x+1].type != '1') 
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
		if (maze[cell->y-1][cell->x-1].type != '1')
			{
			cell->predecessor[NORTHWEST] = &maze[cell->y-1][cell->x-1];
			}
		else
		{
			cell->predecessor[NORTHWEST] = 0;
		}
	}
}


double LpaStar::minValue(double g_, double rhs_){
	if(g_ <= rhs_){
		return g_;
	} else {
		return rhs_;
	}	
}

int LpaStar::maxValue(int v1, int v2){
	
	if(v1 >= v2){
		return v1;
	} else {
		return v2;
	}	
}

double LpaStar::calc_H(int x, int y){
	
	int diffY = abs(goal->y - y);
	int diffX = abs(goal->x - x);
	
	//maze[y][x].h = (double)maxValue(diffY, diffX);
	return (double)maxValue(diffY, diffX);
}

void LpaStar::updateManhattonHValues(){
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   maze[i][j].h = calc_H(j, i);
		}
	}
	
	start->h = calc_H(start->x, start->y);
	goal->h = calc_H(goal->x, goal->y);
}

double LpaStar::calc_EH(int x, int y)
{
	
	int diffY = abs(start->y - y);
	int diffX = abs(start->x - x);
	
	return sqrt(pow(diffY, 2) + pow(diffX, 2));

}
void LpaStar::updateEuclideanHValues () {
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   maze[i][j].h = calc_EH(j, i);
		}
	}
	
	start->h = calc_EH(start->x, start->y);
	goal->h = calc_EH(goal->x, goal->y);
}
void LpaStar::calcKey(int x, int y){
	double key1, key2;
	
	key2 = minValue(maze[y][x].g, maze[y][x].rhs);
	key1 = key2 + maze[y][x].h;
}


void LpaStar::calcKey(LpaStarCell *cell){
	double key1, key2;
	
	key2 = minValue(cell->g, cell->rhs);
	key1 = key2 + cell->h;
	
	cell->key[0] = key1;
	cell->key[1] = key2;
}

void LpaStar::updateAllKeyValues(){	
	for(int i=0; i < rows; i++){
	   for(int j=0; j < cols; j++){
		   calcKey(&maze[i][j]);
		}
	}
	
	calcKey(start);
	calcKey(goal);
}

//checkig highest priority of two cells, returns 1 if cell1 is higher priority than cell2, otherwise 0
int LpaStar::IsKeyLessThanOrEqual(LpaStarCell *cell1, LpaStarCell *cell2){
	if(cell1->key[0] < cell2->key[0]) {
		return 1;
	}
	else if(cell1->key[0] == cell2->key[0] && cell1->key[1] <= cell2->key[1]){
		return 1;
	} 
	return 0;
}

void LpaStar::AddToProrityQueue(LpaStarCell *cell) 
{
	if (U.empty())
	{
		U.push_back(cell);
	}
	else {
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
	if (U.size() > max_queue_length) {
		max_queue_length = U.size();
	}
}
int LpaStar:: getOppositeDirection(int direction) {
	if (direction < 4) {
		return direction + 4;
	}
	else {
		return direction - 4;
	}
}
void LpaStar:: UpdateVertex(LpaStarCell *cell) {	
	double temprhs = cell->rhs;
	state_expansions = state_expansions + 1;
	if(cell != start) {
		for (int i = 0; i < DIRECTIONS; i++){
			vertex_count = vertex_count + 1;
			if (cell->predecessor[i] != 0){
				//predecessor value is set
				temprhs = sum(cell->predecessor[i]->g, cell->linkCost[i]);
				if (temprhs < cell->rhs) {
					cell->rhs = temprhs;
				}
			}
		}
		RemoveFromPriorityCell(cell);
		if (cell->g != cell->rhs){
			calcKey(cell);
			AddToProrityQueue(cell);
		}
	}
}

bool LpaStar::FindShortestPath()
{
	cout << "1,1 type = " <<  maze[1][1].type << endl;
	vertex_count = 0;
	state_expansions = 0;
	max_queue_length = 0;

	while (U.empty() == false)
	{
		vector<LpaStarCell *>::reverse_iterator ptr = U.rbegin() ; 
		LpaStarCell *cell = *ptr; //vertex with highest priority
		calcKey(goal);
		if (IsKeyLessThanOrEqual(goal, cell) == 0 || goal->rhs != goal->g) 
		{	
			U.pop_back();
			if (cell->g > cell->rhs) 
			{
		
				cell->g = cell->rhs;
				SetSuccessors(cell);
				//cout << "successors set" << endl;
				for (int i = 0; i < DIRECTIONS; i++) 
				{
					//cout << "for i in directions" << endl;
					//cout << cell->move[i] << endl;
					if (cell->move[i] != 0) 
					{
						SetPredecessors(cell->move[i]);
						//cell->move[i]->predecessor[getOppositeDirection(i)] = cell;
						UpdateVertex(cell->move[i]);
					}
				}
			}
			else 
			{
				cell->g = INF;
				SetSuccessors(cell);
				for (int i = 0; i < DIRECTIONS; i++)
				{
					if(cell->move[i] != NULL) 
					{
						UpdateVertex(cell->move[i]);
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
	cout << "The path length is " << goal->g << endl;
	return goal->g != INF;		
}

void AddToVector(LpaStarCell* cell , vector<LpaStarCell*>& v )
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

bool LpaStar:: ReplanPath(GridWorld* new_world)
{	
	cout << "++++++++++++++++++++++++++ replaning";
	cout << "getGridWorldRows = " << new_world->getGridWorldRows() << endl;
	cout << "getGridWorldCols = " << new_world->getGridWorldCols() << endl;

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

				cout<< "GOAL" << maze[2][2].type << endl ;
		
				SetSuccessors(cell);
	   			for(int k = 0; k< DIRECTIONS; k++)
	   			{	
	   				if (cell->move[k] != NULL) 
	   				{	
						if(cell->move[k] != start)   
						{
							cell->move[k]->rhs = INF;
							cell->move[k]->g = INF;
							cell->move[k]->predecessor[getOppositeDirection(k)] = cell;
							AddToVector(cell->move[k],updatedNodes);   
						}
	   					//UpdateVertex(cell->move[k]);
	   				}
	   			}
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
		FindShortestPath();
	}
	return goal->g != INF;
}

void LpaStar:: RemoveFromPriorityCell(LpaStarCell *cell) {
	for (vector<LpaStarCell *>::iterator it = U.begin(); it != U.end(); ++it){
		if (cell == *it) {
			U.erase(it);
			break;
		}
	}
}

double LpaStar:: sum(double a, double b){
		if(a == INF || b == INF){
			return INF;
		}else{
			return (a+b);
		}
    }

void LpaStar:: unitTesting()
{
	cout << "Calling unit testing" << endl;
	cout << maze[0][1].type << endl;
	cout << maze[0][1].y << endl;
	cout << maze[0][1].x << endl;
	cout << maze[0][1].g << endl;
	cout << maze[0][1].rhs <<endl;

	cout << "Calling unit testing" << endl;
	cout << maze[1][1].type << endl;
	cout << maze[1][1].y << endl;
	cout << maze[1][1].x << endl;
	cout << maze[1][1].g << endl;
	cout << maze[1][1].rhs <<endl;

}

