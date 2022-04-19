// OLED STUFF STARTS HERE
// based on https://github.com/qmk/qmk_firmware/blob/master/keyboards/kyria/keymaps/j-inc/keymap.c

// In your rules.mk make sure you have:
// OLED_DRIVER_ENABLE = yes
// WPM_ENABLE = yes

// WPM-responsive animation stuff here    --------------------put speed so that it is always idle
#    define IDLEtako_FRAMES 4
#    define IDLEtako_SPEED 200  // below this wpm value your animation will IDLEtako

// #define PREPtako_FRAMES 1 // uncomment if >1

#    define MOVEtako_FRAMES 1
#    define MOVEtako_SPEED 200  // above this wpm value typing animation to trigger

#    define tako_FRAME_DURATION 100  // how long each frame lasts in ms
#    define tako_SIZE 144 // size of single image /number of bytes in array, minimize for adequate firmware size, max is 1024


uint32_t tako_timer         = 0;
uint32_t tako_sleep         = 0;
uint8_t  current_IDLEtako_frame = 0;
uint8_t current_MOVEtako_frame = 0;

// Code containing pixel arten
// To make your own pixel art:
// save a png/jpeg of an 128x32 image (resource: https://www.pixilart.com/draw )
// follow this guide up to and including "CONVERT YOUR IMAGE" https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
// replace numbers in brackets with your own
// if you start getting errors when compiling make sure you didn't accedentally delete a bracket



static void draw_tako(void) {  //frames = row,  size = column
    static const char PROGMEM IDLEtako[IDLEtako_FRAMES][tako_SIZE] = {{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x10, 0x20, 0x2c, 0x1a, 0x12, 0x12, 0x09, 0x09, 0x09, 
    0x09, 0x09, 0x09, 0x12, 0x12, 0x1a, 0x2c, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0x07, 0x10, 0x00, 0x14, 0x04, 0x02, 0x12, 0x20, 0x20, 0x10, 
    0x20, 0x20, 0x12, 0x02, 0x04, 0x14, 0x00, 0x10, 0x00, 0x07, 0x38, 0xc0, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x03, 0x04, 0x0c, 0x0c, 0x0c, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x18, 0x1c, 
    0x1c, 0x1c, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x0c, 0x0c, 0x08, 0x07, 0x00, 0x00, 0x00
},
{ 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x60, 0x90, 0x10, 0x90, 0x08, 0x0b, 0x06, 0x04, 0x04, 0x02, 0x02, 0x02, 
    0x02, 0x02, 0x04, 0x04, 0x06, 0x0b, 0x08, 0x08, 0x90, 0x10, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x80, 0x60, 0x1c, 0x03, 0x10, 0x00, 0x12, 0x02, 0x01, 0x09, 0x10, 0x10, 0x08, 
    0x10, 0x10, 0x09, 0x01, 0x02, 0x12, 0x00, 0x10, 0x00, 0x03, 0x3c, 0xe0, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0c, 0x0c, 0x08, 0x0c, 0x0c, 0x1e, 0x1e, 0x1e, 0x0c, 0x08, 
    0x10, 0x10, 0x08, 0x0c, 0x1e, 0x1e, 0x0c, 0x08, 0x08, 0x0c, 0x06, 0x06, 0x03, 0x00, 0x00, 0x00
},
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0xa0, 0xa0, 0xa0, 
    0xa0, 0xa0, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x88, 0x04, 0x02, 0x42, 0x41, 0x21, 0x21, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x21, 0x21, 0x41, 0x42, 0x02, 0x04, 0x88, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0x07, 0x00, 0x80, 0x82, 0x80, 0x00, 0x01, 0x02, 0x02, 0x81, 
    0x82, 0x82, 0x81, 0x00, 0x00, 0x02, 0x00, 0x82, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x03, 0x03, 0x03, 0x01, 0x02, 0x02, 0x01, 0x00, 
    0x01, 0x01, 0x03, 0x03, 0x02, 0x01, 0x01, 0x03, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
},
{ 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x38, 0x48, 0x88, 0x48, 0x04, 0x07, 0x06, 0x84, 0x82, 0x02, 0x02, 0x02, 
    0x02, 0x02, 0x82, 0x86, 0x06, 0x07, 0x04, 0x48, 0x88, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x20, 0x10, 0x0e, 0x01, 0x08, 0x00, 0x09, 0x01, 0x00, 0x04, 0x08, 0x08, 0x04, 
    0x08, 0x08, 0x04, 0x00, 0x01, 0x09, 0x00, 0x08, 0x01, 0x0e, 0x30, 0x40, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x0e, 0x0f, 0x06, 0x04, 0x08, 0x08, 0x0c, 0x0e, 0x0f, 
    0x06, 0x04, 0x08, 0x08, 0x08, 0x04, 0x06, 0x0f, 0x0e, 0x0c, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00
}
};

