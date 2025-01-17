// Bob's pin definitions for PIC16F1829 for I2C communication:
#define res pin_b5
#define sa0 pin_c2=1
#define scl pin_b6
#define sda pin_b4



/*  Kennys pin assignments for PIC18F4550 for I2C communication:
#define res pin_b3
#define sa0 pin_b2=1
#define scl pin_b1
#define sda pin_b0
*/


// Number of pixels in LCD
#define LCD_X     128
#define LCD_Y     64


int char_row,charsel,charpos,chardata;       // for nokia_5110 lcd

int16 ddram;

//char plot_value;

int32 plot_value32;

int32 plot_umsb,plot_lmsb,plot_ulsb,plot_llsb;

// ASCII table for NOKIA LCD and OLED: 96 rows * 5 bytes= 480 bytes

BYTE const TABLE5[240]=            {0x00,0x00,0x00,0x00,0x00,     //  20 space 

  0x00,0x00,0x5f,0x00,0x00,   // 21 !
  0x00,0x07,0x00,0x07,0x00,   // 22 "
  0x14,0x7f,0x14,0x7f,0x14,   // 23 #
//  0x24,0x2a,0x7f,0x2a,0x12,   // 24 $   // original pixels for "$" symbol
  0x06,0x09,0x09,0x06,0x00,   // 24 $     
// I have changed the display value for the ASCII symbol "$" to the degree symbol "�"  RG Dennis
  0x23,0x13,0x08,0x64,0x62,   // 25 %
  0x36,0x49,0x55,0x22,0x50,   // 26 &
  0x00,0x05,0x03,0x00,0x00,   // 27 '
  0x00,0x1c,0x22,0x41,0x00,   // 28 (
  0x00,0x41,0x22,0x1c,0x00,   // 29 )
  0x14,0x08,0x3e,0x08,0x14,   // 2a *
  0x08,0x08,0x3e,0x08,0x08,   // 2b +
  0x00,0x50,0x30,0x00,0x00,   // 2c ,
  0x08,0x08,0x08,0x08,0x08,   // 2d -
  0x00,0x60,0x60,0x00,0x00,   // 2e .
  0x20,0x10,0x08,0x04,0x02,   // 2f /
  0x3e,0x51,0x49,0x45,0x3e,   // 30 0
  0x00,0x42,0x7f,0x40,0x00,   // 31 1
  0x42,0x61,0x51,0x49,0x46,   // 32 2
  0x21,0x41,0x45,0x4b,0x31,   // 33 3
  0x18,0x14,0x12,0x7f,0x10,   // 34 4
  0x27,0x45,0x45,0x45,0x39,   // 35 5
  0x3c,0x4a,0x49,0x49,0x30,   // 36 6
  0x01,0x71,0x09,0x05,0x03,   // 37 7
  0x36,0x49,0x49,0x49,0x36,   // 38 8
  0x06,0x49,0x49,0x29,0x1e,   // 39 9
  0x00,0x36,0x36,0x00,0x00,   // 3a :
  0x00,0x56,0x36,0x00,0x00,   // 3b ;
  0x08,0x14,0x22,0x41,0x00,   // 3c <
  0x14,0x14,0x14,0x14,0x14,   // 3d =
  0x00,0x41,0x22,0x14,0x08,   // 3e >
  0x02,0x01,0x51,0x09,0x06,   // 3f ?
  0x32,0x49,0x79,0x41,0x3e,   // 40 @
  0x7e,0x11,0x11,0x11,0x7e,   // 41 A
  0x7f,0x49,0x49,0x49,0x36,   // 42 B
  0x3e,0x41,0x41,0x41,0x22,   // 43 C
  0x7f,0x41,0x41,0x22,0x1c,   // 44 D
  0x7f,0x49,0x49,0x49,0x41,   // 45 E
  0x7f,0x09,0x09,0x09,0x01,   // 46 F
  0x3e,0x41,0x49,0x49,0x7a,   // 47 G
  0x7f,0x08,0x08,0x08,0x7f,   // 48 H
  0x00,0x41,0x7f,0x41,0x00,   // 49 I
  0x20,0x40,0x41,0x3f,0x01,   // 4a J
  0x7f,0x08,0x14,0x22,0x41,   // 4b K
  0x7f,0x40,0x40,0x40,0x40,   // 4c L
  0x7f,0x02,0x0c,0x02,0x7f,   // 4d M
  0x7f,0x04,0x08,0x10,0x7f,   // 4e N
  0x3e,0x41,0x41,0x41,0x3e    // 4f O
};   


