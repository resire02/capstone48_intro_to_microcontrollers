/*

  MakerFaire 2024 Demo 
  AVR64DD32 + CNano Board


*/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_MCP23008.h"
// #include <Adafruit_NeoPixel.h>
#include <tinyNeoPixel.h>

// IO Extenders 

tinyNeoPixel pixel_ring = tinyNeoPixel(8, PIN_PC3, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel pixel_ring(8,PIN_PC3,NEO_GRB + NEO_KHZ800);
void pixel_ring_test(void);
void draw_meatball(void) ;
void animate_meatball(void);

Adafruit_MCP23008 mcp_joystick,mcp_leds;
void led_test(void);


// OLED screen 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define NUMMEATBALLS  2
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define MEATBALL_H    51
#define MEATBALL_W    52


const unsigned char meatball [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xff, 
	0xf0, 0xff, 0xff, 0x80, 0x00, 0x0e, 0x1f, 0xf0, 0xff, 0xfe, 0x00, 0x00, 0x06, 0x1f, 0xf0, 0xff, 
	0xfc, 0x00, 0x00, 0x02, 0x1f, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0x02, 0x3f, 0xf0, 0xff, 0xe0, 0x00, 
	0x00, 0x01, 0xff, 0xf0, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xf0, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0xff, 0xf0, 0xff, 0x80, 0x10, 0x00, 0x20, 0x7f, 0xf0, 0xff, 0x00, 0x3c, 0x00, 0x70, 0x7f, 0xf0, 
	0xff, 0x00, 0x7c, 0x00, 0xf8, 0x3f, 0xf0, 0xfe, 0x00, 0x7e, 0x01, 0xf8, 0x1f, 0xf0, 0xfe, 0x00, 
	0xff, 0x01, 0xfc, 0x1f, 0xf0, 0xfc, 0x01, 0xff, 0x03, 0xfe, 0x0f, 0xf0, 0xfc, 0x00, 0xff, 0x83, 
	0xfe, 0x07, 0xf0, 0xfc, 0x00, 0xff, 0xc1, 0xff, 0x07, 0xf0, 0xfc, 0x00, 0x7f, 0xc1, 0xff, 0x03, 
	0xf0, 0xf8, 0x00, 0x7f, 0xe0, 0xff, 0x81, 0xf0, 0xf8, 0x08, 0x3f, 0xf0, 0xff, 0xc1, 0xf0, 0xf8, 
	0x1c, 0x1f, 0xf0, 0x7f, 0xc0, 0xf0, 0xf8, 0x3e, 0x1f, 0xf8, 0x3f, 0xe0, 0x70, 0xf8, 0x3e, 0x0f, 
	0xf8, 0x3f, 0xf0, 0x70, 0xf8, 0x7f, 0x07, 0xfc, 0x1f, 0xf0, 0x70, 0xfc, 0xff, 0x83, 0xfe, 0x0f, 
	0xf8, 0x70, 0xfd, 0xff, 0x83, 0xfe, 0x0f, 0xfc, 0xf0, 0xff, 0xff, 0x01, 0xff, 0x07, 0xfc, 0xf0, 
	0xff, 0xff, 0x01, 0xff, 0x03, 0xff, 0xf0, 0xff, 0xfe, 0x00, 0xfe, 0x03, 0xff, 0xf0, 0xff, 0xfc, 
	0x00, 0xfc, 0x01, 0xff, 0xf0, 0xff, 0xf8, 0x00, 0x78, 0x00, 0xff, 0xf0, 0xff, 0xf8, 0x00, 0x38, 
	0x00, 0xff, 0xf0, 0xff, 0xf0, 0x00, 0x10, 0x00, 0x7f, 0xf0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x3f, 
	0xf0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0xff, 
	0xf8, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xf0, 0xff, 0xff, 0x80, 
	0x00, 0x07, 0xff, 0xf0, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x00, 0xff, 
	0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0
};

void setup() 
{
  
  uint8_t pin_id,status;
  
  Serial.swap(3);       // access correct CNano CDC pair
  Serial.begin(115200);

  delay(1000);
  Serial.println(F("CNano Explorer + AVR64DD32"));

  Serial.println(F("Init OLED...."));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
   {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
   }
  
  display.clearDisplay();
  display.display();

  Serial.println(F("OLED init complete...."));

  status = mcp_joystick.begin(0x24);       // create the joystick interface
  Serial.print("joystick status : ");
  Serial.println(status);
  // set up as all inputs with pull ups
  for(pin_id = 0;pin_id < 8;pin_id++)
    {
        mcp_joystick.pinMode(pin_id,INPUT);
        mcp_joystick.pullUp(pin_id,HIGH);

    }
  
  status = mcp_leds.begin(0x25);
  Serial.print("LED status : ");
  Serial.println(status);

  for(pin_id = 0;pin_id < 8;pin_id++)
    {
        mcp_leds.pinMode(pin_id,OUTPUT);
        mcp_leds.digitalWrite(pin_id,HIGH);   

    }

  pixel_ring.begin();
  
}

void pixel_ring_test(void)
{

  int pixel_index;

  pixel_ring.begin();
  for(pixel_index = 0;pixel_index < 8;pixel_index++)
  {

    pixel_ring.setPixelColor(pixel_index,0x00007f);

  }
  
  // pixel_ring.show();

}


void draw_meatball(void) 
{
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - MEATBALL_W ) / 2,
    (display.height() - MEATBALL_H) / 2,
    meatball, MEATBALL_W, MEATBALL_H, 1);
  display.display();

}

