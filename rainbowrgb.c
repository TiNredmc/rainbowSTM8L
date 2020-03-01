/*
* rainbowSTM8L Library
*
* Coded to STM8L151F3U6 
* By TInLethax 
* 2020/03/01 
*
*/

#include "rainbowrgb.h"
#include "stm8l.h"
#include "delay.h"
#include <stdint.h>

int Brightness ;

/* GPIOs initialixe here, I use Port B
 uint8_t GloBri is Global Brightness of the LEDS
*/

void apa102_init(uint8_t GloBri) {
  PB_DDR |= (1 << apa102_data) | (1 << apa102_clk) ;
  PB_CR1 |= (1 << apa102_data) | (1 << apa102_clk) ;
  Brightness = GloBri ;
}

/* Insead of using SPI, I prefer bit-banging method
(Still working on SPI, tried to make it works but not, I mean not work at all (SPI needs Implementations)
 uint8_t c is the byte that you want to bit-banging into the LEDS chain
*/
void apa102_bitbang(uint8_t c) {
  uint8_t i;
  for (i=0; i<8 ;i++)
  {
    if (!(c&0x80)) {
     PB_ODR = (0 << apa102_data); // set data low

    } else {
     PB_ODR |=  (1 << apa102_data); // set data high

    }     
      PB_ODR |= (1<< apa102_clk); // SCK hi , data will be sampled when the clock rise
  c<<=1;
      PB_ODR = (0 << apa102_clk); // clk low, clock fall 


}
PB_ODR = (0 << apa102_data); // clear data pin 
}

/* Setled is the function to set the color of individual LED, by using 8 bit color, you can have as many color as 256^3 !
 uint8_t RedVal,GreVal,BluVal is the parameter you must set (can be 0) for showing out the color
 uint16_t leds is the n led you want to set the color, this variable is 16bit so you can have LEDs as much as 2^16 LEDs !
*/
void apa102_setleds(uint8_t RedVal, uint8_t GreVal, uint8_t BluVal, uint16_t leds)
{
uint16_t i ;
  PB_ODR = (0 << apa102_clk);  // initial state of clk is low
  
  
  apa102_bitbang(0x00);  // Start Frame 32bit data
  apa102_bitbang(0x00);
  apa102_bitbang(0x00);
  apa102_bitbang(0x00);	

  for (i=0; i<(leds+leds+leds); i+=3) // 32bit data
  {
    apa102_bitbang(0xe0+Brightness);  // Maximum global brightness
    apa102_bitbang(BluVal);
    apa102_bitbang(GreVal);
    apa102_bitbang(RedVal);
    //delay_us();
  }
	

  // End frame: 8+8*(leds >> 4) clock cycles    
  for (i=0; i<leds; i+=16)
  {
    apa102_bitbang(0x00);  // 8 more clock cycles
  }

}