/* SPDX-License-Identifier: LGPL-3.0-or-later */

/** @file
 * @brief List of management IDs
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2021 Erez Geva
 *
 * This header is design to be multiple included
 */

/*
 * Use:
 *  #define A(n, v, sc, a, sz, f) <macro text>
 *  #include "ids.h"
 */
#ifndef IDS_START
#define IDS_START
#endif
#ifndef IDS_END
#define IDS_END
#endif
#ifndef caseNA
#define caseNA(n)
#endif
#ifndef caseUF
#define caseUF(n)
#endif
#ifndef caseUFS
#define caseUFS(n) caseUF(n)
#endif
#ifndef caseUFB
#define caseUFB(n) caseUF(n)
#endif
#ifndef caseUFBS
#define caseUFBS(n) caseUFB(n)
#endif
#define use_GSC A_GET | A_SET | A_COMMAND
#define use_GS  A_GET | A_SET
/*
 * For functions use
 * #define caseNA(n)    <macro text>
 * #define caseUF(n)    <macro text>
 * #define caseUFB(n)   <macro text>
 * NA = no functions needed
 * UF   - functions for parsing
 * UFS  - functions for parsing having variable size
 * UFB  - functions for parsing and build
 * UFBS - functions for parsing and build having variable size
 */
#ifndef FIRST_MNG_ID
#define FIRST_MNG_ID NULL_PTP_MANAGEMENT
#endif
/*
 * NULL_MANAGEMENT is the name from "IEEE Std 1588-2008"
 * NULL_PTP_MANAGEMENT is the name from "IEEE Std 1588-2019"
 */
#ifndef NULL_MANAGEMENT
#define NULL_MANAGEMENT NULL_PTP_MANAGEMENT
#endif
/*
 * size: > 0  fixed size dataField
 *         0  No dataField (with NA)
 *        -2  Variable length dataField, need calculation
 */