void animate_meatball(void)
{
  
  int8_t x_pos, y_pos,dx,dy;

  x_pos = (display.width() - MEATBALL_W ) / 2;
  y_pos = 0;

  while(1)
  {
       display.clearDisplay();
       display.drawBitmap(x_pos,y_pos, meatball, MEATBALL_W, MEATBALL_H, 1);
       display.display();
       delay(200);
       
       y_pos += 2;
       if(y_pos >= display.height())
        y_pos = -MEATBALL_H;
  }

}

void loop()
{
    
  ring_chase();
  meatball_drop();
  cylon();

}

unsigned long color_grid[3] = {0x00007f,0x007f00,0x7f0000};

void ring_chase(void)
{
  static unsigned long ring_timer = 0UL;
  unsigned long now;
  static uint8_t pixel_index = 0,color_index = 0;


   now = millis();
   if(now - ring_timer > 211UL)
   {

      ring_timer = now;
      pixel_ring.clear();
      pixel_ring.show();    
      pixel_ring.setPixelColor(pixel_index,color_grid[color_index]);
      pixel_ring.show();
      pixel_index++;
      if(pixel_index > 7)
             pixel_index = 0;
      color_index++;
      if(color_index > 3)
        color_index = 0;
       
   }

}

void meatball_drop(void)
{
  static unsigned long meatball_timer = 0UL;
  unsigned long now;
  static int8_t x_pos = ((display.width() - MEATBALL_W ) / 2), y_pos = -MEATBALL_H,dx = 0;

  now = millis();
  if(now - meatball_timer > 101UL)
  {
     meatball_timer = now;
     display.clearDisplay();
     display.drawBitmap(x_pos,y_pos, meatball, MEATBALL_W, MEATBALL_H, 1);
     display.display();

     y_pos += 2;
       if(y_pos >= display.height())
          {
            y_pos = -MEATBALL_H;
            x_pos = ((display.width() - MEATBALL_W ) / 2);
            dx = (random(1,10) > 5 ? -15 : 15);
            x_pos += dx;
          }
  }

}

void cylon(void)
{
    static uint8_t led_index = 0,led_state = false,led_dir = true;
    static unsigned long cylon_timer = 0UL;
    unsigned long now;
    uint8_t clr_index;

    now = millis();
    if(now - cylon_timer > 37UL)
    {
        cylon_timer = now;
        if(led_state)
          {
              led_state = false;
              mcp_leds.digitalWrite(led_index,HIGH);
          }
        else
          {
            led_state = true;
            mcp_leds.digitalWrite(led_index,LOW);
          }
        
        if(led_state == false)
        {
           if(led_dir)
            {
              led_index++;
              if(led_index > 7)
                {
                  led_index = 7;
                  led_dir = false;
                }
            }
           else
              {
                led_index--;
                if(led_index > 127)     // unsigned 8 bit gone negative
                  {
                    led_index = 0;
                    led_dir = true;
                  }
              }
        }
  }

}




void led_test(void)
{

  uint8_t pin_id;

  for(pin_id = 0;pin_id < 8;pin_id++)
    {
      mcp_leds.digitalWrite(pin_id,LOW);
      delay(100);
      mcp_leds.digitalWrite(pin_id,HIGH);
      delay(400);
    }

}


