/**
 * @brief       SX128X.h
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/January/2019
 * @version     29/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/**
  * @brief   LIST OF COMMANDS
  */
typedef enum
{
  SX128X_GET_STATUS                 =   0xC0,                       /*!<  Parameters: N/A                                                                                                                                   | Return: status                                                                                                */
  SX128X_WRITE_REGISTER             =   0x18,                       /*!<  Parameters: address[15:8], address[7:0], data[0:n]                                                                                                | Return: N/A                                                                                                   */
  SX128X_READ_REGISTER              =   0x19,                       /*!<  Parameters: address[15:8], address[7:0]                                                                                                           | Return: data[0:n-1]                                                                                           */
  SX128X_WRITE_BUFFER               =   0x1A,                       /*!<  Parameters: offset,data[0:n]                                                                                                                      | Return: N/A                                                                                                   */
  SX128X_READ_BUFFER                =   0x1B,                       /*!<  Parameters: offset                                                                                                                                | Return: data[0:n-1]                                                                                           */
  SX128X_SET_SLEEP                  =   0x84,                       /*!<  Parameters: sleepConfig                                                                                                                           | Return: N/A                                                                                                   */
  SX128X_SET_STANDBY                =   0x80,                       /*!<  Parameters: standbyConfig                                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_FS                     =   0xC1,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX                     =   0x83,                       /*!<  Parameters: periodBase, periodBaseCount[15:8], periodBaseCount[7:0]                                                                               | Return: N/A                                                                                                   */
  SX128X_SET_RX                     =   0x82,                       /*!<  Parameters: periodBase, periodBaseCount[15:8], periodBaseCount[7:0]                                                                               | Return: N/A                                                                                                   */
  SX128X_SET_RX_DUTY_CYCLE          =   0x94,                       /*!<  Parameters: rxPeriodBase, rxPeriodBaseCount[15:8], rxPeriodBaseCount[7:0], sleepPeriodBase, sleepPeriodBaseCount[15:8], sleepPeriodBaseCount[7:0] | Return: N/A                                                                                                   */
  SX128X_SET_CAD                    =   0xC5,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX_CONTINUOUS_WAVE     =   0xD1,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX_CONTINUOUS_PREAMBLE =   0xD2,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_PACKET_TYPE            =   0x8A,                       /*!<  Parameters: packetType                                                                                                                            | Return: N/A                                                                                                   */
  SX128X_GET_PACKET_TYPE            =   0x03,                       /*!<  Parameters: N/A                                                                                                                                   | Return: packetType                                                                                            */
  SX128X_SET_RF_FREQUENCY           =   0x86,                       /*!<  Parameters: rfFrequency[23:16],rfFrequency[15:8], rfFrequency[7:0]                                                                                | Return: N/A                                                                                                   */
  SX128X_SET_TX_PARAMS              =   0x8E,                       /*!<  Parameters: power, rampTime                                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_CAD_PARAMS             =   0x88,                       /*!<  Parameters: cadSymbolNum                                                                                                                          | Return: N/A                                                                                                   */
  SX128X_SET_BUFFER_BASE_ADDRESS    =   0x8F,                       /*!<  Parameters: txBaseAddress, rxBaseAddress                                                                                                          | Return: N/A                                                                                                   */
  SX128X_SET_MODULATION_PARAMS      =   0x8B,                       /*!<  Parameters: modParam1, modParam2, modParam3                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_PACKET_PARAMS          =   0x8C,                       /*!<  Parameters: packetParam1, packetParam2, packetParam3, packetParam4, packetParam5, packetParam6, packetParam7                                      | Return: N/A                                                                                                   */
  SX128X_GET_RX_BUFFER_STATUS       =   0x17,                       /*!<  Parameters: N/A                                                                                                                                   | Return: payloadLength, rxBufferOffset                                                                         */
  SX128X_GET_PACKET_STATUS          =   0x1D,                       /*!<  Parameters: N/A                                                                                                                                   | Return: packetStatus[39:32], packetStatus[31:24], packetStatus[23:16], packetStatus[15:8], packetStatus[7:0]  */
  SX128X_GET_RSSI_INST              =   0x1F,                       /*!<  Parameters: N/A                                                                                                                                   | Return: rssiInst                                                                                              */
  SX128X_SET_DIO_IRQ_PARAMS         =   0x8D,                       /*!<  Parameters: irqMask[15:8], irqMask[7:0], dio1Mask[15:8],dio1Mask[7:0], dio2Mask[15:8], dio2Mask[7:0], dio3Mask[15:8], dio3Mask[7:0]               | Return: N/A                                                                                                   */
  SX128X_GET_IRQ_STATUS             =   0x15,                       /*!<  Parameters: N/A                                                                                                                                   | Return: irqStatus[15:8], irqStatus[7:0]                                                                       */
  SX128X_CLR_IRQ_STATUS             =   0x97,                       /*!<  Parameters: irqMask[15:8], irqMask[7:0]                                                                                                           | Return: N/A                                                                                                   */
  SX128X_SET_REGULATOR_MODE         =   0x96,                       /*!<  Parameters: regulatorMode                                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_SAVE_CONTEXT           =   0xD5,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_AUTO_FS                =   0x9E,                       /*!<  Parameters: 0x00: disable or 0x01: enable                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_AUTO_TX                =   0x98,                       /*!<  Parameters: time                                                                                                                                  | Return: N/A                                                                                                   */
  SX128X_SET_PERF_COUNTER_MODE      =   0x9C,                       /*!<  Parameters: perfCounterMode                                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_LONG_PREAMBLE          =   0x9B,                       /*!<  Parameters: enable                                                                                                                                | Return: N/A                                                                                                   */
  SX128X_SET_UART_SPEED             =   0x9D,                       /*!<  Parameters: uartSpeed                                                                                                                             | Return: N/A                                                                                                   */
  SX128X_SET_RANGING_ROLE           =   0xA3                        /*!<  Parameters: 0x00=Slave or 0x01=Master                                                                                                             | Return: N/A                                                                                                   */
} SX128X_commands_t;



