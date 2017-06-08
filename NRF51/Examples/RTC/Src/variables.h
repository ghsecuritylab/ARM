/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017    The ORIGIN
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
uint32_t changeLEDsSTATE;       /*!<   changeLEDsSTATE = ON:     [todo].
                                       changeLEDsSTATE = OFF:    [todo]         */

uint32_t my375msDelay;          /*!<   counter for the Timer2 to generate a
                                       delay of 0.375s                         */
