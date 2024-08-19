#include <iostream>
#include <vector>
using namespace std;

struct block {
int type;
int xpos;
int ypos;
};
block newblock(int a,int b,int c) {
block s;
s.type = a;
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
			a.blocks[16*x+y] = newblock(1,x,y);
			y++;
				
		}
		x++;
	}
	return a;
}
vector< chunk > map;

string pixrender(block a)
{
	string s = "\x1b[";
	if (a.type == 1)
		{
			s.append("32;45m");
			return(s);
		}
	else 
		{
			cout << a.type;
			exit(1);
		}
}
block getblock(int x,int y) 
{
	int cnt = 0;
	while (cnt < map.size()) 
	{
		//cout << map[cnt].x << "," << map[cnt].y << endl; cout.flush();
		if (map[cnt].x == x/16)
		{
			if(map[cnt].y == y/16)
			{
				
				return(map[cnt].blocks[16*(x%16)+(y%16)]);
			}
		}
		cnt++;
	}
	map.push_back(newchunk(x/16,y/16));
	return(map[map.size()-1].blocks[16*(x%16)+(y%16)]);
	
}
void display(int x,int y)
{
	string block = "";
	//32x18 screen, each square is XX
	//render x-15 x+16 y+9 y-8
	int cntx;
	int cnty = 9;
	while (cnty > -9)
	{	
		cntx = -15;
		while (cntx < 17)
		{	
			cout << cntx << "," << cnty << endl; cout.flush();
			cout << "test1" << endl; cout.flush();
			getblock(x+cntx,y+cnty);
			cout << "test2" << endl; cout.flush();
			block.append(pixrender(getblock(x+cntx,y+cnty)));
			cout << "test3" << endl; cout.flush();
			cout << cntx << "," << cnty << endl; cout.flush();
			cntx++;
		}
		block.append("\n");
		cnty = cnty - 1;
	}
	cout << block << endl;
	cout.flush();


}
void game() 
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
					}
					cntc ++;
				}
				if (cf == false)
				{
					map.push_back(newchunk(x + cntx,y + cnty));
					
				}
					
				
				cnty++;
			}
			cntx++;
		}
		cout << map.size();
		cout << "test4" << endl; cout.flush();
		
		display(x,y);
		
	}
}
int main()
{
	
	game();
	cout << "program returned 0" << endl;
	return 0;

}