/**
  * @brief   GET_STATUS
  */
/* CIRCUIT_MODE <7:5>: CIRCUIT MODE
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_CIRCUIT_MODE_MASK       =   ( 0b111 << 5U ),             /*!<  CIRCUIT_MODE mask                                   */
    GET_STATUS_CIRCUIT_MODE_STDBY_RC   =   ( 0x02  << 5U ),             /*!<  CIRCUIT_MODE: STDBY_RC                              */
    GET_STATUS_CIRCUIT_MODE_STDBY_XOSC =   ( 0x03  << 5U ),             /*!<  CIRCUIT_MODE: STDBY_XOSC                            */
    GET_STATUS_CIRCUIT_MODE_FS         =   ( 0x04  << 5U ),             /*!<  CIRCUIT_MODE: FS                                    */
    GET_STATUS_CIRCUIT_MODE_RX         =   ( 0x05  << 5U ),             /*!<  CIRCUIT_MODE: RX                                    */
    GET_STATUS_CIRCUIT_MODE_TX         =   ( 0x06  << 5U )              /*!<  CIRCUIT_MODE: TX                                    */
} SX128X_get_status_circuit_mode_t;



/* COMMAND_STATUS <4:2>: COMMAND STATUS
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_COMMAND_STATUS_MASK                                              =   ( 0b111 << 2U ),  /*!<  COMMAND_STATUS mask                                                                             */
    GET_STATUS_COMMAND_STATUS_TRANSCEIVER_HAS_SUCCESSFULLY_PROCESSED_COMMAND    =   ( 0x01  << 2U ),  /*!<  The command has been terminated correctly                                                       */
    GET_STATUS_COMMAND_STATUS_DATA_ARE_AVAILABLE_TO_HOST                        =   ( 0x02  << 2U ),  /*!<  A packet has been successfully received and data can be retrieved                               */
    GET_STATUS_COMMAND_STATUS_COMMAND_TIMEOUT                                   =   ( 0x03  << 2U ),  /*!<  A transaction from the host took too long to complete and triggered an internal watchdog        */
    GET_STATUS_COMMAND_STATUS_COMMAND_PROCESSING_ERROR                          =   ( 0x04  << 2U ),  /*!<  The transceiver was unable to process command                                                   */
    GET_STATUS_COMMAND_STATUS_FAILURE_TO_EXECUTE_COMMAND                        =   ( 0x05  << 2U ),  /*!<  The command was successfully processed, however the transceiver could not execute the command   */
    GET_STATUS_COMMAND_STATUS_COMMAND_TX_DONE                                   =   ( 0x06  << 2U )   /*!<  The transmission of the current packet has terminated                                           */
} SX128X_get_status_command_status_t;



