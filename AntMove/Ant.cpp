#include "StdAfx.h"
#include "Ant.h"

int Map[nMapHeight][nMapWidth]; //地图信息

 HDC FIND_LEFTDC;
 HBITMAP FIND_LEFTBitmap;

 HDC FIND_UPDC;
 HBITMAP FIND_UPBitmap;

 HDC FIND_RIGHTDC;
 HBITMAP FIND_RIGHTBitmap;

 HDC FIND_DOWNDC;
 HBITMAP FIND_DOWNBitmap;
//------------------------------------------------
 HDC GO_LEFTDC;
 HBITMAP GO_LEFTBitmap;

 HDC GO_UPDC;
 HBITMAP GO_UPBitmap;

 HDC GO_RIGHTDC;
 HBITMAP GO_RIGHTBitmap;

 HDC GO_DOWNDC;
 HBITMAP GO_DOWNBitmap;

//------------------------------------------------
 HDC BACK_LEFTDC;
 HBITMAP BACK_LEFTBitmap;

 HDC BACK_UPDC;
 HBITMAP BACK_UPBitmap;

 HDC BACK_RIGHTDC;
 HBITMAP BACK_RIGHTBitmap;

 HDC BACK_DOWNDC;
 HBITMAP BACK_DOWNBitmap;

//------------------------------------------------

 int nFoodCount;//食物数

HDC wallDC;
HBITMAP wallBitmap;


HDC foodDC;
HBITMAP foodBitmap;


HDC nestDC;
HBITMAP nestBitmap;

vector<Ant> g_vecAnt;

void DrawAll(HDC hdc)
{

	PatBlt(hdc, 0, 0, nMapWidth * nPicWidth, nMapHeight * nPicHeight, WHITENESS);

	for (int i = 0; i < nMapHeight; i++)
	{
		for (int k = 0; k < nMapWidth; k++)
		{
			switch(Map[i][k])
			{
			case WALL:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, wallDC, 0, 0, SRCCOPY);
					break;
				}
			case NEST:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, nestDC, 0, 0, SRCCOPY);
					break;
				}
			case FOOD:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, foodDC, 0, 0, SRCCOPY);
					break;
				}
			}
		}
	}

	vector<Ant>::iterator it = g_vecAnt.begin();

	while (it != g_vecAnt.end())
	{

		int nX = (*it).nX * nPicWidth;

		int nY = (*it).nY * nPicHeight;

		switch((*it).m_state)
		{
		case FINDING:
			{
				switch((*it).m_movestate.top().mDirection)
				{
				case LEFT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, FIND_LEFTDC, 0, 0, SRCCOPY);
						break;
					}
				case UP:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, FIND_UPDC, 0, 0, SRCCOPY);
						break;
					}
				case RIGHT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, FIND_RIGHTDC, 0, 0, SRCCOPY);
						break;
					}
				case DOWN:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, FIND_DOWNDC, 0, 0, SRCCOPY);
						break;
					}
				}
				break;
			}

		case GO:
			{
				switch((*it).mDirection)
				{
				case LEFT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, GO_LEFTDC, 0, 0, SRCCOPY);
						break;
					}
				case UP:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, GO_UPDC, 0, 0, SRCCOPY);
						break;
					}
				case RIGHT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, GO_RIGHTDC, 0, 0, SRCCOPY);
						break;
					}
				case DOWN:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, GO_DOWNDC, 0, 0, SRCCOPY);
						break;
					}
				}
				break;
			}

		case BACK:
			{
				//(m_movestate.top()).mDirection
				
				switch((*it).mDirection)
				{
				case LEFT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, BACK_LEFTDC, 0, 0, SRCCOPY);
						break;
					}
				case UP:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, BACK_UPDC, 0, 0, SRCCOPY);
						break;
					}
				case RIGHT:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, BACK_RIGHTDC, 0, 0, SRCCOPY);
						break;
					}
				case DOWN:
					{
						BitBlt(hdc,  nX, nY, nPicWidth, nPicHeight, BACK_DOWNDC, 0, 0, SRCCOPY);
						break;
					}
				}
				break;
			}
			
		}

		
		
		it++;
	}

	
}


