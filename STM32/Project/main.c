#include "ws2812b.h"
#include "delay.h"

#define RED 		0xff0000
#define ORANGE 	0xff7f00
#define YELLOW 	0xffff00
#define GREEN 	0x00ff00
#define BLUE 		0x0000ff
#define INDIGO 	0x4b0082
#define VIOLET 	0x9400d3
#define WHITE 	0xffffff

void rainbow(uint8_t wait);
uint32_t Wheel(uint8_t WheelPos);
void rainbowCycle(uint8_t wait);

int main()
{
    ws2812bInit();
		delay_init(72000000);
    
    if(!ws2812bTest()) while(1);
    while(1)
    {
//			rainbow(30);
//			delay_ms(10);
//			for (int i=0; i<7; i++) {
//				rainbow7(i, 20); // starting at i, draw the 7 color rainbow
			rainbowCycle(10);
    }

}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<8; i++) {
      ws2812bSet(i, Wheel(j));
    }
    delay_ms(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(uint8_t WheelPos) {	
	 WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return setvalue(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return setvalue(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return setvalue(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 8; i++) {
      ws2812bSet(i, Wheel(((i * 256 / 8) + j) & 255));
    }
    delay_ms(wait);
  }
}