/* BUSY <0>: BUSY
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_BUSY_MASK                =   ( 0b1 << 0U ),                      /*!<  BUSY mask                                                     */
    GET_STATUS_BUSY_BUSY                =   ( 0b1 << 0U ),                      /*!<  Transceiver is processing command or doing internal operation */
    GET_STATUS_BUSY_NOT_BUSY            =   ( 0b0 << 0U )                       /*!<  Transceiver is released                                       */
} SX128X_get_status_busy_t;



/**
  * @brief   SET_SLEEP
  */
/* SLEEP CONFIG 0 <0>: DATA RAM
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG0_MASK                                =   ( 0b1 << 0U ),   /*!<  SleepConfig[0] mask                                           */
    SET_SLEEP_SLEEP_CONFIG0_DATA_RAM_FLUSHED                    =   ( 0b0 << 0U ),   /*!<  SleepConfig[0] Data RAM is flushed during Sleep Mode          */
    SET_SLEEP_SLEEP_CONFIG0_DATA_RAM_IN_RETENTION_MODE          =   ( 0b1 << 0U )    /*!<  SleepConfig[0] Data RAM in retention mode                     */
} SX128X_set_sleep_sleep_config0_t;



/* SLEEP CONFIG 1 <1>: DATA BUFFER
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG1_MASK                                =   ( 0b1 << 1U ),  /*!<  SleepConfig[1] mask                                           */
    SET_SLEEP_SLEEP_CONFIG1_DATA_BUFFER_FLUSHED                 =   ( 0b0 << 1U ),  /*!<  SleepConfig[1] Data buffer is flushed during Sleep Mode       */
    SET_SLEEP_SLEEP_CONFIG1_DATA_BUFFER_IN_RETENTION_MODE       =   ( 0b1 << 1U )   /*!<  SleepConfig[1] Data buffer in retention mode                  */
} SX128X_set_sleep_sleep_config1_t;



/* SLEEP CONFIG 2 <2>: INSTRUCTION RAM
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG2_MASK                                =   ( 0b1 << 2U ),  /*!<  SleepConfig[2] mask                                           */
    SET_SLEEP_SLEEP_CONFIG2_INSTRUCTION_RAM_FLUSHED             =   ( 0b0 << 2U ),  /*!<  SleepConfig[2] Instruction RAM is flushed during Sleep Mode   */
    SET_SLEEP_SLEEP_CONFIG2_INSTRUCTION_RAM_IN_RETENTION_MODE   =   ( 0b1 << 2U )   /*!<  SleepConfig[2] Instruction RAM in retention mode              */
} SX128X_set_sleep_sleep_config2_t;



/**
  * @brief   SET_STANDBY
  */
/* STANDBYCONFIG <0>
 *    NOTE: N/A.
 */
typedef enum
{
    SET_STANDBY_MASK                                            =   ( 0b1 << 0U ),  /*!<  StandbyConfig mask                                            */
    SET_STANDBY_STANDBY_CONFIG_STDBY_RC                         =   ( 0b0 << 0U ),  /*!<  Device running on RC 13MHz, set STDBY_RC mode                 */
    SET_STANDBY_STANDBY_CONFIG_STDBY_XOSC                       =   ( 0b1 << 0U )   /*!<  Device running on XTAL 52MHz, set STDBY_XOSC mode             */
} SX128X_set_standby_standbyconfig_t;



/**
  * @brief   SET_TX/SET_RX
  */
