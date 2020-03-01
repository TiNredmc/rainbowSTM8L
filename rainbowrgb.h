/*
* rainbowSTM8L Library
*
* Coded to STM8L151F3U6 
* By TInLethax 
* 2020/03/01 
*
*/

#ifndef RAINBOWRGB_H_
#define RAINBOWRGB_H_

#include <stdint.h>


#define apa102_clk  1    // Clk out pin PB1
#define apa102_data 2    // Data out pin PB2


void apa102_init(uint8_t GloBri);
void apa102_bitbang(uint8_t c);
void apa102_setleds(uint8_t RedVal, uint8_t GreVal, uint8_t BluVal, uint16_t leds);


#endif 
