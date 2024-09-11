#include <avr/io.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>


u8 ledCount = 0;

void LED_Control(u8 ledCount) {
    switch (ledCount) {
        case 1:
            DIO_setPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);
            break;
        case 2:
            DIO_setPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);
            DIO_setPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_HIGH);
            break;
        case 3:
            DIO_setPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_HIGH);
            DIO_setPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_HIGH);
            DIO_setPinValue(DIO_PORTB, DIO_PIN3, DIO_PIN_HIGH);
            break;
        default:
            // Turn off all LEDs
            DIO_setPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
            DIO_setPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_LOW);
            DIO_setPinValue(DIO_PORTB, DIO_PIN3, DIO_PIN_LOW);
            break;
    }
}

int main() {
    EXTI_enable(EXTI_INT0, EXTI_RISING_EDGE);
    EXTI_enable(EXTI_INT1, EXTI_RISING_EDGE);

    DIO_setPinDirection(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);

    sei();

    while (1) {
        // Wait here or perform other tasks as needed
    }
}

// External Interrupt 0 ISR
void __vector_1(void) __attribute__((signal));
void __vector_1(void) {
    ledCount++;
    if (ledCount > 3) {
        ledCount = 0;
    }
    LED_Control(ledCount);
}

// External Interrupt 1 ISR
void __vector_2(void) __attribute__((signal));
void __vector_2(void) {
	ledCount--;
    if (ledCount == 2 ) {

        DIO_setPinValue(DIO_PORTB, DIO_PIN3, DIO_PIN_LOW);
    }
    if (ledCount == 1 ) {

          DIO_setPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_LOW);
      }
    if (ledCount == 0 ) {

          DIO_setPinValue(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
      }
}
