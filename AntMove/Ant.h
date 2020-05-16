#if !defined ANT_H_INCLUDE
#define ANY_H_INCLUDE

#include <fstream>
#include <list>
#include <vector>
#include <stack>
#include <windows.h>

using namespace std;



extern HDC FIND_LEFTDC;
extern HBITMAP FIND_LEFTBitmap;

extern HDC FIND_UPDC;
extern HBITMAP FIND_UPBitmap;

extern HDC FIND_RIGHTDC;
extern HBITMAP FIND_RIGHTBitmap;

extern HDC FIND_DOWNDC;
extern HBITMAP FIND_DOWNBitmap;
//------------------------------------------------
extern HDC GO_LEFTDC;
extern HBITMAP GO_LEFTBitmap;

extern HDC GO_UPDC;
extern HBITMAP GO_UPBitmap;

extern HDC GO_RIGHTDC;
extern HBITMAP GO_RIGHTBitmap;

extern HDC GO_DOWNDC;
extern HBITMAP GO_DOWNBitmap;

//------------------------------------------------
extern HDC BACK_LEFTDC;
extern HBITMAP BACK_LEFTBitmap;

extern HDC BACK_UPDC;
extern HBITMAP BACK_UPBitmap;

extern HDC BACK_RIGHTDC;
extern HBITMAP BACK_RIGHTBitmap;

extern HDC BACK_DOWNDC;
extern HBITMAP BACK_DOWNBitmap;

//------------------------------------------------

extern HDC wallDC;
extern HBITMAP wallBitmap;


extern HDC foodDC;
extern HBITMAP foodBitmap;


extern HDC nestDC;
extern HBITMAP nestBitmap;


const int nMapWidth = 50;//��ͼ��

const int nMapHeight = 20;//��ͼ��

const int nPicWidth = 16;//ÿ��ͼƬ�Ŀ�

const int nPicHeight = 16;//ÿ��ͼƬ�ĸ�

const int nAntCount = 40;//���ϵĸ���

extern int Map[nMapHeight][nMapWidth];//��ͼ����

extern int nFoodCount;//ʳ����



enum MAPSTATE//��ͼ�ϵ��״̬
{
	NOTHING = 0,
	FOOD = 1,
    NEST = 2,
	WALL = 3
};

enum ANTSTATE//���ϵ�״̬
{
	FINDING = 0,//Ѱ��ʳ����
    GO = 1,//�Ѿ��ҵ�ʳ������ҵ�����·�ڳ���
	BACK = 2//��ʳ���ؼ�
};

enum DIRECTION//���ϵ��˶�����
{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};

typedef struct SMoveState
{
	int nX;

	int nY;

	bool bDirectionMoved[4];//��������Ѿ��߹�
    
	DIRECTION mDirection;//��ǰ�ķ���

	SMoveState(int x, int y, DIRECTION direction)
	{
		nX = x;

		nY = y;

		memset(bDirectionMoved, true, sizeof(bool) * 4);

		mDirection = direction;

		bDirectionMoved[direction] = true;
	}

	bool ChangeDirection()
	{
		if (!bDirectionMoved[0] && !bDirectionMoved[1] && !bDirectionMoved[2] && !bDirectionMoved[3])
		{
			return false;
		}

		switch(mDirection) 
		{
		case LEFT:
			{
				bDirectionMoved[LEFT] = false;

				mDirection = UP;

				break;
			}
		case UP:
			{
				bDirectionMoved[UP] = false;

				mDirection = RIGHT;

				break;
			}
		case RIGHT:
			{
				bDirectionMoved[RIGHT] = false;

				mDirection = DOWN;

				break;
			}
		case DOWN:
			{
				bDirectionMoved[DOWN] = false;

				mDirection = LEFT;

				break;
			}
		}

		return true;
	}


}MoveState;




class Ant
{
public:
	int nX;
	
	int nY;
	
	ANTSTATE m_state;//��ǰ��״̬;
	
	stack<MoveState> m_movestate;//��ǰ���˶�״̬

	DIRECTION mDirection;//��ǰ�ķ���

	Ant(int x, int y)
	{
		nX = x;

		nY = y;

		srand(time(0));
		
		DIRECTION dir = (DIRECTION)(rand()%4);
		
		mDirection = dir;

		MoveState tmpstate(x, y, dir);

		m_state = FINDING;

		m_movestate.push(tmpstate);

		for (int i = 0; i < nMapHeight; i++)
		{
			for (int k = 0; k < nMapWidth; k++)
			{
				m_bPass[i][k] = false;
			}
		}

		m_bPass[y][x] = true;
		
	}

	~Ant()
	{
		while(!m_movestate.empty())
		{
			m_movestate.pop();
		}

		m_go.clear();

		m_back.clear();
	}

	void Move();



	bool m_bPass[nMapHeight][nMapWidth];

	list<MoveState> m_go;

	list<MoveState> m_back;

};

extern vector<Ant> g_vecAnt;

extern void InitResource();

extern void ReleaseResource();

extern void DrawAll(HDC hdc);

extern void ReadMap(char *lpszFileName);

#endif