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

#include "../include/adc0.h"

/**
 * \brief Initialize ADC interface
 */
int8_t ADC_0_init()
{

	// 	ADC0.CALIB = ADC_DUTYCYC_DUTY50_gc; /* Duty Cycle: 50% Duty cycle */

	// 	ADC0.CTRLB = ADC_SAMPNUM_ACC1_gc; /* Accumulation Samples: 1 ADC sample */

		ADC0.CTRLC = ADC_PRESC_DIV2_gc /* Clock Pre-scaler: CLK_PER divided by 2 */
					| ADC_REFSEL_VDDREF_gc /* Reference Selection: VDD */
					| 1 << ADC_SAMPCAP_bp; /* Sample Capacitance Selection: enabled */

	// 	ADC0.CTRLD = ADC_ASDV_ASVOFF_gc /* Automatic Sampling Delay Variation: The Automatic Sampling Delay Variation is disabled */
	// 				| ADC_INITDLY_DLY0_gc /* Initial Delay Selection: Delay 0 CLK_ADC cycles */
	// 				| 0 << ADC_SAMPDLY_gp; /* Sampling Delay Selection: 0 */

	// 	ADC0.CTRLE = ADC_WINCM_NONE_gc; /* Window Comparator Mode: No Window Comparison */

	// 	ADC0.DBGCTRL = 0 << ADC_DBGRUN_bp; /* Debug run: disabled */

	// 	ADC0.EVCTRL = 0 << ADC_STARTEI_bp; /* Start Event Input Enable: disabled */

	// 	ADC0.INTCTRL = 0 << ADC_RESRDY_bp /* Result Ready Interrupt Enable: disabled */
	// 				| 0 << ADC_WCMP_bp; /* Window Comparator Interrupt Enable: disabled */

		ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc; /* Analog Channel Selection Bits: ADC input pin 6 */

		ADC0.SAMPCTRL = 10 << ADC_SAMPLEN_gp; /* Sample lenght: 10 */

	// 	ADC0.WINHT = 0; /* Window comparator high threshold */

	// 	ADC0.WINLT = 0; /* Window comparator low threshold */

	
		ADC0.CTRLA = 1 << ADC_ENABLE_bp /* ADC Enable: enabled */
					| 0 << ADC_FREERUN_bp /* ADC Freerun mode: disabled */
					| ADC_RESSEL_8BIT_gc /* ADC Resolution: 8-bit mode */
					| 0 << ADC_RUNSTBY_bp; /* Run standby mode: disabled */

	return 0;
}

ISR(ADC0_RESRDY_vect)
        {
            /* Insert your ADC result ready interrupt handling code here */

            /* The interrupt flag has to be cleared manually */
            ADC0.INTFLAGS = ADC_RESRDY_bm;
        }
ISR(ADC0_WCOMP_vect)
    {
        /* Insert your ADC window comparator interrupt handling code here */

        /* The interrupt flag has to be cleared manually */
        ADC0.INTFLAGS = ADC_WCMP_bm;
    }