BYTE const TABLE6[240]=            {0x7f,0x09,0x09,0x09,0x06,   // 50 P
  0x3e,0x41,0x51,0x21,0x5e,   // 51 Q
  0x7f,0x09,0x19,0x29,0x46,   // 52 R
  0x46,0x49,0x49,0x49,0x31,   // 53 S
  0x01,0x01,0x7f,0x01,0x01,   // 54 T
  0x3f,0x40,0x40,0x40,0x3f,   // 55 U
  0x1f,0x20,0x40,0x20,0x1f,   // 56 V
  0x3f,0x40,0x38,0x40,0x3f,   // 57 W
  0x63,0x14,0x08,0x14,0x63,   // 58 X
  0x07,0x08,0x70,0x08,0x07,   // 59 Y
  0x61,0x51,0x49,0x45,0x43,   // 5a Z
  0x00,0x7f,0x41,0x41,0x00,   // 5b [
  0x02,0x04,0x08,0x10,0x20,   // 5c
  0x00,0x41,0x41,0x7f,0x00,   // 5d
  0x04,0x02,0x01,0x02,0x04,   // 5e
  0x40,0x40,0x40,0x40,0x40,   // 5f
  0x00,0x01,0x02,0x04,0x00,   // 60
  0x20,0x54,0x54,0x54,0x78,   // 61 a
  0x7f,0x48,0x44,0x44,0x38,   // 62 b
  0x38,0x44,0x44,0x44,0x20,   // 63 c
  0x38,0x44,0x44,0x48,0x7f,   // 64 d
  0x38,0x54,0x54,0x54,0x18,   // 65 e
  0x08,0x7e,0x09,0x01,0x02,   // 66 f
  0x0c,0x52,0x52,0x52,0x3e,   // 67 g
  0x7f,0x08,0x04,0x04,0x78,   // 68 h
  0x00,0x44,0x7d,0x40,0x00,   // 69 i
  0x20,0x40,0x44,0x3d,0x00,   // 6a j
  0x7f,0x10,0x28,0x44,0x00,   // 6b k
  0x00,0x41,0x7f,0x40,0x00,   // 6c l
  0x7c,0x04,0x18,0x04,0x78,   // 6d m
  0x7c,0x08,0x04,0x04,0x78,   // 6e n
  0x38,0x44,0x44,0x44,0x38,   // 6f o
  0x7c,0x14,0x14,0x14,0x08,   // 70 p
  0x08,0x14,0x14,0x18,0x7c,   // 71 q
  0x7c,0x08,0x04,0x04,0x08,   // 72 r
  0x48,0x54,0x54,0x54,0x20,   // 73 s
  0x04,0x3f,0x44,0x40,0x20,   // 74 t
  0x3c,0x40,0x40,0x20,0x7c,   // 75 u
  0x1c,0x20,0x40,0x20,0x1c,   // 76 v
  0x3c,0x40,0x30,0x40,0x3c,   // 77 w
  0x44,0x28,0x10,0x28,0x44,   // 78 x
  0x0c,0x50,0x50,0x50,0x3c,   // 79 y
  0x44,0x64,0x54,0x4c,0x44,   // 7a z
  0x00,0x08,0x36,0x41,0x00,   // 7b
  0x00,0x00,0x7f,0x00,0x00,   // 7c
  0x00,0x41,0x36,0x08,0x00,   // 7d
  0x10,0x08,0x08,0x10,0x08,   // 7e
  0x78,0x46,0x41,0x46,0x78    // 7f
}; 


