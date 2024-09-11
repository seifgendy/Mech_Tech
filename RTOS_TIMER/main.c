#define F_CPU 16000000UL
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"

#include "ADC_interface.h"
#include "LCD_interface.h"

int main() {
	/* Initialize ADC and LCD */
	ADC_init(ADC_REFERENCE_AVCC); // Set reference voltage to 2.56v
	LCD_init();


	/* Variables for ADC and LCD */
	u16 digitalValue = 0;
	u16 digitalValue0 = 0;
	u16 digitalValue1 = 0;
	u16 digitalValue2 = 0;



	while (1) {
		/* Read ADC value from Potentiometer */
		ADC_getDigitalValue(ADC_CHANNEL_0, &digitalValue0);
		ADC_getDigitalValue(ADC_CHANNEL_1, &digitalValue);
		ADC_getDigitalValue(ADC_CHANNEL_2, &digitalValue1);
		ADC_getDigitalValue(ADC_CHANNEL_3, &digitalValue2);


		if (digitalValue0<44 && digitalValue<182 && digitalValue1>129 && digitalValue2<40) {
			LCD_clear();
			LCD_writeString("Incredible");
			_delay_ms(1000);
		}
		else if (digitalValue0<44 && digitalValue<182 && digitalValue1>129 && digitalValue2>42) {
			LCD_clear();
			LCD_writeString("love you");
			_delay_ms(1000);
		}
		else if (digitalValue0<44 && digitalValue>185 && digitalValue1>129 && digitalValue2>42) {
			LCD_clear();
			LCD_writeString("I really love you");
			_delay_ms(1000);
		}
		else if (digitalValue0<44 && digitalValue<184 && digitalValue1<115 && digitalValue2<42) {
			LCD_clear();
			LCD_writeString("I'm watching you");
			_delay_ms(1000);
		}
		else if (digitalValue0<44 && digitalValue<184 && digitalValue1<115 && digitalValue2>44) {
			LCD_clear();
			LCD_writeString("good job");
			_delay_ms(1000);
		}
		else if (digitalValue0>44 && digitalValue>185 && digitalValue1>129 && digitalValue2>42) {
			LCD_clear();
			LCD_writeString("Have a nice life");
			_delay_ms(1000);
		}
		else if (digitalValue0<50 && digitalValue>195 && digitalValue1<115 && digitalValue2<60) {
			LCD_clear();
			LCD_writeString("Perfect");
			_delay_ms(1000);
		}

		else if (digitalValue0>44 && digitalValue<182 && digitalValue1>129 && digitalValue2<40) {
					LCD_clear();
					LCD_writeString("good night");
					_delay_ms(1000);
				}
		else if (digitalValue0<44 && digitalValue>182 && digitalValue1>129 && digitalValue2<40) {
					LCD_clear();
					LCD_writeString("good morning");
					_delay_ms(1000);
				}
		else if (digitalValue0<44 && digitalValue>182 && digitalValue1>129 && digitalValue2>40) {
					LCD_clear();
					LCD_writeString("get will soon");
					_delay_ms(1000);
				}

		else if (digitalValue0>44 && digitalValue>182 && digitalValue1<129 && digitalValue2>40) {
					LCD_clear();
					LCD_writeString("no room for mistakes");
					_delay_ms(1000);
				}
		else if (digitalValue0<44 && digitalValue>182 && digitalValue1<129 && digitalValue2<40) {
					LCD_clear();
					LCD_writeString("no way");
					_delay_ms(1000);
				}
		else if (digitalValue0<44 && digitalValue<184 && digitalValue1<115 && digitalValue2<44) {
					LCD_clear();
					LCD_writeString("ohh i forgot");
					_delay_ms(1000);
				}
		else if (digitalValue0>44 && digitalValue>184 && digitalValue1<115 && digitalValue2>44) {
					LCD_clear();
					LCD_writeString("my bad");
					_delay_ms(1000);
				}
		else if (digitalValue0>44 && digitalValue<184 && digitalValue1>115 && digitalValue2>44) {
					LCD_clear();
					LCD_writeString("sorry");
					_delay_ms(1000);
				}





	}

	return 0;
}
