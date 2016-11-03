#ifndef __vga__
#define __vga__

//===================================================================================================================
//							V	V    GGGG	   AAA
//							V	V   G	   G  A	  A
//							V	V   G		    A	  A
//							V	V   G	 GGG  AAAAA
//							V V   G	   G  A	  A
//							 V	   GGGG	  A	  A
//===================================================================================================================

#define		VGA_SYNC_DEL		0x60	

#define		LINES_MAX					5000		// kol-vo liniy
#define		VGA_X_LEN					25			// dilinna stroki

#define		VGA_LINE_SPACE		11			// otstup megdu strok
#define		VGA_FONT_SIZE			2				// razmer chrifta
#define		VGA_LETTER_WHIDTH	4

typedef enum vga_md {TXT_STATIC, TXT_SCROLL_DWN, TXT_SCROLL_UP, TXT_NO_SCROLL, VGA_GARPH, VGA_NONE} vga_mod;

typedef struct 
{
	int x;
	int y;
}POINT;	

void 	vga_init		(vga_mod mode);
void 	vga_clear					(void);
void	vga_print_string	(POINT *_xy, char *str, char word_wrap);
void vga_put_char (int x, int y, char ch);
char* vga_get_line (int line);

void 	vga_mode 		(vga_mod mode);
void 	vga_scroll_speed	(int spd);
int 	get_lines_cnt (int new_lines);

#endif
