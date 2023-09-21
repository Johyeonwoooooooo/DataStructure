//--------------------------------------------------------------------
//
//  Laboratory 13                                          wtgraph.cpp
//
//  Implementation of the Weighted Graph ADT
//
//--------------------------------------------------------------------
#include "wtgraph.h"

//--------------------------------------------------------------------

WtGraph::WtGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize * maxSize];
	for (int i = 0; i < maxSize * maxSize; i++)
		adjMatrix[i] = infiniteEdgeWt;

#if INLAB1
	pathMatrix = new int [maxSize * maxSize];
#endif
}

WtGraph::~WtGraph()
{
	delete[] vertexList;
	delete[] adjMatrix;

#if INLAB1
	delete[] pathMatrix;
#endif
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)
{
	int finded_index = -1;

	for (int i = 0; i < size; i++)
	{
		if (strcmp(vertexList[i].label, v) == 0)
			finded_index = i;
	}

	return finded_index;
}

int WtGraph::getEdge(int row, int col)
{
	return adjMatrix[size * row + col];
}

void WtGraph::setEdge(int row, int col, int wt) 
{
	adjMatrix[size * row + col] = wt;
}

//--------------------------------------------------------------------

void WtGraph::insertVertex(Vertex newVertex)
{
	if (isFull())
	{
		cout << "Error : Full Graph" << endl;
	}
	else
	{
		if (getIndex(newVertex.label) == -1)
		{
			vertexList[size] = newVertex;
			for (int i = size - 1; i > 0; i--) // 대칭을 유지한체로 이동시킨다. 행에 따라 움직이는 값이 (행 -1) 으로 정해져있기에
			{                          
				for (int j = size - 1; j >= 0; j--)  //  해당인덱스에 큰 것 부터 바꾼다
				{
					adjMatrix[i * size + j + i] = adjMatrix[i * size + j];
				}
			}

			size++;

			for (int i = 0; i < size; i++)                // 새로 추가된 열을 초기화 한다.
				adjMatrix[(i + 1) * size - 1] = infiniteEdgeWt;
		}
		else
		{
			int index = getIndex(newVertex.label);
			vertexList[index] = newVertex;
		}
	}
}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
	int v1_index = getIndex(v1);
	int v2_index = getIndex(v2);

	if (v1_index != -1 && v2_index != -1)
	{
		setEdge(v1_index, v2_index, wt);
		setEdge(v2_index, v1_index, wt);
	}
	else
	{
		cout << "Error : Can't find Vertex" << endl;
	}
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
	bool result = false;
	if (getIndex(v) != -1)
	{
		result = true;
		int index = getIndex(v);
		vData = vertexList[index];
	}
	return  result;
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
	bool result = false;
	int v1_index = getIndex(v1);
	int v2_index = getIndex(v2);

	if (v1_index != -1 && v2_index != -1)
	{
		if (getEdge(v1_index, v2_index) != infiniteEdgeWt)
		{
			result = true;
			wt = getEdge(v1_index, v2_index);
		}
	}
	return result;
}

//--------------------------------------------------------------------

void WtGraph::removeVertex(char* v)
{
	if (isEmpty())
	{
		cout << "Error : Empty Graph" << endl;
	}
	else
	{
		int index = getIndex(v);
		if (index == -1)
		{
			cout << "Error : Can't find Vertex" << endl;
		}
		else
		{
			int mov = 0;  // 이동할 거리
			for (int i = 0; i < size; i++) // 해당 인덱스에 해당하는 행,열을 삭제함
			{
				setEdge(index, i, infiniteEdgeWt); 
				setEdge(i, index, infiniteEdgeWt);
			}
						
			
			for (int i = 0; i < size * size; i++)
			{
				if ((index * size <= i && i < (index + 1) * size) || i % size == index) // 나머지가 index일때 (열), index *size 일때(행) 나오면 한번씩 밀어야 하기에
					mov++;                                                              // 나오면 이동할 길이 + 1
				else
				{
					adjMatrix[i - mov] = adjMatrix[i];   // 이동할 길이를 뺀 인덱스로 이동
				}
			}

			for (int i = (size - 1) * (size - 1); i < size * size; i++)  // 줄어든 부분 초기화하기
				adjMatrix[i] = infiniteEdgeWt;

			for (int i = index; i < size; i++)
				vertexList[i] = vertexList[i + 1];

			size--;
		}
	}
}

void WtGraph::removeEdge(char* v1, char* v2)
{
	int v1_index = getIndex(v1);
	int v2_index = getIndex(v2);
	if (v1_index == -1 || v2_index == -1)
	{
		cout << "Error : Can't find Vertex" << endl;
	}
	else
	{
		setEdge(v1_index, v2_index, infiniteEdgeWt);
		setEdge(v2_index, v1_index, infiniteEdgeWt);
	}
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
	size = 0;
	for (int i = 0; i < maxSize * maxSize; i++)
		adjMatrix[i] = infiniteEdgeWt;
}

bool WtGraph::isEmpty() const
{
	if (size == 0)
		return true;
	else
		return false;
}

bool WtGraph::isFull() const
{
	if (size == maxSize)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

void WtGraph::showStructure()
{
    int wt,         // Edge weight
        row, col;   // Loop counters

    if (size == 0)
        cout << "Empty graph" << endl;
    else
    {
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++)
			cout << row << '\t' << vertexList[row].label << endl;

		cout << endl << "Edge matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getEdge(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}

#if INLAB1
		cout << endl << "Path matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getPath(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}
#endif
    }
}

//--------------------------------------------------------------------

#if INLAB1
int WtGraph::getPath(int row, int col)
{
	return pathMatrix[row * size + col];
}

void WtGraph::setPath(int row, int col, int wt)
{
	pathMatrix[row * size + col] = wt;
}

void WtGraph::computePaths() 
{
	for (int i = 0; i < size * size; i++)
		pathMatrix[i] = adjMatrix[i];

	for (int i = 0; i < size; i++)
		setPath(i, i, 0);

	for (int m = 0; m < size; m++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
			{
				if ((getPath(j, m) != infiniteEdgeWt && getPath(m, k) != infiniteEdgeWt) && (getPath(j, m) + getPath(m, k) < getPath(j, k)))
				{
					setPath(j, k, getPath(j, m) + getPath(m, k));
					setPath(k, j, getPath(j, m) + getPath(m, k));
				}
			}
}
#endif