/* TIME-OUT DEFINITION <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_TX_RX_TIMEOUT_STEP_MASK                                 =   0xFF,           /*!<  Time-out step mask                                            */
    SET_TX_RX_TIMEOUT_STEP_15_625_US                            =   0x00,           /*!<  Time-out step: 15.625us                                       */
    SET_TX_RX_TIMEOUT_STEP_62_5_US                              =   0x01,           /*!<  Time-out step: 62.5us                                         */
    SET_TX_RX_TIMEOUT_STEP_1_MS                                 =   0x02,           /*!<  Time-out step:  1ms                                           */
    SET_TX_RX_TIMEOUT_STEP_4_MS                                 =   0x03            /*!<  Time-out step:  4ms                                           */
} SX128X_set_tx_rx_timeout_definition_t;



/**
  * @brief   SET_LONG_PREAMBLE
  */
/* ENABLE/DISABLE <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_LONG_PREAMBLE_MASK                                      =   0x01,           /*!<  Long preamble mask                                            */
    SET_LONG_PREAMBLE_ENABLE                                    =   0x01,           /*!<  Long preamble: Enabled                                        */
    SET_LONG_PREAMBLE_DISABLE                                   =   0x00            /*!<  Long preamble: Disabled                                       */
} SX128X_set_long_preamble_t;



/**
  * @brief   SET_AUTO_FS
  */
/* ENABLE/DISABLE <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_AUTO_FS_MASK                                            =   0x01,           /*!<  Auto FS mask                                                  */
    SET_AUTO_FS_ENABLE                                          =   0x01,           /*!<  Auto FS: Enabled                                              */
    SET_AUTO_FS_DISABLE                                         =   0x00            /*!<  Auto FS: Disabled                                             */
} SX128X_set_auto_fs_t;



/**
  * @brief   SET_PACKET_TIME
  */
/* PACKET TYPE DEFINITION <7:0>: MODEM MODE OF OPERATION
 *    NOTE: N/A.
 */
typedef enum
{
    SET_PACKET_TIME_MASK                                        =   0x0F,           /*!<  Packet type mask                                              */
    SET_PACKET_TIME_PACKET_TYPE_GFSK                            =   0x00,           /*!<  Packet type: GFSK mode                              [default] */
    SET_PACKET_TIME_PACKET_TYPE_LORA                            =   0x01,           /*!<  Packet type: LoRa mode                                        */
    SET_PACKET_TIME_PACKET_TYPE_RANGING                         =   0x02,           /*!<  Packet type: Ranging Engine mode                              */
    SET_PACKET_TIME_PACKET_TYPE_FLRC                            =   0x03,           /*!<  Packet type: FLRC mode                                        */
    SET_PACKET_TIME_PACKET_TYPE_BLE                             =   0x04            /*!<  Packet type: BLE mode                                         */
} SX128X_set_packet_time_t;



/**
  * @brief   SET_TX_PARAMS
  */
/* RAMP TIME <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_RAMP_TIME_MASK                                          =   0xFF,           /*!<  Ramp time mask                                                */
    SET_RAMP_TIME_RADIO_RAMP_02_US                              =   0x00,           /*!<  Ramp time:  2us                                               */
    SET_RAMP_TIME_RADIO_RAMP_04_US                              =   0x20,           /*!<  Ramp time:  4us                                               */
    SET_RAMP_TIME_RADIO_RAMP_06_US                              =   0x40,           /*!<  Ramp time:  6us                                               */
    SET_RAMP_TIME_RADIO_RAMP_08_US                              =   0x60,           /*!<  Ramp time:  8us                                               */
    SET_RAMP_TIME_RADIO_RAMP_10_US                              =   0x80,           /*!<  Ramp time: 10us                                               */
    SET_RAMP_TIME_RADIO_RAMP_12_US                              =   0xA0,           /*!<  Ramp time: 12us                                               */
    SET_RAMP_TIME_RADIO_RAMP_16_US                              =   0xC0,           /*!<  Ramp time: 16us                                               */
    SET_RAMP_TIME_RADIO_RAMP_20_US                              =   0xE0            /*!<  Ramp time: 20us                                               */
} SX128X_set_tx_params_ramp_time_time_t;



/**
  * @brief   SET_CAD_PARAMS
  */
/* CAD PARAMS <7:0>: NUMBER OF SYMBOLS USED FOR CAD
 *    NOTE: N/A.
 */
