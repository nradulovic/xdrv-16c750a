/*
 * This file is part of x-16c750
 *
 * Copyright (C) 2011, 2012 - Nenad Radulovic
 *
 * x-16c750 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * x-16c750 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with x-16c750; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * web site:    http://blueskynet.dyndns-server.com
 * e-mail  :    blueskyniss@gmail.com
 *//***********************************************************************//**
 * @file
 * @author  	Nenad Radulovic
 * @brief       Port interface
 *********************************************************************//** @{ */

#if !defined(PORT_H_)
#define PORT_H_

/*=========================================================  INCLUDE FILES  ==*/

#include "drv/x-16c750.h"
#include "compiler.h"

/*===============================================================  MACRO's  ==*/

/**@brief       Expand UART data as IO memory table
 */
#define UART_DATA_EXPAND_AS_MEM(uart, mem, irq)                                 \
    mem,

/**@brief       Expand UART data as IRQ number table
 */
#define UART_DATA_EXPAND_AS_IRQ(uart, mem, irq)                                 \
    irq,

/**@brief       Supported UARTs table
 */
#define UART_DATA_EXPAND_AS_UART(uart, mem, iqr)                                \
    uart,

/*------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================  DATA TYPES  ==*/

struct devData;

/*======================================================  GLOBAL VARIABLES  ==*/

/**@brief       Hardware IO memory maps
 */
extern const uint32_t PortIOmap[];

/**@brief       Hardware IRQ numbers
 */
extern const uint32_t PortIRQ[];

/**@brief       Number of supported UARTs
 */
extern const uint32_t PortUartNum;

/*===================================================  FUNCTION PROTOTYPES  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Generic functions
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Create and init kernel device driver
 * @param       id
 *              Device driver ID as supplied by silicon manufacturer
 * @return      Private device data, needed to be saved somewhere for later
 *              reference
 */
struct devData * portInit(
    uint32_t            id);

/**@brief       Deinit and destroy kernel device driver
 * @param       devResource
 *              Pointer returned by portInit()
 */
int32_t portTerm(
    struct devData *    devData);

int32_t portModeGet(
    uint32_t            baudrate);

int32_t portDIVdataGet(
    uint32_t            baudrate);

volatile uint8_t * portIORemapGet(
    struct devData *    devData);

bool_T portIsOnline(
    uint32_t            id);

/**@} *//*----------------------------------------------------------------*//**
 * @name        DMA functions
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Request and create DMA coherent buffer segment and return
 *              virtual address to that buffer
 * @param       devData
 *              Device data structure
 * @param       buff
 *              Pointer to buffer pointer which is accessible from Linux domain
 * @param       size
 *              The size of requested buffer in bytes
 * @return      Operation status
 *  @retval     0 - success
 *              -ENOMEM - no abailable DMA memory
 *              -EINVAL - invalid resource
 */
int32_t portDMARxInit(
    struct devData *    devData,
    void (* callback)(void *),
    void *              arg);

int32_t portDMARxTerm(
    struct devData *    devData);

int32_t portDMARxBeginI(
    struct devData *    devData,
    uint8_t *           dst,
    size_t              size);

int32_t portDMARxContinueI(
    struct devData *    devData,
    uint8_t *           dst,
    size_t              size);

int32_t portDMARxStartI(
    struct devData *    devData);

/**@brief       Stop RX DMA activity
 * @param       devData
 *              Device data structure
 * @return      Operation status
 *  @retval     0 - success
 */
int32_t portDMARxStopI(
    struct devData *    devData);

/**@brief       Request and create DMA coherent buffer segment and return
 *              virtual address to that buffer
 * @param       devData
 *              Device data structure
 */
int32_t portDMATxInit(
    struct devData *    devData,
    void (* callback)(void *),
    void *              arg);

int32_t portDMATxTerm(
    struct devData *    devData);

int32_t portDMATxBeginI(
    struct devData *    devData,
    const uint8_t *     src,
    size_t              size);

int32_t portDMATxContinueI(
    struct devData *    devData,
    const uint8_t *     src,
    size_t              size);

int32_t portDMATxStartI(
    struct devData *    devData);


/**@brief       Stop TX DMA activity
 * @param       devData
 *              Device data structure
 * @return      Operation status
 *  @retval     0 - success
 *  @retval     -EBUSY - DMA channel is still active
 */
int32_t portDMATxStopI(
    struct devData *    devData);

/** @} *//*-----------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of port.h
 ******************************************************************************/
#endif /* PORT_H_ */
