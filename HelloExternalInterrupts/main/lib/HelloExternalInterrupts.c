#include<avr/io.h>

#include<Serial.h>
#include<util/delay.h>
#include<DigitalServiceHandler.h>

void Serial::UART::onDataReceiveCompleted(const uint8_t& data) {
          Serial::UART::getInstance()->println(data, 10);

}

void Serial::UART::onDataTransmitCompleted(const uint8_t& data) {

}

/**
 * @brief Triggered when the PIN state is changing (From HIGH to LOW -- Falling edge -- LOGIC = 1) and (From LOW to HIGH -- Rising edge -- LOGIC = 0) 
 */
void GPIO::ExternalInterruptHandler::onPinChanged() {
      /* print on the RISING edge (when PD4 is still LOW) -- FROM LOW TO HIGH Logic*/
      if (!isPCINT20Active()) {
          Serial::UART::getInstance()->sprintln((char*) "ON -- RISING EDGE");
          /* set the pin to HIGH LEVEL as of after the RISING EDGE */
          PORTD |= (1 << PD4);
      } else if (isPCINT20Active()) {
          Serial::UART::getInstance()->sprintln((char*) "OFF -- FALLING EDGE");
          /* set the pin to LOW LEVEL as of after the FALLING EDGE */
          PORTD &= ~(1 << PD4);
      }
      reti(); /* exit to the main function */
}

int main(void) {
    Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600);
    // /* Write PD4 to LOW */
    // PORTD &= ~(1 << PD4);
    // /* activate the external interrupt service routine handler on the PCINT20/PD4 */
    // GPIO::ExternalInterruptHandler::getInstance()->activatePCINT2(1 << PCINT20);
    
    // /* block as long as the pin is on the ZERO LEVEL */
    // while (true) { 
    //     if (!isPCINT20Active()) {
    //         Serial::UART::getInstance()->sprintln((char*) "OFF -- LOW LEVEL");
    //     }
    //     _delay_ms(1000);
    // } 

    while (1);
    return 0;
}