/*Name                                 value scope  allow       size   func*/
IDS_START
A(NULL_PTP_MANAGEMENT,                 0000, port,  use_GSC,    0,     NA)
A(CLOCK_DESCRIPTION,                   0001, port,  A_GET,     -2,     UFS)
A(USER_DESCRIPTION,                    0002, clock, use_GS,    -2,     UFBS)
A(SAVE_IN_NON_VOLATILE_STORAGE,        0003, clock, A_COMMAND,  0,     NA)
A(RESET_NON_VOLATILE_STORAGE,          0004, clock, A_COMMAND,  0,     NA)
A(INITIALIZE,                          0005, clock, A_COMMAND,  2,     UFB)
A(FAULT_LOG,                           0006, clock, A_GET,     -2,     UFS)
A(FAULT_LOG_RESET,                     0007, clock, A_COMMAND,  0,     NA)
A(DEFAULT_DATA_SET,                    2000, clock, A_GET,     20,     UF)
A(CURRENT_DATA_SET,                    2001, clock, A_GET,     18,     UF)
A(PARENT_DATA_SET,                     2002, clock, A_GET,     32,     UF)
A(TIME_PROPERTIES_DATA_SET,            2003, clock, A_GET,      4,     UF)
A(PORT_DATA_SET,                       2004, port,  A_GET,     26,     UF)
A(PRIORITY1,                           2005, clock, use_GS,     2,     UFB)
A(PRIORITY2,                           2006, clock, use_GS,     2,     UFB)
A(DOMAIN,                              2007, clock, use_GS,     2,     UFB)
A(SLAVE_ONLY,                          2008, clock, use_GS,     2,     UFB)
A(LOG_ANNOUNCE_INTERVAL,               2009, port,  use_GS,     2,     UFB)
A(ANNOUNCE_RECEIPT_TIMEOUT,            200a, port,  use_GS,     2,     UFB)
A(LOG_SYNC_INTERVAL,                   200b, port,  use_GS,     2,     UFB)
A(VERSION_NUMBER,                      200c, port,  use_GS,     2,     UFB)
A(ENABLE_PORT,                         200d, port,  A_COMMAND,  0,     NA)
A(DISABLE_PORT,                        200e, port,  A_COMMAND,  0,     NA)
A(TIME,                                200f, clock, use_GS,    10,     UFB)
A(CLOCK_ACCURACY,                      2010, clock, use_GS,     2,     UFB)
A(UTC_PROPERTIES,                      2011, clock, use_GS,     4,     UFB)
A(TRACEABILITY_PROPERTIES,             2012, clock, use_GS,     2,     UFB)
A(TIMESCALE_PROPERTIES,                2013, clock, use_GS,     2,     UFB)
A(UNICAST_NEGOTIATION_ENABLE,          2014, port,  use_GS,     2,     UFB)
A(PATH_TRACE_LIST,                     2015, clock, A_GET,     -2,     UFS)
A(PATH_TRACE_ENABLE,                   2016, clock, use_GS,     2,     UFB)
A(GRANDMASTER_CLUSTER_TABLE,           2017, clock, use_GS,    -2,     UFBS)
A(UNICAST_MASTER_TABLE,                2018, port,  use_GS,    -2,     UFBS)
A(UNICAST_MASTER_MAX_TABLE_SIZE,       2019, port,  A_GET,      2,     UF)
A(ACCEPTABLE_MASTER_TABLE,             201a, clock, use_GS,    -2,     UFBS)
A(ACCEPTABLE_MASTER_TABLE_ENABLED,     201b, port,  use_GS,     2,     UFB)
A(ACCEPTABLE_MASTER_MAX_TABLE_SIZE,    201c, clock, A_GET,      2,     UF)
A(ALTERNATE_MASTER,                    201d, port,  use_GS,     4,     UFB)
A(ALTERNATE_TIME_OFFSET_ENABLE,        201e, clock, use_GS,     2,     UFB)
A(ALTERNATE_TIME_OFFSET_NAME,          201f, clock, use_GS,    -2,     UFBS)
A(ALTERNATE_TIME_OFFSET_MAX_KEY,       2020, clock, A_GET,      2,     UF)
A(ALTERNATE_TIME_OFFSET_PROPERTIES,    2021, clock, use_GS,    16,     UFB)
A(TRANSPARENT_CLOCK_PORT_DATA_SET,     4001, port,  A_GET,     20,     UF)
A(LOG_MIN_PDELAY_REQ_INTERVAL,         6001, port,  use_GS,     2,     UFB)
/* Deprecated in "IEEE Std 1588-2019" */
A(TRANSPARENT_CLOCK_DEFAULT_DATA_SET,  4000, clock, A_GET,     12,     UF)
A(PRIMARY_DOMAIN,                      4002, clock, use_GS,     2,     UFB)
A(DELAY_MECHANISM,                     6000, port,  use_GS,     2,     UFB)
/* From "IEEE Std 1588-2019" */
A(EXTERNAL_PORT_CONFIGURATION_ENABLED, 3000, clock, use_GS,     2,     UFB)
A(MASTER_ONLY,                         3001, port,  use_GS,     2,     UFB)
A(HOLDOVER_UPGRADE_ENABLE,             3002, clock, use_GS,     2,     UFB)
A(EXT_PORT_CONFIG_PORT_DATA_SET,       3003, port,  use_GS,     2,     UFB)
/* linuxptp TLVs (in Implementation-specific C000-DFFF) */
#define use_GL  A_GET | A_USE_LINUXPTP
#define use_GSL A_GET | A_SET | A_USE_LINUXPTP
A(TIME_STATUS_NP,                      c000, clock, use_GL,    50,     UF)
A(GRANDMASTER_SETTINGS_NP,             c001, clock, use_GSL,    8,     UFB)
A(PORT_DATA_SET_NP,                    c002, port,  use_GSL,    8,     UFB)
A(SUBSCRIBE_EVENTS_NP,                 c003, clock, use_GSL,   66,     UFB)
A(PORT_PROPERTIES_NP,                  c004, port,  use_GL,    -2,     UFS)
A(PORT_STATS_NP,                       c005, port,  use_GL,   266,     UF)
A(SYNCHRONIZATION_UNCERTAIN_NP,        c006, clock, use_GSL,    2,     UFB)
IDS_END
#ifndef LAST_MNG_ID
#define LAST_MNG_ID SYNCHRONIZATION_UNCERTAIN_NP
#endif
#undef A
#undef use_GSC
#undef use_GS
#undef use_GL
#undef use_GSL
#undef caseNA
#undef caseNS
#undef caseUF
#undef caseUFS
#undef caseUFB
#undef caseUFBS
#undef IDS_START
#undef IDS_END
