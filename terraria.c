#include <string.h>
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <curses.h>
int fileread(char file[],long bytenum)
{
FILE* fptr;
fptr = fopen(file,"rb");
int a = 0;
unsigned char b[1];
    fseek(fptr,bytenum,SEEK_SET);
	fread(b,1,1,fptr);
//	printf("%x",b[0]);
    return(b[0]);
fclose(fptr);
//printf("\n");
}
void filewrite(char file[],unsigned char input[])
{

//b=&a;
FILE *fptr;
fptr = fopen(file,"wb");
fprintf(fptr,"%c",input);
fclose(fptr);
}
void fileappend(char file[],unsigned char input)
{
    FILE *fptr;
    fptr=fopen(file,"ab");
    fprintf(fptr,"%c",input);
    fclose(fptr);
}
char cgen(long chunkx,long chunky,int indexnum)
{	
	unsigned long buffer;
	if (indexnum < 8)
	{
		buffer = chunkx;	
		if (indexnum == 0)
		{
			return(buffer/256);
		}
		buffer=buffer-(buffer/256*256);
		if (indexnum == 1)
		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 2)
		{
			return(buffer/256);
		}
	
		buffer=buffer-(buffer/256*256);
		if (indexnum == 3)
		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 4)
		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 5)
		{
			return(buffer/256);
		}
	
		buffer=buffer-(buffer/256*256);
		if (indexnum == 6)
		{
			return(buffer/256);
		}
		if (indexnum == 7)
		{
			return(buffer);
		}
	}
	if (indexnum < 16)
	{
		buffer = chunky;	
		if (indexnum == 8)
		{
			return(buffer/256);
		}
		buffer=buffer-(buffer/256*256);
		if (indexnum == 9)
		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 10)
		{
			return(buffer/256);
		}
	
		buffer=buffer-(buffer/256*256);
		if (indexnum == 11)
		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 12)
 		{
			return(buffer/256);
		}
		
		buffer=buffer-(buffer/256*256);
		if (indexnum == 13)
		{
			return(buffer/256);
		}
	
		buffer=buffer-(buffer/256*256);
		if (indexnum == 14)
		{
			return(buffer/256);
		}
		if (indexnum == 15)
		{
			return(buffer);
		}
	}
	buffer = indexnum - 16;
	//temp because I cant think of a gen function
	//f(blockx,blocky,chunkx,chunky)
	int blockx = buffer%16;
	int blocky = buffer/16;
	//out[buffer+16]='f';
	return('f');
	//char k;
	//k = *out;
	//return(out);
}
char* pixrender(unsigned char a)
{
	if (a == 'f')
    {
		return("\x1b[35;42mXX\x1b[39;49m");
    }
	if (a == 'g')
	{
		return("\x1b[35;45mXX\x1b[39;49m");
	}
    else
    {
		printf("block type %u (aka %c) not found\n", a,a);
        exit(1);
    }
}

	//globals start
	long playerx = 0;
	long playery = 0;
	char chunktl[262];
	char chunktm[262];
	char chunktr[262];
	char chunkml[262];
	char chunkmm[262];
	char chunkmr[262];
	char chunkbl[262];
	char chunkbm[262];
	char chunkbr[262];
	bool run = true;
	bool interr = false;
	//globals end

