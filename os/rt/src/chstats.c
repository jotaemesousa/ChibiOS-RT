/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012,2013 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    chstats.c
 * @brief   Statistics module code.
 *
 * @addtogroup statistics
 * @details Statistics services.
 * @{
 */

#include "ch.h"

#if CH_DBG_STATISTICS || defined(__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes the statistics module.
 *
 * @init
 */
void _stats_init(void) {

  ch.kernel_stats.n_irq = 0;
  ch.kernel_stats.n_ctxswc = 0;
  chTMObjectInit(&ch.kernel_stats.m_crit_thd);
  chTMObjectInit(&ch.kernel_stats.m_crit_isr);
}

/**
 * @brief   Increases the IRQ counter.
 */
void _stats_increase_irq(void) {

  ch.kernel_stats.n_irq++;
}

/**
 * @brief   Updates context switch related statistics.
 */
void _stats_ctxswc(thread_t *ntp, thread_t *otp) {

  ch.kernel_stats.n_ctxswc++;
  chTMChainMeasurementToX(&otp->p_stats, &ntp->p_stats);
}

/**
 * @brief   Starts the measurement of a thread critical zone.
 */
void _stats_start_measure_crit_thd(void) {

  chTMStartMeasurementX(&ch.kernel_stats.m_crit_thd);
}

/**
 * @brief   Stops the measurement of a thread critical zone.
 */
void _stats_stop_measure_crit_thd(void) {

  chTMStopMeasurementX(&ch.kernel_stats.m_crit_thd);
}

/**
 * @brief   Starts the measurement of an ISR critical zone.
 */
void _stats_start_measure_crit_isr(void) {

  chTMStartMeasurementX(&ch.kernel_stats.m_crit_isr);
}

/**
 * @brief   Stops the measurement of an ISR critical zone.
 */
void _stats_stop_measure_crit_isr(void) {

  chTMStopMeasurementX(&ch.kernel_stats.m_crit_isr);
}

#endif /* CH_DBG_STATISTICS */

/** @} */