typedef enum
{
    SET_CAD_PARAMS_MASK                                         =   0xFF,           /*!<  CAD params mask                                               */
    SET_CAD_PARAMS_LORA_CAD_01_SYMBOL                           =   0x00,           /*!<  CAD params:  1                                                */
    SET_CAD_PARAMS_LORA_CAD_02_SYMBOLS                          =   0x20,           /*!<  CAD params:  4                                                */
    SET_CAD_PARAMS_LORA_CAD_04_SYMBOLS                          =   0x40,           /*!<  CAD params:  8                                                */
    SET_CAD_PARAMS_LORA_CAD_08_SYMBOLS                          =   0x60,           /*!<  CAD params:  8                                                */
    SET_CAD_PARAMS_LORA_CAD_16_SYMBOLS                          =   0x80            /*!<  CAD params: 10                                                */
} SX128X_set_cad_params_cad_symbol_num_t;



/**
  * @brief   MODULATION PARAMETERS
  */
/* MODULATION PARAMETERS 1 <7:0>: GFSK AND BLE MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_1_GFSK_BLE_MASK                                   =   0xFF,           /*!<  Mod param 1 GFSK and BLE mode mask                            */
    MOD_PARAM_1_GFSK_BLE_BR_2_000_BW_2_4                        =   0x04,           /*!<  2     Mb/s Bitrate | 2.5 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_1_600_BW_2_4                        =   0x28,           /*!<  1.6   Mb/s Bitrate | 2.4 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_1_000_BW_2_4                        =   0x4C,           /*!<  1     Mb/s Bitrate | 2.4 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_1_000_BW_1_2                        =   0x45,           /*!<  1     Mb/s Bitrate | 1.2 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_800_BW_2_4                        =   0x70,           /*!<  0.8   Mb/s Bitrate | 2.4 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_800_BW_1_2                        =   0x69,           /*!<  0.8   Mb/s Bitrate | 1.2 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_500_BW_1_2                        =   0x8D,           /*!<  0.5   Mb/s Bitrate | 1.2 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_500_BW_0_6                        =   0x86,           /*!<  0.5   Mb/s Bitrate | 0.6 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_400_BW_1_2                        =   0xB1,           /*!<  0.4   Mb/s Bitrate | 1.2 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_400_BW_0_6                        =   0xAA,           /*!<  0.4   Mb/s Bitrate | 0.6 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_250_BW_0_6                        =   0xCE,           /*!<  0.25  Mb/s Bitrate | 0.6 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_250_BW_0_3                        =   0xC7,           /*!<  0.25  Mb/s Bitrate | 0.3 MHz Bandwidth                        */
    MOD_PARAM_1_GFSK_BLE_BR_0_125_BW_0_3                        =   0xEF            /*!<  0.125 Mb/s Bitrate | 0.3 MHz Bandwidth                        */
} SX128X_modulation_parameter_gfsk_ble_modparam1_t;



/* MODULATION PARAMETERS 1 <7:0>: FLRC MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_1_FLRC_MASK                                       =   0xFF,           /*!<  Mod param 1 FLRC mode mask                                    */
    MOD_PARAM_1_FLRC_BR_1_300_BW_1_2                            =   0x45,           /*!<  1.3    Mb/s Bitrate | 1.2 MHz Bandwidth                       */
    MOD_PARAM_1_FLRC_BR_1_000_BW_1_2                            =   0x69,           /*!<  1.04   Mb/s Bitrate | 1.2 MHz Bandwidth                       */
    MOD_PARAM_1_FLRC_BR_0_650_BW_0_6                            =   0x86,           /*!<  0.65   Mb/s Bitrate | 0.6 MHz Bandwidth                       */
    MOD_PARAM_1_FLRC_BR_0_520_BW_0_6                            =   0xAA,           /*!<  0.52   Mb/s Bitrate | 0.6 MHz Bandwidth                       */
    MOD_PARAM_1_FLRC_BR_0_325_BW_0_3                            =   0xC7,           /*!<  0.325  Mb/s Bitrate | 20.3 MHz Bandwidth                      */
    MOD_PARAM_1_FLRC_BR_0_260_BW_0_3                            =   0xEB            /*!<  0.26   Mb/s Bitrate | 0.3 MHz Bandwidth                       */
} SX128X_modulation_parameter_flrc_modparam1_t;



