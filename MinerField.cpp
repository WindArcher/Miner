#include "MinerField.h"
MinerField::MinerField(int m_size) :FIELD_NUM(m_size), gridLogic(FIELD_NUM+2, vector<int>(FIELD_NUM+2,-1))
{
	
}
MinerField::~MinerField()
{

}

void MinerField::CreateField()
{
	SetUpBombs();
	SetUpNumbers();
	Created = true;
}
void MinerField::OpenCell(vector<vector<int>>& view, int x, int y)
{
	
	if (gridLogic[x][y] == 9)
	{
		for (int i = 1; i <= FIELD_NUM; i++)
			for (int j = 1; j <= FIELD_NUM; j++)
			{
				view[i][j] = gridLogic[i][j];
			}
	}
	else {
		if (gridLogic[x][y] == 0)
			OpenVoidCells(view, x, y);
		else
		view[x][y] = gridLogic[x][y];
	}
}
bool MinerField::IsCreated()
{
	return this->Created;
}
void MinerField::SetUpBombs()
{
	for (int i = 1; i <= FIELD_NUM; i++)
		for (int j = 1; j <= FIELD_NUM; j++)
		{
			if (rand() % 8 == 0)gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;

		}
}
void MinerField::SetUpNumbers()
{
	for (int i = 1; i <= FIELD_NUM; i++)
		for (int j = 1; j <= FIELD_NUM; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}
}
void MinerField::OpenVoidCells(vector<vector<int>>& view, int x, int y)
{
	if (x >= (FIELD_NUM + 2) || y >= (FIELD_NUM + 2))
		return;
	if (gridLogic[x][y] == 10 || gridLogic[x][y]==11 )
		return;
	if ((gridLogic[x][y] <= 8) && (gridLogic[x][y] >= 1))
	{
		view[x][y] = gridLogic[x][y];
		return;
	}
	view[x][y] = gridLogic[x][y];
	OpenVoidCells(view,x + 1, y); //North;
	OpenVoidCells(view,x - 1, y); //South
	OpenVoidCells(view,x, y + 1); //East
	OpenVoidCells(view, x, y - 1); //West

	OpenVoidCells(view, x - 1, y - 1); //South-West
	OpenVoidCells(view, x + 1, y + 1);	//North-East
	OpenVoidCells(view, x - 1, y + 1);	//South-East
	OpenVoidCells(view, x + 1, y - 1);	//North-West
}
void MinerField::CreateFieldwithEntryPoint(int x, int y)
{
	do {
		SetUpBombs();
	}while(gridLogic[x][y]==9);
	SetUpNumbers();
	Created = true;
}