void iic_start(){
output_high(scl);
delay_us(1);
output_high(sda);
delay_us(1);
output_low(sda);
delay_us(1);
output_low(scl);
delay_us(1);
}

void iic_stop(){
output_low(scl);
delay_us(1);
output_low(sda);
delay_us(1);
output_high(scl);
delay_us(1);
output_high(sda);
delay_us(1);
}

void iic_write(byte iic_byte){
int i;
for (i=0;i<8;i++) {
output_bit(sda, shift_left(&iic_byte,1,0));
output_high(scl) ;
delay_us(1);
output_low(scl) ;
delay_us(1);
}
output_high(sda);
output_high(scl);
delay_us(1);
output_low(scl);
delay_us(1);
}

void oled_write_data(byte iic_data){
iic_start();
iic_write(0x78);
iic_write(0x40);
iic_write(iic_data);
iic_stop();
}

void oled_write_command(byte iic_command){
iic_start();
iic_write(0x78);
iic_write(0x00);
iic_write(iic_command);
iic_stop();
}

void initialise_screen(){
oled_write_command(0xae);
oled_write_command(0x20);
oled_write_command(0x10);
oled_write_command(0xb0);
oled_write_command(0xc8);
oled_write_command(0x00);
oled_write_command(0x10);
oled_write_command(0x40);
oled_write_command(0x81);
oled_write_command(0xaf);
oled_write_command(0xa1);
oled_write_command(0xa6);
oled_write_command(0xa8);
oled_write_command(0x3f);
oled_write_command(0xa4);
oled_write_command(0xd3);
oled_write_command(0x00);
oled_write_command(0xd5);
oled_write_command(0xf0);
oled_write_command(0xd9);
oled_write_command(0x22);
oled_write_command(0xda);
oled_write_command(0x12);
oled_write_command(0xdb);
oled_write_command(0x20);
oled_write_command(0x8d);
oled_write_command(0x14);
oled_write_command(0xaf);
}

void table_to_oled(void){
if (charsel<0x20)return;
  if (charsel>0x7f)return;

  for (char_row=0;char_row<5;char_row++) {      // 5 bytes

    if (charsel<0x50){charpos=(((charsel&0xff)-0x20)*5);chardata=TABLE5[(charpos+char_row)];}            // use TABLE5
    else if (charsel>0x4f){charpos=(((charsel&0xff)-0x50)*5);chardata=TABLE6[(charpos+char_row)];}            // use TABLE6


    oled_write_data(chardata);      // send data to oled
  }

  oled_write_data(0x00);      //    1 byte (always blank)

}

void oled_printchar(int cvar){
charsel=cvar;
table_to_oled();
}



void clear_screen(void){
int m,n;
for(m=0;m<8;m++){
oled_write_command(0xb0+m);
oled_write_command(0x00);
oled_write_command(0x10);
for(n=0;n<128;n++) {
oled_write_data(0x00);
}
}
}

void fill_screen(void){
int m,n;
for(m=0;m<8;m++){
oled_write_command(0xb0+m);
oled_write_command(0x00);
oled_write_command(0x10);
for(n=0;n<128;n++) {
oled_write_data(0xff);
}
}
}

void oled_gotoxy(int page, int column){
byte column_lower=0x00;
byte column_upper=0x10;
byte page_start=0xb0;
page_start=page_start+page;
column_upper=(column_upper+column/16);
column_lower=(column_lower+column%16);
oled_write_command(page_start);
oled_write_command(column_lower);
oled_write_command(column_upper);
}

void oled_zoom(void){
//  These four lines (two 2-byte commands) set ZOOM IN mode (characters are twice as high)
//  see SSD1306-1.2 user manual for OLED driver, pages 33, 34, and 49
  oled_write_command(0xda);     
  oled_write_command(0x12);
  oled_write_command(0xd6);
  oled_write_command(0x01);
}

void vertical_line(int length){

}

void oled_drawbox(int width, int height){

}
