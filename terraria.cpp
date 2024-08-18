#include <iostream>
#include <vector>
using namespace std;

struct block {
char col;
int xpos;
int ypos;
};
block newblock(char a,int b,int c) {
block s;
s.col = a;
s.xpos = b;
s.ypos = c;
return s;
}
struct chunk 
{
	int x;
	int y;
	block blocks[256];
};
chunk newchunk (int chunkx, int chunky)
{
	int x;
	int y;
	chunk a;
	a.x = chunkx;
	a.y = chunky;
	x=0;
	while (x<16) 
	{
		y=0;
		while (y<16)
		{
			a.blocks[16*x+y] = newblock('r',x,y);
			y++;
				
		}
		x++;
	}
	return a;
}
vector< chunk > map;
void display(int x,int y)
{
	//32x18 screen, each square is XX
	//x/16+-1	
	//y/16+-1

}
block getblock(int x,int y) 
{
	int cnt = 0;
	while (cnt < map.size()) 
	{
		if (map[cnt].x == x/16)
		{
			if(map[cnt].y == y/16)
			{
				
				return(map[cnt].blocks[16*(x%16)+(y%16)]);
			}
		}
		cnt++;
	}
	cerr << "block not found" << endl;
	exit(1);
}

int main() 
{
	map.push_back(newchunk(0,0));
	int x;
	int y;
	int cntx;
	int cnty;
	int cntc;
	bool cf;
	while (true) 
	{
		cntx = -1;
	
		while (cntx < 2)
		{
			cnty = -1;
			while (cnty < 2)
			{
				cntc = 0;
				cf = false;			
				while (cntc < map.size())
				{
					if (map[cntc].x == x + cntx) 
					{
						if (map[cntc].y == y + cnty)
						{
							cf = true;
						}
						else 
						{
							map.push_back(newchunk(x + cntx,y + cnty));
						}
					}
				}
			}
		}
		
	}
	display(x,y);
	cout << "program returned 0" << endl;
	return 0;

}