/* MODULATION PARAMETERS 1 <7:0>: LORA MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_1_LORA_MASK                                       =   0xFF,           /*!<  Mod param 1 LoRa mode mask                                    */
    MOD_PARAM_1_LORA_SF_5                                       =   0x50,           /*!<  Spreading factor:  5                                          */
    MOD_PARAM_1_LORA_SF_6                                       =   0x60,           /*!<  Spreading factor:  6                                          */
    MOD_PARAM_1_LORA_SF_7                                       =   0x70,           /*!<  Spreading factor:  7                                          */
    MOD_PARAM_1_LORA_SF_8                                       =   0x80,           /*!<  Spreading factor:  8                                          */
    MOD_PARAM_1_LORA_SF_9                                       =   0x90,           /*!<  Spreading factor:  9                                          */
    MOD_PARAM_1_LORA_SF_10                                      =   0xA0,           /*!<  Spreading factor: 10                                          */
    MOD_PARAM_1_LORA_SF_11                                      =   0xB0,           /*!<  Spreading factor: 11                                          */
    MOD_PARAM_1_LORA_SF_12                                      =   0xC0            /*!<  Spreading factor: 12                                          */
} SX128X_modulation_parameter_lora_modparam1_t;



/* MODULATION PARAMETERS 2 <7:0>: GFSK AND BLE MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_2_GFSK_BLE_MASK                                   =   0xFF,           /*!<  Mod param 2 GFSK and BLE mode mask                            */
    MOD_PARAM_2_MOD_IND_0_35                                    =   0x00,           /*!<  Modindex: 0.35                                                */
    MOD_PARAM_2_MOD_IND_0_5                                     =   0x01,           /*!<  Modindex: 0.5                                                 */
    MOD_PARAM_2_MOD_IND_0_75                                    =   0x02,           /*!<  Modindex: 0.75                                                */
    MOD_PARAM_2_MOD_IND_1_00                                    =   0x03,           /*!<  Modindex: 1                                                   */
    MOD_PARAM_2_MOD_IND_1_25                                    =   0x04,           /*!<  Modindex: 1.25                                                */
    MOD_PARAM_2_MOD_IND_1_50                                    =   0x05,           /*!<  Modindex: 1.5                                                 */
    MOD_PARAM_2_MOD_IND_1_75                                    =   0x06,           /*!<  Modindex: 1.75                                                */
    MOD_PARAM_2_MOD_IND_2_00                                    =   0x07,           /*!<  Modindex: 2                                                   */
    MOD_PARAM_2_MOD_IND_2_25                                    =   0x08,           /*!<  Modindex: 2.25                                                */
    MOD_PARAM_2_MOD_IND_2_50                                    =   0x09,           /*!<  Modindex: 2.5                                                 */
    MOD_PARAM_2_MOD_IND_2_75                                    =   0x0A,           /*!<  Modindex: 2.75                                                */
    MOD_PARAM_2_MOD_IND_3_00                                    =   0x0B,           /*!<  Modindex: 3                                                   */
    MOD_PARAM_2_MOD_IND_3_25                                    =   0x0C,           /*!<  Modindex: 3.25                                                */
    MOD_PARAM_2_MOD_IND_3_50                                    =   0x0D,           /*!<  Modindex: 3.5                                                 */
    MOD_PARAM_2_MOD_IND_3_75                                    =   0x0E,           /*!<  Modindex: 3.75                                                */
    MOD_PARAM_2_MOD_IND_4_00                                    =   0x0F            /*!<  Modindex: 4                                                   */
} SX128X_modulation_parameter_gfsk_ble_modparam2_t;



/* MODULATION PARAMETERS 2 <7:0>: FLRC MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_2_FLRC_MASK                                       =   0xFF,           /*!<  Mod param 2 FLRC mode mask                                    */
    MOD_PARAM_2_FLRC_CR_1_2                                     =   0x00,           /*!<  Coding rate: 1/2                                              */
    MOD_PARAM_2_FLRC_CR_3_4                                     =   0x02,           /*!<  Coding rate: 3/4                                              */
    MOD_PARAM_2_FLRC_CR_1_0                                     =   0x04            /*!<  Coding rate: 1                                                */
} SX128X_modulation_parameter_flrc_modparam2_t;



