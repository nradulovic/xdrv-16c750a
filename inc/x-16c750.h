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
 * @brief       Driver level shared types
 *********************************************************************//** @{ */

#if !defined(X_16C750_H_)
#define X_16C750_H_

/*=========================================================  INCLUDE FILES  ==*/

#include <linux/platform_device.h>
#include <linux/circ_buf.h>

#include <rtdm/rtserial.h>
#include <rtdm/rtdm_driver.h>
#include <native/heap.h>
#include <native/queue.h>

#include "circ_buff.h"

/*===============================================================  MACRO's  ==*/

/**@brief       Return value: operation was successful
 */
#define RETVAL_SUCCESS                  0
#define RETVAL_FAILURE                  -1

/*------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================  DATA TYPES  ==*/

enum uartStatus {
    UART_STATUS_NORMAL,
    UART_STATUS_SOFT_OVERFLOW
};

struct uartUnit {
    RT_HEAP             heapHandle;
    RT_QUEUE            queueHandle;
    CIRC_BUFF           buffHandle;                                             /**<@brief Buffer handle                                    */
    nanosecs_rel_t      timeout;
    rtdm_mutex_t        mtx;
    void *              queue;                                                  /**<@brief Buffer storage                                   */
    int                 status;
};

/**@brief       UART device context structure
 */
struct uartCtx {
    rtdm_lock_t         lock;                                                   /**<@brief Lock to protect this structure                   */
    rtdm_irq_t          irqHandle;                                              /**<@brief IRQ routine handler structure                    */
    struct rtdm_device *        rtdev;                                          /**<@brief Real-time device driver                          */
    struct platform_device *    platDev;                                        /**<@brief Linux kernel device driver                       */
    u32                 id;                                                     /**<@brief UART ID number (maybe unused)                    */
    volatile u8 *       io;                                                     /**<@brief Remaped IO memory area                           */
    struct uartUnit     tx;
    struct uartUnit     rx;
};

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/
/*--------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of x-16c750.h
 ******************************************************************************/
#endif /* X_16C750_H_ */
