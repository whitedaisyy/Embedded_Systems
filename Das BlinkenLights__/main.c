#include <msp430.h>

#define RED_LED BIT0    // P1.0
#define GREEN_LED BIT6  // P6.6
#define BUTTON BIT1   // P2.3

void delay(void)
{
    volatile unsigned int i;
    for(i=1000; i>0; i--); // Adjust the loop count for the desired delay
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    P1DIR |= RED_LED;      // Set red LED as output
    P6DIR |= GREEN_LED;    // Set green LED as output

    P1OUT |= RED_LED;      // Turn on red LED initially
    P6OUT &= ~GREEN_LED;   // Turn off green LED initially

    P4DIR &= ~BUTTON;      // Set button pin as input
    P4REN |= BUTTON;       // Enable pull-up resistor on button pin
    P4OUT |= BUTTON;       // Set pull-up resistor

    while (1)
    {
        if ((P4IN & BUTTON) == 0)  // Check if button is pressed (active low)
        {
            delay();  // Call delay function for debounce
            if ((P4IN & BUTTON) == 0)  // Check button again after debounce
            {
                P1OUT ^= RED_LED;     // Toggle red LED
                P6OUT ^= GREEN_LED;   // Toggle green LED
                while ((P4IN & BUTTON) == 0); // Wait for button release (active low)
                delay(); // Call delay function for debounce
            }
        }
    }
}