/* MODULATION PARAMETERS 2 <7:0>: LORA MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_2_LORA_MASK                                       =   0xFF,           /*!<  Mod param 2 LoRa mode mask                                    */
    MOD_PARAM_2_LORA_BW_1600                                    =   0x0A,           /*!<  Bandwidth:  1625.0   kHz                                      */
    MOD_PARAM_2_LORA_BW_800                                     =   0x18,           /*!<  Bandwidth:   812.5   kHz                                      */
    MOD_PARAM_2_LORA_BW_400                                     =   0x26,           /*!<  Bandwidth:   406.25  kHz                                      */
    MOD_PARAM_2_LORA_BW_200                                     =   0x34            /*!<  Bandwidth:   203.125 kHz                                      */
} SX128X_modulation_parameter_lora_modparam2_t;



/* MODULATION PARAMETERS 3 <7:0>: GFSK, BLE AND FLRC MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_3_GFSK_BLE_FLRC_MASK                              =   0xFF,           /*!<  Mod param 3 GFSK, BLE and FLRC mode mask                      */
    MOD_PARAM_3_BT_OFF                                          =   0x00,           /*!<  BT: No filtering                                              */
    MOD_PARAM_3_BT_1_0                                          =   0x10,           /*!<  BT: 1                                                         */
    MOD_PARAM_3_BT_0_5                                          =   0x20            /*!<  BT: 0.5                                                       */
} SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t;



/* MODULATION PARAMETERS 3 <7:0>: LORA MODE
 *    NOTE: N/A.
 */
typedef enum
{
    MOD_PARAM_3_LORA_MASK                                       =   0xFF,           /*!<  Mod param 3 LoRa mode mask                                    */
    MOD_PARAM_3_LORA_CR_4_5                                     =   0x01,           /*!<  Coding rate:  4/5                                             */
    MOD_PARAM_3_LORA_CR_4_6                                     =   0x02,           /*!<  Coding rate:  4/6                                             */
    MOD_PARAM_3_LORA_CR_4_7                                     =   0x03,           /*!<  Coding rate:  4/7                                             */
    MOD_PARAM_3_LORA_CR_4_8                                     =   0x04,           /*!<  Coding rate:  4/8                                             */
    MOD_PARAM_3_LORA_CR_LI_4_5                                  =   0x05,           /*!<  Coding rate:  4/5                                             */
    MOD_PARAM_3_LORA_CR_LI_4_6                                  =   0x06,           /*!<  Coding rate:  4/6                                             */
    MOD_PARAM_3_LORA_CR_LI_4_7                                  =   0x07            /*!<  Coding rate:  4/8                                             */
} SX128X_modulation_parameter_lora_modparam3_t;









#ifndef SX128X_VECTOR_STRUCT_H
#define SX128X_VECTOR_STRUCT_H
typedef struct
{
    uint8_t                     status;             /*!<  Status            */

    SX128X_set_packet_time_t    packetType;         /*!<  Packet type       */
} SX128X_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SX128X_SUCCESS     =       0,
    SX128X_FAILURE     =       1
} SX128X_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
  */
SX128X_status_t  SX128X_Init                ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It gets the transceiver status.
  */
SX128X_status_t  GetStatus                  ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myStatus                                                                                                                        );

// WriteCommand, ReadCommand, WriteBuffer, ReadBuffer

/** It sets the transceiver to Sleep mode with the lowest current consumption possible.
  */
SX128X_status_t  SetSleep                   ( SPI_parameters_t mySPI_parameters, SX128X_set_sleep_sleep_config0_t myDataRAM, SX128X_set_sleep_sleep_config1_t myDataBuffer, SX128X_set_sleep_sleep_config2_t myInstructionRAM   );

/** It sets the transceiver to Stand-by mode.
  */
SX128X_status_t  SetStandby                 ( SPI_parameters_t mySPI_parameters, SX128X_set_standby_standbyconfig_t myStandbyConfig                                                                                             );

/** It sets the device in Frequency Synthesizer mode where the PLL is locked to the carrier frequency.
  */
SX128X_status_t  SetFs                      ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It sets the device in Transmit mode.
  */