void render()
{
	int xrend;
	int relx;
	int rely;
	char xoff;
	char yoff;
	int yrend=9;
		
	while (yrend >-9)
	{
		xrend = -16;
		while (xrend < 16)
		{
			//printf("%dx,%dy",xrend,yrend);	
			xoff = 'm';
			yoff = 'm';
			relx = playerx + xrend;
			rely = playery + yrend;
			if (relx > 8)
			{
				xoff = 'r';
				relx=relx-16;
			}		
			if (relx < -7)
			{
				xoff = 'l';
				relx = relx+16;
			}			
			if (rely > 8)
			{
				yoff = 't';
				rely=rely-16;
			}		
			if (rely < -7)
			{
				yoff = 'b';
				rely = rely+16;
			}
			int arrayloc = relx + 7 +(8-rely)*16;
			if (yoff == 't')
			{
				if (xoff == 'l')
				{
					printf(pixrender(chunktl[arrayloc]));
				}  
				if (xoff == 'm')
				{
					printf(pixrender(chunktm[arrayloc]));
				}  
				if (xoff == 'r')
				{
					printf(pixrender(chunktr[arrayloc]));
				}  
			}
			if (yoff == 'm')
			{
				if (xoff == 'l')
				{
					printf(pixrender(chunkml[arrayloc]));
				}  
				if (xoff == 'm')
				{
					printf(pixrender(chunkmm[arrayloc]));
				}  
				if (xoff == 'r')
				{
					printf(pixrender(chunkmr[arrayloc]));
				}  
			}
			if (yoff == 'b')
			{
				if (xoff == 'l')
				{
					printf(pixrender(chunkbl[arrayloc]));
				}  
				if (xoff == 'm')
				{
					printf(pixrender(chunkbm[arrayloc]));
				}  
				if (xoff == 'r')
				{
					printf(pixrender(chunkbr[arrayloc]));
				}  
			}
			
			xrend++;
		}
		printf("\n");
		yrend=yrend-1;
	}
}
//active chunk updater
void acu()
{
	long playerchunkx = playerx/16;
	long playerchunky = playerx/16;
	int cnt = 0;
	while (cnt < 262)
	{
		chunktl[cnt]=cgen(playerchunkx-1,playerchunky+1,cnt+16);
		chunktm[cnt]=cgen(playerchunkx,playerchunky+1,cnt+16);
		chunktr[cnt]=cgen(playerchunkx+1,playerchunky+1,cnt+16);
		chunkml[cnt]=cgen(playerchunkx-1,playerchunky,cnt+16);
		chunkmm[cnt]=cgen(playerchunkx,playerchunky,cnt+16);
		chunkmr[cnt]=cgen(playerchunkx+1,playerchunky,cnt+16);
		chunkbl[cnt]=cgen(playerchunkx-1,playerchunky-1,cnt+16);
		chunkbm[cnt]=cgen(playerchunkx,playerchunky-1,cnt+16);
		chunkbr[cnt]=cgen(playerchunkx+1,playerchunky-1,cnt+16);
		cnt++;
	}
}
bool skip(char a)
{
	if (a == '\0' || a == '\n' || a == ' ')
	{
		return(false);
	}
	return(true);
}
int string_to_int(char a)
{
	if (a == '1')
	{
		return(1);
	}
	if (a == '2')
	{
		return(2);
	}
	if (a == '3')
	{
		return(3);
	}
	if (a == '4')
	{
		return(4);
	}
	if (a == '5')
	{
		return(5);
	}
	if (a == '6')
	{
		return(6);
	}
	if (a == '7')
	{
		return(7);
	}
	if (a == '8')
	{
		return(8);
	}
	if (a == '9')
	{
		return(9);
	}
	if (a == '0')
	{
		return(0);
	}
	else
	{
		return(0);
		interr = true;
	}
}
int getint(char input[],int intget)
{
int loc = 1;
int blocknum = 4;
int intblock[2];
int cnt;
	while (input[loc] == ' ')
	{
		while (skip(input[loc]))
		{
			cnt = cnt * 10;
			if (interr)
			{
				return(1);
				printf("invalid input\n");
			}
			cnt = cnt + string_to_int(input[loc]);
			loc = loc  + 1;
		}
		intblock[blocknum] = cnt;
		blocknum++;
	}
	return(intblock[intget]);
}
void cmd()
{
	char input[200];
	printf("> ");
	fgets(input,200,stdin);
	run = true;
	//printf("%s\n",input);
	
	if (input[0] == 'q')
	{
		run=false;
	}
	if (input[0] == 'h')
	{
		if (input[1] == '\0' || input[1] == '\n')
		{
			printf("q:quit\nh:help\n");
		}
	}
	if (input[0] == 'f');
	{
		printf("int0 %d\n",input[0]);
		printf("intf %d\n",'f');
		printf("f detected\n");
		printf("num %d\n",getint(input,1));

	}

	
}
void game()
{
	acu();
	render();

	long framecount = 0;
	while (run)
	{
		framecount++;
		cmd();
	}
}
int main()
{
game();
return(0);

}
