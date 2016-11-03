#ifndef __menu__h__
#define	__menu__h__

#include <string.h>
#include "kbd.h"

int file_man_count (FATFS *fs1)//, BYTE *buff1)
{			  
FRESULT res = FR_OK;
DIR Dir;
FILINFO Fno;
int i = 0;			
	//¬€¡Œ– ‘¿…À¿
	cout << "(c) fios 2012" << endl;
	cout << "     ¬€¡Œ– ‘¿…À¿" << endl << endl;
	pf_mount(fs1);	
	pf_opendir(fs1, &Dir, "");
	for(;;)
	{
		res = pf_readdir(fs1, &Dir, &Fno);
		if ((res != FR_OK) || (Fno.fname[0] == 0)) break;
		if (strstr(Fno.fname, ".TXT"))
		{
			cout << Fno.fname << endl;
			i++;
		}
	}
	return i;
}

void draw_men (int index, int cnt)
{
	for (int i = 4; i < cnt + 1; i++)
	if (i == index)
		vga_put_char (14, i, '<');
	else
		vga_put_char (14, i, ' ');
}

void del_men (int dl_vga) 
{
next:
	if (dl_vga != 0)
	{
		dl_vga--;
		goto next;
	}
}

int menu (int count)
{
int st_index = count + 3, index = 3;
	while (!btn_get())
	{
		if (index++ > st_index)
				index = 3;
		draw_men(index, st_index);
		del_men (20000000);		
	}	
	
	return index;
}

#endif