SX128X_status_t  SetTx                      ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount                                                                 );

/** It sets the device in Receiver mode.
  */
SX128X_status_t  SetRx                      ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount                                                                 );

/** It sets the transceiver in sniff mode, so that it regularly looks for new packets ( duty cycled operation ).
  */
SX128X_status_t  SetRxDutyCycle             ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myRxPeriodBaseCount, uint16_t mySleepPeriodBaseCount                              );

/** It sets the transceiver into Long Preamble mode, and can only be used with either the LoRa mode and GFSK mode.
  */
SX128X_status_t  SetLongPreamble            ( SPI_parameters_t mySPI_parameters, SX128X_set_long_preamble_t myLongPreambleStatus                                                                                                );

/** ( Channel Activity Detection ) can be used only in LoRa packet type. The Channel Activity Detection is a LoRa specific mode of operation where the device searches for a LoRa.
  */
SX128X_status_t  SetCAD                     ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It is a test command to generate a Continuous Wave (RF tone) at a selected frequency and output power.
  */
SX128X_status_t  SetTxContinuousWave        ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It is a test command to generate an infinite sequence of alternating '0's and '1's in GFSK, BLE, or FLRC modulation and symbol 0 in LoRa.
  */
SX128X_status_t  SetTxContinuousPreamble    ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It sets the auto-Tx ( BLE requires sending back a response after a packet reception ).
  */
SX128X_status_t  SetAutoTx                  ( SPI_parameters_t mySPI_parameters, uint16_t myTime                                                                                                                                );

/** This feature modifies the chip behavior so that the state following a Rx or Tx operation is FS and not STDBY.
  */
SX128X_status_t  SetAutoFs                  ( SPI_parameters_t mySPI_parameters, SX128X_set_auto_fs_t myAutoFsStatus                                                                                                            );

/** It sets the transceiver radio frame out of a choice of 6 different packet types.
  */
SX128X_status_t  SetPacketType              ( SPI_parameters_t mySPI_parameters, SX128X_set_packet_time_t myPacketType                                                                                                          );

/** It returns the current operating packet type of the radio.
  */
SX128X_status_t  GetPacketType              ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myPacketType                                                                                                                    );

/** It is used to set the frequency of the RF frequency mode.
  */
SX128X_status_t  SetRfFrequency             ( SPI_parameters_t mySPI_parameters, uint32_t myRfFrequency                                                                                                                         );

/** It sets the Tx output power using parameter power and the Tx ramp time using parameter rampTime.
  */
SX128X_status_t  SetTxParams                ( SPI_parameters_t mySPI_parameters, uint8_t myPower, SX128X_set_tx_params_ramp_time_time_t myRampTime                                                                              );

/** It defines the number of symbols on which Channel Activity Detected ( CAD ) operates.
  */
SX128X_status_t  SetCadParams               ( SPI_parameters_t mySPI_parameters, SX128X_set_cad_params_cad_symbol_num_t myCadSymbolNum                                                                                          );

/** It fixes the base address for the packet handing operation in Tx and Rx mode for all packet types.
  */
SX128X_status_t  SetBufferBaseAddress       ( SPI_parameters_t mySPI_parameters, uint8_t myTxBaseAdress, uint8_t myRxBaseAdress                                                                                                 );

/** It configures the modulation parameters of the radio ( GFSK and BLE mode ).
  */
SX128X_status_t  SetModulationParams_GFSK_BLE   ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_gfsk_ble_modparam1_t myModParam1, SX128X_modulation_parameter_gfsk_ble_modparam2_t myModParam2, SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t myModParam3  );

/** It configures the modulation parameters of the radio ( FLRC mode ).
  */
SX128X_status_t  SetModulationParams_FLRC   ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_flrc_modparam1_t myModParam1, SX128X_modulation_parameter_flrc_modparam2_t myModParam2, SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t myModParam3              );

/** It configures the modulation parameters of the radio ( LoRa mode ).
  */
SX128X_status_t  SetModulationParams_LORA   ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_lora_modparam1_t myModParam1, SX128X_modulation_parameter_lora_modparam2_t myModParam2, SX128X_modulation_parameter_lora_modparam3_t myModParam3                       );