//     static const char PROGMEM PREPtako[][tako_SIZE] = { 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 
//     0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x00, 0x60, 0x90, 0x10, 0x90, 0x08, 0x0b, 0x06, 0x04, 0x04, 0x02, 0x02, 0x02, 
//     0x02, 0x02, 0x04, 0x04, 0x06, 0x0b, 0x08, 0x08, 0x90, 0x10, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x80, 0x60, 0x1c, 0x03, 0x10, 0x00, 0x12, 0x02, 0x01, 0x09, 0x10, 0x10, 0x08, 
//     0x10, 0x10, 0x09, 0x01, 0x02, 0x12, 0x00, 0x10, 0x00, 0x03, 0x3c, 0xe0, 0x80, 0x00, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0c, 0x0c, 0x08, 0x0c, 0x0c, 0x1e, 0x1e, 0x1e, 0x0c, 0x08, 
//     0x10, 0x10, 0x08, 0x0c, 0x1e, 0x1e, 0x0c, 0x08, 0x08, 0x0c, 0x06, 0x06, 0x03, 0x00, 0x00, 0x00
// };

    static const char PROGMEM MOVEtako[MOVEtako_FRAMES][tako_SIZE] = {{ 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x38, 0x48, 0x88, 0x48, 0x04, 0x07, 0x06, 0x84, 0x82, 0x02, 0x02, 0x02, 
    0x02, 0x02, 0x82, 0x86, 0x06, 0x07, 0x04, 0x48, 0x88, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x20, 0x10, 0x0e, 0x01, 0x08, 0x00, 0x09, 0x01, 0x00, 0x04, 0x08, 0x08, 0x04, 
    0x08, 0x08, 0x04, 0x00, 0x01, 0x09, 0x00, 0x08, 0x01, 0x0e, 0x30, 0x40, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x0e, 0x0f, 0x06, 0x04, 0x08, 0x08, 0x0c, 0x0e, 0x0f, 
    0x06, 0x04, 0x08, 0x08, 0x08, 0x04, 0x06, 0x0f, 0x0e, 0x0c, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00
} 
};



    // assumes 1 frame PREP stage
    void TAKOanimation_phase(void) {
        oled_set_cursor(0, 11);
        if (get_current_wpm() <= IDLEtako_SPEED) {
            current_IDLEtako_frame = (current_IDLEtako_frame + 1) % IDLEtako_FRAMES;
            oled_write_raw_P(IDLEtako[abs((IDLEtako_FRAMES - 1) - current_IDLEtako_frame)], tako_SIZE);
        }
        // if (get_current_wpm() > IDLEtako_SPEED && get_current_wpm() < MOVEtako_SPEED) {
        //     oled_write_raw_P(PREPtako[abs((PREPtako_FRAMES-1)-current_PREPtako_frame)], tako_SIZE); // uncomment if IDLEtako_FRAMES >1
        //     // oled_write_raw_P(PREPtako[0], tako_SIZE);  // remove if IDLEtako_FRAMES >1
        // }
        if (get_current_wpm() >= MOVEtako_SPEED) {
            current_MOVEtako_frame = (current_MOVEtako_frame + 1) % MOVEtako_FRAMES;
            oled_write_raw_P(MOVEtako[abs((MOVEtako_FRAMES - 1) - current_MOVEtako_frame)], tako_SIZE);
        }
    }


    //  timeout - need tako_sleep
    if (get_current_wpm() != 000) {
        oled_on();  // not essential but turns on animation OLED with any alpha keypress
        if (timer_elapsed32(tako_timer) > tako_FRAME_DURATION) {
            tako_timer = timer_read32();
            TAKOanimation_phase();
        }
        tako_sleep = timer_read32();
    } else {
        if (timer_elapsed32(tako_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(tako_timer) > tako_FRAME_DURATION) {
                tako_timer = timer_read32();
                TAKOanimation_phase();
            }
        }
    }

}



