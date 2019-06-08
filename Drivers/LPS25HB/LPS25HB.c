/**
 * @brief       LPS25HB.c
 * @details     Capacitive digital sensor for relative humidity and temperature.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/May/2019
 * @version     22/May/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "LPS25HB.h"


/**
 * @brief       LPS25HB_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/May/2019
 * @version     22/May/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetDeviceID ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID.
 *
 *
 * @return       Status of LPS25HB_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetDeviceID ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myDeviceID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_WHO_AM_I;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Mask it and update it with the new value  */
  myDeviceID->deviceID   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetResolution ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It set humidity and temperature resolution mode.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 * @param[in]    myTempHumResolution: Humidity and Temperature resolution mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myTempHumResolution )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_AV_CONF;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Mask it and update it with the new value  */
  cmd[1]  &=  ~( AV_CONF_AVGT_MASK | AV_CONF_AVGH_MASK );
  cmd[1]  |=   ( myTempHumResolution.temperatureResolution | myTempHumResolution.humidityResolution );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetResolution ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It get humidity and temperature resolution mode.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 *
 * @param[out]   myTempHumResolution: Humidity and Temperature resolution mode
 *
 *
 * @return       Status of LPS25HB_GetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTempHumResolution )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_AV_CONF;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data  */
  myTempHumResolution->temperatureResolution   =   (LPS25HB_av_config_avgt_t)( cmd & AV_CONF_AVGT_MASK );
  myTempHumResolution->humidityResolution      =   (LPS25HB_av_config_avgh_t)( cmd & AV_CONF_AVGH_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetPowerDown ( I2C_parameters_t , LPS25HB_ctrl_reg1_pd_t )
 *
 * @details     It sets the device into power-down ( low-power mode ) or active mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPowerMode:     Power-Down/Active mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetPowerDown ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg1_pd_t myPowerMode )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_PD_MASK ) | myPowerMode );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetBlockDataUpdate ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBDU:           Block data update mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myBDU )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_BDU_MASK ) | myBDU.bdu );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetBlockDataUpdate ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBDU:           Block data update mode
 *
 *
 * @return       Status of LPS25HB_GetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myBDU )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_CTRL_REG1;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data  */
  myBDU->bdu   =   (LPS25HB_ctrl_reg1_bdu_t)( cmd & CTRL_REG1_BDU_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetOutputDataRate ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the output data rate ( ODR ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myODR:           Output data rate.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetOutputDataRate  ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myODR )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_ODR_MASK ) | myODR.odr );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetOutputDataRate ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the output data rate ( ODR ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myODR:           Output data rate
 *
 *
 * @return       Status of LPS25HB_GetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetOutputDataRate  ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myODR )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_CTRL_REG1;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myODR->odr   =   (LPS25HB_ctrl_reg1_odr_t)( cmd & CTRL_REG1_ODR_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetBoot ( I2C_parameters_t )
 *
 * @details     It sets reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetBoot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         At the end of the boot process, the BOOT bit is set again to '0'.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetBoot  ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_BOOT_MASK ) | CTRL_REG2_BOOT_REBOOT_MEMORY_CONTENT );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetBoot ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBOOT:          Reboot memory content flag
 *
 *
 * @return       Status of LPS25HB_GetBoot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetBoot ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myBOOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myBOOT->boot   =   (LPS25HB_ctrl_reg2_boot_t)( cmd & CTRL_REG2_BOOT_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetHeater ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It sets heater mode: Enabled/Disabled.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHeater:        Heater mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetHeater.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetHeater ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myHeater )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_HEATER_MASK ) | myHeater.heater );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetHeater ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHeater         Heater mode
 *
 *
 * @return       Status of LPS25HB_GetHeater.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetHeater ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHeater )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myHeater->heater   =   (LPS25HB_ctrl_reg2_heater_t)( cmd & CTRL_REG2_HEATER_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetOneShot ( I2C_parameters_t )
 *
 * @details     It sets one-shot, new data set.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         ONE_SHOT bit comes back to '0' by hardware
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetOneShot ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_ONE_SHOT_MASK ) | CTRL_REG2_ONE_SHOT_START );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetOneShot ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets one-shot flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myOneShot:       One-shot flag
 *
 *
 * @return       Status of LPS25HB_GetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetOneShot ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myOneShot )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myOneShot->one_shot   =   (LPS25HB_ctrl_reg2_one_shot_t)( cmd & CTRL_REG2_ONE_SHOT_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetDataReadyOuput ( I2C_parameters_t , LPS25HB_ctrl_reg3_drdy_h_l_t )
 *
 * @details     It sets data ready output signal active high/low.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY_H_L:      Data ready output signal high/low.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetDataReadyOuput.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetDataReadyOuput ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_drdy_h_l_t myDRDY_H_L )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_DRDY_H_L_MASK ) | myDRDY_H_L );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetSelectionOnPin3 ( I2C_parameters_t , LPS25HB_ctrl_reg3_pp_od_t )
 *
 * @details     It sets Push-pull/Open Drain selection on pin 3 ( DRDY ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY:          Push-pull/Open Drain selection on pin 3 (DRDY).
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetDataReadyOuput.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetSelectionOnPin3 ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_pp_od_t myDRDY )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_PP_OD_MASK ) | myDRDY );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetDataReadyEnable ( I2C_parameters_t , LPS25HB_ctrl_reg3_drdy_en_t )
 *
 * @details     It sets data ready enable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY_EN:       Data Ready enable.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of LPS25HB_SetDataReadyEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetDataReadyEnable ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_drdy_en_t myDRDY_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   LPS25HB_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_DRDY_EN_MASK ) | myDRDY_EN );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetHumidityDataAvailable ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets humidity data available flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumidityFlag:  Humidity data available flag
 *
 *
 * @return       Status of LPS25HB_GetHumidityDataAvailable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetHumidityDataAvailable ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHumidityFlag )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_STATUS_REG;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myHumidityFlag->h_da   =   (LPS25HB_status_reg_h_da_t)( cmd & STATUS_REGISTER_H_DA_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetTemperatureDataAvailable ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets temperature data available flag.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperatureFlag: Temperature data available flag
 *
 *
 * @return       Status of LPS25HB_GetTemperatureDataAvailable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetTemperatureDataAvailable ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTemperatureFlag )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   LPS25HB_STATUS_REG;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myTemperatureFlag->t_da   =   (LPS25HB_status_reg_t_da_t)( cmd & STATUS_REGISTER_T_DA_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetRawHumidity ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets raw humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawHumidity:     Raw humidity
 *
 *
 * @return       Status of LPS25HB_GetRawHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetRawHumidity ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawHumidity )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( LPS25HB_HUMIDITY_OUT_L | 0x80 );                                        // Autoincrementing
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myRawHumidity->rawHumidity   =   cmd[1];
  myRawHumidity->rawHumidity <<=   8U;
  myRawHumidity->rawHumidity  |=   cmd[0];
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetRawTemperature ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature
 *
 *
 * @return       Status of LPS25HB_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetRawTemperature ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawTemperature )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( LPS25HB_TEMP_OUT_L | 0x80 );                                             // Autoincrementing
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


  /* Parse the data   */
  myRawTemperature->rawTemperature   =   cmd[1];
  myRawTemperature->rawTemperature <<=   8U;
  myRawTemperature->rawTemperature  |=   cmd[0];
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetCalibrationCoefficients ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets calibration coefficients.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCoeff:           Calibration coefficients
 *
 *
 * @return       Status of LPS25HB_GetCalibrationCoefficients.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     30/May/2019     Coefficients calibration is calculated here.
 *              24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetCalibrationCoefficients ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myCoeff )
{
  uint8_t      cmd[16]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( LPS25HB_CALIB_0 | 0x80 );                                             // Autoincrementing 
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myCoeff->h0_rH_x2    =   cmd[0];
  myCoeff->h1_rH_x2    =   cmd[1];
  myCoeff->t0_degC_x8  =   cmd[2];
  myCoeff->t1_degC_x8  =   cmd[3];
  myCoeff->t1_T0_msb   =   ( cmd[5] & 0x0F );
  myCoeff->h0_T0_OUT   =   cmd[7];
  myCoeff->h0_T0_OUT <<=   8U;
  myCoeff->h0_T0_OUT  |=   cmd[6];
  myCoeff->h1_T0_OUT   =   cmd[11];
  myCoeff->h1_T0_OUT <<=   8U;
  myCoeff->h1_T0_OUT  |=   cmd[10];
  myCoeff->t0_OUT      =   cmd[13];
  myCoeff->t0_OUT    <<=   8U;
  myCoeff->t0_OUT     |=   cmd[12];
  myCoeff->t1_OUT      =   cmd[15];
  myCoeff->t1_OUT    <<=   8U;
  myCoeff->t1_OUT     |=   cmd[14];
  
  /* Coefficient result for temperature & humidity  */
  myCoeff->t0_degC   =  ( myCoeff->t1_T0_msb & 0x03 );
  myCoeff->t0_degC <<=  8U;
  myCoeff->t0_degC  |=  myCoeff->t0_degC_x8;
  myCoeff->t0_degC >>=  3U;

  myCoeff->t1_degC   =   ( myCoeff->t1_T0_msb & 0x0C );
  myCoeff->t1_degC <<=   6U;
  myCoeff->t1_degC  |=   myCoeff->t1_degC_x8;
  myCoeff->t1_degC >>=  3U;

  myCoeff->h0_RH     =   myCoeff->h0_rH_x2;
  myCoeff->h0_RH   >>=  1U;

  myCoeff->h1_RH     =   myCoeff->h1_rH_x2;
  myCoeff->h1_RH   >>=  1U;
  



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetTemperature ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the current temperature in Celsius degrees.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature in Celsius degress
 *
 *
 * @return       Status of LPS25HB_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        26/May/2019
 * @version     30/May/2019     Temperature calculation was improved
 *              26/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetTemperature ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTemperature )
{
  LPS25HB_status_t aux;

  /* Get temperature  */
  aux  =   LPS25HB_GetRawTemperature ( myI2Cparameters, &(*myTemperature) );

  /* Parse the data   */
  myTemperature->temperature   =   (int32_t)( 10.0*( myTemperature->rawTemperature - myTemperature->t0_OUT )*( myTemperature->t1_degC - myTemperature->t0_degC )/( myTemperature->t1_OUT - myTemperature->t0_OUT ) );
  myTemperature->temperature  +=   10.0*myTemperature->t0_degC;
  myTemperature->temperature  /=   10.0;
  
  

  if ( aux == LPS25HB_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}


/**
 * @brief       LPS25HB_GetHumidity ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the current humidity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidity:        Current humidity value
 *
 *
 * @return       Status of LPS25HB_GetHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        26/May/2019
 * @version     30/May/2019     Humidity calculation was improved
 *              26/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetHumidity ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHumidity )
{
  LPS25HB_status_t aux;

  /* Get humidity  */
  aux  =   LPS25HB_GetRawHumidity ( myI2Cparameters, &(*myHumidity) );

  /* Parse the data   */ 
  myHumidity->humidity   =   (int32_t)( 10.0*( myHumidity->rawHumidity - myHumidity->h0_T0_OUT )*( myHumidity->h1_RH - myHumidity->h0_RH )/( myHumidity->h1_T0_OUT - myHumidity->h0_T0_OUT ) );
  myHumidity->humidity  +=   10.0*myHumidity->h0_RH;
  myHumidity->humidity  /=   10.0;

  /* Check if it is saturated  */
  if ( myHumidity->humidity > 100 )
  {
    myHumidity->humidity   =   100;
  }
  
  

  if ( aux == LPS25HB_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}