
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"

int main() {
    /* Initialize ADC and LCD */
    ADC_init(ADC_REFERENCE_AVCC); // Set reference voltage to 2.56v
    LCD_init();

    /* Variables for ADC and LCD */
    u16 digitalValue = 0;
    long long int voltage_mv = 0;


    while (1) {
        /* Read ADC value from Potentiometer */
        ADC_getDigitalValue(ADC_CHANNEL_1, &digitalValue);
        /* Convert ADC value to voltage in mV */
        voltage_mv = (u16)((u32)digitalValue * 5000UL / 1023UL);
        /* Display voltage on LCD */
        LCD_clear();
        LCD_writeString("Voltage:");

        LCD_SendNumber4bit(voltage_mv );

        _delay_ms(1000); // Delay for one second before reading ADC again
    }

    return 0;
}
