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
char* chunkgen(long x,long y)
{
	char *out = malloc(140);
	
	unsigned long buffer;
	buffer = x;
	
	out[0]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[1]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[2]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[3]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[4]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[5]=buffer/255;
	buffer=buffer-(buffer/256*256);
	out[6]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[7]=buffer;
	buffer=buffer-(buffer/256*256);
	buffer = y;
	out[1]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[2]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[3]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[4]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[5]=buffer/255;
	buffer=buffer-(buffer/256*256);
	out[6]=buffer/256;
	buffer=buffer-(buffer/256*256);
	out[7]=buffer;
	buffer=0;
	while (buffer<128)
	{
		buffer++;
		//temp because I cant think of a gen function
		out[buffer+16]='f';
	}	
	//char k;
	//k = *out;
	return(out);
}
char* pixrender(char a)
{
	if (a == 'f')
        {
			return("\x1b[32;45mXX");
        }

    else
        {
			printf("block type %c not found", a);
            exit(1);
        }
}
void game()
{
//spawncoords 00 idk for now
	int spawnx = 0;
	int spawny = 0;
	char chunktl[140];
	char chunktm[140];
	char chunktr[140];
	char chunkml[140];
	char chunkmm[140];
	char chunkmr[140];
	char chunkbl[140];
	char chunkbm[140];
	char chunkbr[140];
	
	char* pchunktl[140];
	char* pchunktm[140];
	char* pchunktr[140];
	char* pchunkml[140];
	char* pchunkmm[140];
	char* pchunkmr[140];
	char* pchunkbl[140];
	char* pchunkbm[140];
	char* pchunkbr[140];
	
	int chunkspawnx = spawnx/16;
	int chunkspawny = spawnx/16;
	*pchunktl = chunkgen(chunkspawnx-1,chunkspawny+1);
	*pchunktm = chunkgen(chunkspawnx,chunkspawny+1);
	*pchunktr = chunkgen(chunkspawnx+1,chunkspawny+1);
	*pchunkml = chunkgen(chunkspawnx-1,chunkspawny);
	*pchunkmm = chunkgen(chunkspawnx,chunkspawny);
	*pchunkmr = chunkgen(chunkspawnx+1,chunkspawny);
	*pchunkbl = chunkgen(chunkspawnx-1,chunkspawny-1);
	*pchunkbm = chunkgen(chunkspawnx,chunkspawny-1);
	*pchunkbr = chunkgen(chunkspawnx+1,chunkspawny-1);
	int cnt = 0;
	while (cnt < 140)
	{
		chunktl[cnt]=*pchunktl[cnt];
		chunktm[cnt]=*pchunktm[cnt];
		chunktr[cnt]=*pchunktr[cnt];
		chunkml[cnt]=*pchunkml[cnt];
		chunkmm[cnt]=*pchunkmm[cnt];
		chunkmr[cnt]=*pchunkmr[cnt];
		chunkbl[cnt]=*pchunkml[cnt];
		chunkbm[cnt]=*pchunkbm[cnt];
		chunkbr[cnt]=*pchunkbr[cnt];
		cnt++;
	}
	bool c = true;
	int playerx=spawnx;
	int playery=spawny;
	int xrend;
	int yrend;
	int relx;
	int rely;
	char xoff;
	char yoff;
	char input;
	while (c)
	{
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
						pixrender(chunktl[arrayloc]);
						}  
					if (xoff == 'm')
						{
						pixrender(chunktm[arrayloc]);
						}  
					if (xoff == 'r')
						{
						pixrender(chunktr[arrayloc]);
						}  
					}
				if (yoff == 'm')
					{
					if (xoff == 'l')
						{
						pixrender(chunkml[arrayloc]);
						}  
					if (xoff == 'm')
						{
						pixrender(chunkmm[arrayloc]);
						}  
					if (xoff == 'r')
						{
						pixrender(chunkmr[arrayloc]);
						}  
					}
				if (yoff == 'b')
					{
					if (xoff == 'l')
						{
						pixrender(chunkbl[arrayloc]);
						}  
					if (xoff == 'm')
						{
						pixrender(chunkbm[arrayloc]);
						}  
					if (xoff == 'r')
						{
						pixrender(chunkbr[arrayloc]);
						}  
					}
				printf("\n");
				xrend++;
			}
			yrend=yrend-1;
		}
		printf("> ");
		scanf("%c", &input);
		if (input == 'q')
		{
			c=false;
		}
	}
}
int main()
{
//printf("\033[32;45mXX\n\033[0m");
game();
//printf(pixrender('a'));
printf("\x1b[39;49m");
printf("\n");
return(0);

}
