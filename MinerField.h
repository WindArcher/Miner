#pragma once
#include <vector>
#include <iostream>
#include <list>
using namespace std;

class MinerField
{
	int FIELD_NUM;
	bool Created=false;
	vector < vector<int>> gridLogic;
	void SetUpBombs();
	void OpenVoidCells(vector<vector<int>>&,int,int);
	//list<int> SafeZone;
	void SetUpNumbers();
public:
	bool IsCreated();
	void CreateField();
	void CreateFieldwithEntryPoint(int, int);
	void OpenCell(vector<vector<int>>&,int x,int y);
	MinerField(int);
	~MinerField();

};

