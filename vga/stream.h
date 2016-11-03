#include "vga.h"

enum sys_con_str {endl};

class vgastream{
private:
	POINT sys_con_xy;
	char  inttochar[9];
	int   temp_int, temp_int_k;
public:

	vgastream()
	{
		sys_con_xy.x = 0;
		sys_con_xy.y = 1;
	}

	vgastream& operator << (char * lsd_str)
	{
		if (sys_con_xy.y > get_lines_cnt (0))
		{
			sys_con_xy.x = 0;
			sys_con_xy.y = 1;
			clear();
		}
		vga_print_string(&sys_con_xy, lsd_str, false);
		return *this;
	}  

	vgastream& operator << (sys_con_str str)
	{
		if (str == endl)
			sys_con_xy.y += 1;
		sys_con_xy.x = 0;
		return *this;
	}  

	vgastream& operator << (int int_val)
	{

		for (temp_int_k = 7; temp_int_k >= 0; temp_int_k--)
		{
			temp_int  =  int_val;
			temp_int &= 0x0000000F;
			if (temp_int > 9)
				temp_int += 0x37;
			else
				temp_int += 0x30;
			inttochar[temp_int_k] = temp_int;
			int_val = int_val >> 4;
		}
		inttochar[8] = 0;

		if (sys_con_xy.y > get_lines_cnt (0))
		{
			sys_con_xy.x = 1;
			sys_con_xy.y = 1;
			clear();
		}
		vga_print_string(&sys_con_xy, inttochar, false);

		return *this;
	}

	void clear ()
	{
		vga_clear();
		sys_con_xy.x = 0;
		sys_con_xy.y = 1;
	}  

}cout;		
