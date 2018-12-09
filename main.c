/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/include/pin_manager.h"
#include "mcc_generated_files/config/clock_config.h" // why is this not automatic??
#include <util/delay.h>
#include <avr/io.h>

// WARNING!!! I changed "*link_data_start" in
//E:\Program Files (x86)\Microchip\MPLABX\v5.10\packs\Atmel\ATtiny_DFP\1.3.238\gcc\dev\attiny1614\device-specs\specs-attiny1614
// from "-Tdata 0x803800" to "	-Tdata 0x802000"
// this prevents a linker error for static or global variables.
// But I'm very uncertain if this is actually correct.
// I also set the fuses BOOTEND to 4 and APPEND to 8, not sure if necessary and weird if it is...
// Could cause problems if the code were longer maybe??

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))


void show_num(uint8_t num) {
    IO_PA3_set_level(bit_get(num, BIT(0)));
    IO_PA5_set_level(bit_get(num, BIT(1)));
    IO_PA4_set_level(bit_get(num, BIT(2)));
    IO_PA7_set_level(bit_get(num, BIT(3)));
    IO_PB3_set_level(bit_get(num, BIT(4)));
    IO_PB2_set_level(bit_get(num, BIT(5)));
}

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    
    uint8_t num_sides = 0;
    uint8_t roll = 0;
    /* Replace with your application code */
    while (1){
        if (!IO_PA1_get_level()){
			while (1){
				while (!IO_PA1_get_level()) {
					roll = 1 + rand() % num_sides;
					show_num(roll);
					_delay_ms(10);
				}
				_delay_ms(20);
			}
		}
        ADC0.COMMAND = 1; // start ADC conversion
        while (ADC0.COMMAND); // wait until done
        num_sides = ADC0.RESL / 4;
        show_num(num_sides);
        _delay_ms(20);
    }
}
/**
    End of File
*/