void InitResource()
{
	HDC hdc = GetDC(0);
	
	
	FIND_LEFTDC = CreateCompatibleDC(hdc);
    FIND_LEFTBitmap = (HBITMAP)LoadImage(NULL, "pic\\FIND_LEFT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(FIND_LEFTDC, FIND_LEFTBitmap);

	FIND_UPDC = CreateCompatibleDC(hdc);
    FIND_UPBitmap = (HBITMAP)LoadImage(NULL, "pic\\FIND_UP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(FIND_UPDC, FIND_UPBitmap);

	FIND_RIGHTDC = CreateCompatibleDC(hdc);
    FIND_RIGHTBitmap = (HBITMAP)LoadImage(NULL, "pic\\FIND_RIGHT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(FIND_RIGHTDC, FIND_RIGHTBitmap);

	FIND_DOWNDC = CreateCompatibleDC(hdc);
    FIND_DOWNBitmap = (HBITMAP)LoadImage(NULL, "pic\\FIND_DOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(FIND_DOWNDC, FIND_DOWNBitmap);
	//-----------------------------------------------------------------------------
	GO_LEFTDC = CreateCompatibleDC(hdc);
    GO_LEFTBitmap = (HBITMAP)LoadImage(NULL, "pic\\GO_LEFT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(GO_LEFTDC, GO_LEFTBitmap);

	GO_UPDC = CreateCompatibleDC(hdc);
    GO_UPBitmap = (HBITMAP)LoadImage(NULL, "pic\\GO_UP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(GO_UPDC, GO_UPBitmap);

	GO_RIGHTDC = CreateCompatibleDC(hdc);
    GO_RIGHTBitmap = (HBITMAP)LoadImage(NULL, "pic\\GO_RIGHT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(GO_RIGHTDC, GO_RIGHTBitmap);

	GO_DOWNDC = CreateCompatibleDC(hdc);
    GO_DOWNBitmap = (HBITMAP)LoadImage(NULL, "pic\\GO_DOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(GO_DOWNDC, GO_DOWNBitmap);
	//-----------------------------------------------------------------------------
	BACK_LEFTDC = CreateCompatibleDC(hdc);
    BACK_LEFTBitmap = (HBITMAP)LoadImage(NULL, "pic\\BACK_LEFT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(BACK_LEFTDC, BACK_LEFTBitmap);

	BACK_UPDC = CreateCompatibleDC(hdc);
    BACK_UPBitmap = (HBITMAP)LoadImage(NULL, "pic\\BACK_UP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(BACK_UPDC, BACK_UPBitmap);

	BACK_RIGHTDC = CreateCompatibleDC(hdc);
    BACK_RIGHTBitmap = (HBITMAP)LoadImage(NULL, "pic\\BACK_RIGHT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(BACK_RIGHTDC, BACK_RIGHTBitmap);

	BACK_DOWNDC = CreateCompatibleDC(hdc);
    BACK_DOWNBitmap = (HBITMAP)LoadImage(NULL, "pic\\BACK_DOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(BACK_DOWNDC, BACK_DOWNBitmap);
	//-----------------------------------------------------------------------------
	wallDC = CreateCompatibleDC(hdc);
	wallBitmap = (HBITMAP)LoadImage(NULL, "pic\\wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(wallDC, wallBitmap);

	
	foodDC = CreateCompatibleDC(hdc);
	foodBitmap = (HBITMAP)LoadImage(NULL, "pic\\food.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(foodDC, foodBitmap);
	
	
	nestDC = CreateCompatibleDC(hdc);
	nestBitmap = (HBITMAP)LoadImage(NULL, "pic\\nest.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(nestDC, nestBitmap);

	DeleteDC(hdc);

	nFoodCount = 500;

	ReadMap("Maps\\124.map");


}

void ReleaseResource()
{
	DeleteDC(FIND_LEFTDC);
	DeleteDC(FIND_UPDC);
	DeleteDC(FIND_DOWNDC);
	DeleteDC(FIND_RIGHTDC);
	
	DeleteDC(GO_LEFTDC);
	DeleteDC(GO_UPDC);
	DeleteDC(GO_DOWNDC);
	DeleteDC(GO_RIGHTDC);

	DeleteDC(BACK_LEFTDC);
	DeleteDC(BACK_UPDC);
	DeleteDC(BACK_DOWNDC);
	DeleteDC(BACK_RIGHTDC);

	DeleteDC(wallDC);
	DeleteDC(foodDC);
	DeleteDC(nestDC);
	
	DeleteObject(FIND_RIGHTBitmap);
	DeleteObject(FIND_UPBitmap);
	DeleteObject(FIND_LEFTBitmap);
	DeleteObject(FIND_DOWNBitmap);

	DeleteObject(GO_RIGHTBitmap);
	DeleteObject(GO_UPBitmap);
	DeleteObject(GO_LEFTBitmap);
	DeleteObject(GO_DOWNBitmap);

	DeleteObject(BACK_RIGHTBitmap);
	DeleteObject(BACK_UPBitmap);
	DeleteObject(BACK_LEFTBitmap);
	DeleteObject(BACK_DOWNBitmap);

	DeleteObject(wallBitmap);
	DeleteObject(foodBitmap);
	DeleteObject(nestBitmap);
}

void ReadMap(char *lpszFileName)
{
	fstream file;

	file.open(lpszFileName, ios::in | ios::binary);

	if (file.bad() || !file.good())
	{
		file.close();

		return;
	}
	file.read((char *)Map, nMapHeight * nMapWidth * sizeof(int));

	file.close();
}


void Ant::Move()
{
		{
		switch (m_state)
		{
		case FINDING:
			{
				bool bFind = false;

				int nNewX;

				int nNewY;

				bool bOK = true;

				switch(m_movestate.top().mDirection) 
				{
				case LEFT:
					{
						nNewX = nX - 1;

						nNewY = nY;

						if (nNewX < 0)
						{
							bOK = false;
						}

						break;
					}
				case UP:
					{
						nNewX = nX;

						nNewY = nY - 1;

						if (nNewY < 0)
						{
							bOK = false;
						}

						break;
					}
				case RIGHT:
					{
						nNewX = nX + 1;

						nNewY = nY;

						if (nNewX >= nMapWidth)
						{
							bOK = false;
						}

						break;
					}
				case DOWN:
					{
						nNewX = nX;

						nNewY = nY + 1;

						if (nNewY >= nMapHeight)
						{
							bOK = false;
						}
					}
				}

				
				
				if (Map[nNewY][nNewX] == WALL || !bOK || m_bPass[nNewY][nNewX])
				{
					if (!m_movestate.top().ChangeDirection())
					{
						m_movestate.pop();
						
						nX = m_movestate.top().nX;
					
						nY = m_movestate.top().nY;

					}
					
					mDirection = m_movestate.top().mDirection;

				}
				else
				{
					MoveState sta(nNewX, nNewY, m_movestate.top().mDirection);

					mDirection = m_movestate.top().mDirection;
					
					m_movestate.push(sta);

					nX = nNewX;

					nY = nNewY;

					m_bPass[nNewY][nNewX] = true;

					if (Map[nNewY][nNewX] == FOOD)
					{
						m_state = BACK;

						nFoodCount--;

						m_go.clear();

						m_back.clear();

						while (!m_movestate.empty())
						{
							m_go.push_front(m_movestate.top());
							
							m_back.push_back(m_movestate.top());

							m_movestate.pop();
						}
					}
					else
					{
						vector<Ant>::iterator it = g_vecAnt.begin();

						while (it != g_vecAnt.end())
						{
							if ((*it).m_state == GO || (*it).m_state == BACK)
							{
								list<MoveState>::iterator it2 = (*it).m_go.begin();

								bool bOK = false;

								while (it2 != (*it).m_go.end())
								{
									if ((*it2).nX == nX && (*it2).nY == nY)
									{
										m_go = (*it).m_go;

										m_back = (*it).m_back;

										m_state = GO;

										bOK = true;

										break;
									}	

									it2++;
								}

								if (bOK)
								{
									break;
								}
							}

							it++;
						}
					}
				}
				break;
			}
		case GO:
			{
				if (Map[nY][nX] == FOOD)
				{
					m_state = BACK;

					nFoodCount--;
				}
				else
				{
					list<MoveState>::const_iterator it = m_go.begin();

					while (it != m_go.end())
					{
						if ((*it).nX == nX && (*it).nY == nY)
						{
							it++;
							
							nX = (*it).nX;

							nY = (*it).nY;

							mDirection = (*it).mDirection;

							break;
						}
						
						it++;
					}

				}
				break;
			}
		case BACK:
			{
				if (Map[nY][nX] == NEST)
				{
					m_state = GO;
				}
				else
				{
					list<MoveState>::const_iterator it = m_back.begin();
					
					while (it != m_back.end())
					{
						if ((*it).nX == nX && (*it).nY == nY)
						{
							it++;
							
							nX = (*it).nX;
							
							nY = (*it).nY;
							
							mDirection = (*it).mDirection;
							
							break;
						}
						
						it++;
					}
					
				}
				
				break;
			}

		}
	}
}