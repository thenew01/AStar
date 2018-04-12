#include "stdafx.h"
#include "AStar.h"


// ǰ�ĸ����������ң���ʱ�룩�����ĸ���б��
//int AStarPathFind::dx[] = { 0, -1, 0, 1, -1, -1, 1, 1 };
//int AStarPathFind::dy[] = { -1, 0, 1, 0, 1, -1, -1, 1 };

//˳ʱ�룬�ϣ����£���
int AStarPathFind::dx[] = { 0, 1, 0, -1, -1, -1, 1, 1 };
int AStarPathFind::dy[] = { -1, 0, 1, 0, 1, -1, -1, 1 };

// ����Ȧ����1��ʾ����ͨ��
int AStarPathFind::map[][15] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
};


stack<PointEx*>* AStarPathFind::printPath(PointEx start, PointEx end) 
{
	/*
	* ����PriorityQueue����Ϊ����ȡ�����ڵ�Ԫ��
	*/
	deque<PointEx*> openTable;
	deque<PointEx*> closeTable;
	openTable.clear();
	closeTable.clear();
	stack<PointEx*>* pathStack = new stack<PointEx*>;
	start.parent = NULL;
	//�õ���ת�����ã����ǵ�ǰ��չ��
	PointEx* currentPoint = new PointEx(start.x, start.y);
	PointEx* pEnd = new PointEx(end.x, end.y);

	//closeTable.add(currentPoint);
	bool flag = true;

	while(flag) 
	{
		for (int i = 0; i < 8; i++) 
		{
			int fx = currentPoint->x + dx[i];
			int fy = currentPoint->y + dy[i];
			PointEx* tempPoint = new PointEx(fx,fy);
			if (map[fx][fy] == 1) 
			{
				// ���ڱ߽綼��1�м��ϰ���Ҳ��1�����������ؿ���Խ����ϰ�����չ����
				//��������ñ߽���ôfx >=map.length &&fy>=map[0].length�ж�Խ������
				continue;
			}
			else 
			{
				if(pEnd->equals(*tempPoint)) 
				{
					flag = false;
					//����tempPoint��������һ���˴�ʱ
					pEnd->parent = currentPoint;
					break;
				}
				if(i<4) 
				{
					tempPoint->G = currentPoint->G + 10;
				}else 
				{
					tempPoint->G = currentPoint->G + 14;
				}
				tempPoint->H = PointEx::getDis(*tempPoint,end);
				tempPoint->F = tempPoint->G + tempPoint->H;
				//��Ϊ��д��equals�����������������ֻ�ǰ�equals��Ȱ���
				//��һ����ʹ��java��װ����Ĺؼ�
				//if(openTable.contains(tempPoint)) 
				
				deque<PointEx*>::iterator it = find_if(openTable.begin(), openTable.end(), *tempPoint);
				deque<PointEx*>::iterator itClosed = find_if(closeTable.begin(), closeTable.end(), *tempPoint);
				if( it != openTable.end())
				{           
					//int pos = openTable.indexOf(tempPoint );
					//Point temp = openTable.get(pos);
					PointEx* temp = *it;
					if( tempPoint->F < temp->F ) 
					{
						//openTable.remove(pos);
						//openTable.add(tempPoint);
						openTable.erase(it);
						openTable.push_back(tempPoint);

						tempPoint->parent = currentPoint;
					}
				}
				else if(itClosed != closeTable.end() )
				{
					//int pos = closeTable.indexOf(tempPoint );
					//Point temp = closeTable.get(pos);
					PointEx* temp = *itClosed;
					if( tempPoint->F < temp->F ) 
					{
						//closeTable.remove(pos);
						//openTable.add(tempPoint);
						closeTable.erase(itClosed);
						openTable.push_back(tempPoint);
						tempPoint->parent = currentPoint;
					}
				}else
				{
					//openTable.add(tempPoint);
					openTable.push_back(tempPoint);
					tempPoint->parent = currentPoint;
				}

			}
		}//end for

		if(openTable.empty()) 
		{
			return NULL;
		}//��·��
		if(false==flag) 
		{
			break;
		}//�ҵ�·��
		
		//openTable.remove(currentPoint);
		//closeTable.add(currentPoint);
		//Collections.sort(openTable);
		//currentPoint = openTable.get(0);		
		
		//deque<PointEx*>::iterator it = find_if(openTable.begin(), openTable.end(), *currentPoint);
		//if( it != openTable.end() )
		//	openTable.erase(it);
		remove_if(openTable.begin(), openTable.end(), *currentPoint);
		closeTable.push_back(currentPoint);
		currentPoint = openTable.front();
		openTable.pop_front();
	}//end while
	PointEx* node = pEnd;
	while(node->parent!=NULL) 
	{
		pathStack->push(node);
		node = node->parent;
	}    
	return pathStack;
}
