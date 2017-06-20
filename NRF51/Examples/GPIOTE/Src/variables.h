/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/April/2017
 * @version     20/June/2017    LEDs state depending on the variable: changeLEDsSTATE.
 *              12/April/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define ON  1
#define OFF 0


/* VARIABLES */
uint32_t changeLEDsSTATE;       /*!<   0x01 = LED1
                                       0x02 = LED2
                                       0x04 = LED3
                                       0x08 = LED4       */
