#define TAKO_FRAME_DURATION 100 // how long each frame lasts in ms
#define TAKO_SIZE 720 // number of bytes in array, minimize for adequate firmware size, max is 1024
#define TAKO_FRAMES 4
// #define TAKO_TIMEOUT 10000

uint32_t tako_timer = 0;
uint8_t current_tako_frame = 0;
// uint32_t tako_sleep = 0;


									
static const char PROGMEM tako_jump[TAKO_FRAMES][TAKO_SIZE] = 
{
// {
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x58, 0x54, 0x24, 0x22, 0x12, 0x12, 0x12, 
// 0x12, 0x12, 0x22, 0x24, 0x64, 0x58, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x08, 0x14, 0x12, 0xc9, 0x31, 0x88, 0x00, 0xa0, 0x20, 0x10, 0x90, 0x00, 0x00, 0x80, 0x00, 
// 0x00, 0x90, 0x10, 0x20, 0x20, 0x80, 0x00, 0x80, 0x00, 0x09, 0x31, 0xc2, 0x24, 0x28, 0x10, 0x00, 
// 0x00, 0x00, 0x5c, 0x43, 0xc0, 0x80, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x01, 0x81, 0x80, 0xc1, 
// 0xc1, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0x80, 0x87, 0x98, 0x60, 0x00
// },
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa0, 0x20, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x20, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x20, 0x50, 0x50, 0x50, 0x88, 0x48, 0x08, 0x04, 0x04, 0x03, 0x03, 0x02, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x24, 0x44, 0x88, 0x48, 0x50, 0x50, 0x20, 0x00, 
0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x10, 0x00, 0x12, 0x02, 0x01, 0x09, 0x10, 0x10, 0x08, 0x10, 
0x10, 0x09, 0x01, 0x02, 0x02, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1e, 0x21, 0x20, 0x20, 0x30, 0x38, 0x3c, 0x1c, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 
0x38, 0x3c, 0x3c, 0x18, 0x30, 0x20, 0x20, 0x20, 0x10, 0x18, 0x3c, 0x38, 0x21, 0x1e, 0x00, 0x00
},
{
0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x4c, 0x5a, 0x32, 0x21, 0x11, 0x11, 0x11, 
0x11, 0x11, 0x21, 0x32, 0x56, 0x5c, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 
0x00, 0x01, 0x02, 0x04, 0x85, 0x69, 0x19, 0x05, 0x20, 0x20, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x10, 0x10, 0x20, 0x20, 0x00, 0x00, 0x00, 0x05, 0x09, 0x35, 0xc5, 0x04, 0x02, 0x01, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02, 
0x02, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x04, 0x06, 0x0f, 0x0f, 0x0e, 0x04, 0x08, 0x08, 0x04, 0x06, 
0x06, 0x0e, 0x0c, 0x08, 0x08, 0x04, 0x02, 0x07, 0x07, 0x06, 0x04, 0x08, 0x07, 0x00, 0x00, 0x00
},
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x68, 0xc8, 0xcc, 0x44, 0x44, 0x44, 
0x44, 0xcc, 0xc8, 0xc8, 0x58, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x30, 0x50, 0x50, 0x48, 0x28, 0xc8, 0x04, 0x02, 0x01, 0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x80, 0x00, 0x01, 0x01, 0x01, 0x02, 0x02, 0x44, 0xa8, 0x48, 0x50, 0x50, 0x50, 0x60, 
0x00, 0x00, 0x80, 0x7c, 0x03, 0x00, 0x10, 0x00, 0x11, 0x01, 0x00, 0x08, 0x10, 0x10, 0x08, 0x10, 
0x10, 0x08, 0x00, 0x01, 0x01, 0x10, 0x00, 0x10, 0x00, 0x00, 0x01, 0x3e, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0x20, 0x20, 0x10, 0x30, 0x60, 0x40, 0x40, 0x20, 0x30, 0x78, 0x78, 0x30, 0x20, 
0x40, 0x40, 0x20, 0x30, 0x78, 0x78, 0x30, 0x20, 0x20, 0x20, 0x10, 0x18, 0x19, 0x06, 0x00, 0x00
},
{
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x40, 0x40, 0x40, 
0x40, 0x40, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x17, 0x1d, 0x08, 0x08, 0x08, 0x08, 0x08, 
0x08, 0x08, 0x08, 0x18, 0x1d, 0x17, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x02, 0x05, 0x04, 0xe2, 0x1a, 0x07, 0x41, 0x00, 0x48, 0x08, 0x04, 0x24, 0x40, 0x40, 0x20, 0x40, 
0x40, 0x24, 0x04, 0x08, 0x08, 0x40, 0x00, 0x40, 0x00, 0x02, 0x0e, 0x74, 0x85, 0x0a, 0x0c, 0x00, 
0x00, 0x00, 0x1e, 0x21, 0x60, 0x40, 0xe0, 0xf0, 0x60, 0x40, 0x80, 0x80, 0x80, 0x40, 0xe0, 0xf0, 
0xf0, 0xf0, 0x60, 0x40, 0x80, 0x80, 0x80, 0x40, 0x60, 0xf0, 0xe0, 0xc0, 0x43, 0x3c, 0x00, 0x00
}
};





static void draw_tako(void)
{if (get_current_wpm()!= 000) {
 	oled_set_cursor(0, 11); // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
	
	oled_write_raw_P(tako_jump[abs((TAKO_FRAMES - 1) - current_tako_frame)], TAKO_SIZE);
		
	if (timer_elapsed32(tako_timer) > TAKO_FRAME_DURATION) {
	current_tako_frame = (current_tako_frame + 1) % TAKO_FRAMES;
	tako_timer = timer_read32();
	}

}
else {
		oled_write_raw_P(tako_jump[3], TAKO_SIZE);
	}
}
