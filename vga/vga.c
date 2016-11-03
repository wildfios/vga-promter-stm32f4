#include "vga.h"
#include "ascii_tab.h"
#include "vga_hal.h"
#include <string.h>

vga_mod vga_disp_mode = TXT_SCROLL_DWN; 

int		scroll_speed = 0;
char	scroll_enabled = 1;
int		LINES = 40;

char text_ram [LINES_MAX][VGA_X_LEN];

//====================================================================================================================
//====================================================================================================================
int get_lines_cnt (int new_lines)
{
int old_lines = LINES;
	if (new_lines > 0)
		LINES = new_lines;
	
	return old_lines;
}

char* vga_get_line (int line)
{
	return &text_ram [line][0];
}

void del_vga (int dl_vga) 
{
next:
	if (dl_vga != 0)
	{
		dl_vga--;
		goto next;
	}
}

void vga_print_string (POINT *_xy, char *str, char word_wrap)
{
	strcpy(&text_ram[_xy->y][_xy->x], str);
	if (strlen(str) > VGA_X_LEN)
	{
		_xy->y += strlen(str) / VGA_X_LEN;	
		_xy->x += strlen(str) - _xy->y + 1;	
	}
}

void vga_put_char (int x, int y, char ch)
{
	text_ram[y][x] = ch;
}

void vga_clear () 
{
int i, j;
	for (i = 0; i < LINES; i++)
		for (j = 0; j < VGA_X_LEN; j++)
		text_ram [i][j] = ' ';
}

void  vga_scroll_speed (int spd)
{
	scroll_speed = spd;
}
//====================================================================================================================
//====================================================================================================================

void vga_mode (vga_mod mode)
{
	vga_disp_mode  = mode;

	if ((mode == TXT_STATIC) || (mode == TXT_NO_SCROLL))
		scroll_enabled = 0;
	else 
		if ((mode == TXT_SCROLL_DWN) || (mode == TXT_SCROLL_UP))
			scroll_enabled = 1;
}
//====================================================================================================================
//====================================================================================================================

void draw_text (int h_line_count)
{
int		letter_col_count;    
char 	tmp_letter_col_count;
	
static	int		strt = 0, txt_raw_cnt = 1, cur_leter_line = 1, letet_height_cnt = 1, text_col_cnt = 0;
	//scroll								  			
static	int scroll_del = 0, scroll_height_cnt = 0, scroll_letter_line = 0;

	if (h_line_count < 480)
	{
		del_vga (60);
		//Visota otobrajaemoy bukvi
		if (letet_height_cnt++ > VGA_FONT_SIZE)	{cur_leter_line++;  letet_height_cnt = 0;} 	 
		//Mejstrochniy interval
		if (cur_leter_line   > VGA_LINE_SPACE)	{cur_leter_line = 0;  if (txt_raw_cnt++ > LINES) txt_raw_cnt = 0;}
		//Otobrojenie stroki
		if (cur_leter_line < 8) //.................................................................Mejstrochniy interval
		{
			if (letet_height_cnt != 0) //............................................................Propusk liniy chcrez stroku
			//	del_vga(1);
			for (text_col_cnt = VGA_X_LEN - 1; text_col_cnt >= 0; text_col_cnt--) //......................Schitivanie bukv
			{
				tmp_letter_col_count = ascii_tab[text_ram[txt_raw_cnt][text_col_cnt]][cur_leter_line];
				for (letter_col_count = 0; letter_col_count < 7; letter_col_count++)//.................Sdvig popikselno na ekran
				{
					if ((tmp_letter_col_count | 0xFE) == 0xFE )	 //0xef
						signal_lo
					else
						signal_hi
					del_vga(VGA_LETTER_WHIDTH);	// 
					tmp_letter_col_count = tmp_letter_col_count >> 1;	 //>>
				}
				signal_lo//............................................................................Konec stroki
			}
		}
	}
//...............................scroll routines..........................................................................	
	else
	{
		signal_lo;
		
		if (scroll_enabled)
			if (scroll_del++ > scroll_speed - 100)
			{
				scroll_del = 0;
					if (vga_disp_mode == TXT_SCROLL_DWN)	
					{		
//......................DOWN................
						letet_height_cnt = scroll_height_cnt;
						if (scroll_height_cnt++ > VGA_FONT_SIZE + 1)
						{
							letet_height_cnt  =	0;
							scroll_height_cnt =	1;
							cur_leter_line = scroll_letter_line;
							if (scroll_letter_line++ > VGA_LINE_SPACE) 
							{
								txt_raw_cnt = ++strt;
								scroll_letter_line = 1;
								cur_leter_line = 0;
								if (strt > LINES + 1)
									strt = 0;
							}
						}
					}
//.......................UP....................					
					else
					{
						letet_height_cnt = scroll_height_cnt;
						if (scroll_height_cnt-- < 0)
						{
							letet_height_cnt  =	VGA_FONT_SIZE;
							scroll_height_cnt =	VGA_FONT_SIZE - 1;
							cur_leter_line = scroll_letter_line;
							if (scroll_letter_line-- < 0) 
							{
								txt_raw_cnt = --strt;
								scroll_letter_line = VGA_LINE_SPACE - 1;
								cur_leter_line = VGA_LINE_SPACE;
								if (strt < 0) 
									strt = LINES;
							}
						}
					}
//....................end scroll routines
			}
		else
			if (vga_disp_mode == TXT_STATIC)	//............................................Static node, no scroll		  
			{
				strt = 0;
				txt_raw_cnt = 1;
				cur_leter_line = 1;
				letet_height_cnt = 1;	
			}
			txt_raw_cnt = strt;
	}	
}
//====================================================================================================================
//====================================================================================================================

void draw_graph (int h_line_count)
{
	if (h_line_count < 480)
	{
		del_vga (60);
		//for ()
	
	}
}		  
//====================================================================================================================
//====================================================================================================================
#ifdef __cplusplus 
extern "C"
{
#endif
void TIM2_IRQHandler(void)
{
	static int  h_line_count = 0;

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	signal_lo;						// clear pencil

	h_sync_hi			  			//horisontal sync
		del_vga (VGA_SYNC_DEL);			
	h_line_count++;		
	h_sync_lo	      			

		if (h_line_count > 480)		// vertical sync
		{
			v_sync_lo   	  			
				if (h_line_count == 520 )	
				{					  		
					h_line_count = 0;		
					v_sync_hi		  		
				}							
		}
		if (vga_disp_mode != VGA_NONE)
			if (vga_disp_mode != VGA_GARPH)
				draw_text  (h_line_count);	   	// draw line
			else
				draw_graph (h_line_count);		
}
#ifdef __cplusplus 
}
#endif
//======================================================================================================

void vga_init (vga_mod mode)
{
	vga_mode (mode);

	vga_init_gpio		();
	vga_init_timer	();
}
