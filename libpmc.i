/* SPDX-License-Identifier: LGPL-3.0-or-later */

/* libpmc.i Library Swig header file
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2021 Erez Geva
 *
 */

#ifdef SWIGPERL
%module PmcLib
#else
%module pmc
#endif
%{
    #include "cfg.h"
    #include "msg.h"
    #include "ptp.h"
    #include "sock.h"
    #include "bin.h"
%}

%include "stdint.i"
%include "std_string.i"
%include "std_vector.i"
%apply long { ssize_t };
%include "cfg.h"
#ifdef SWIGRUBY
/* Ignore Wrong constant name */
%warnfilter(801) clockType_e;
%warnfilter(801) implementSpecific_e;
/* operator overload ignored, scripts can use Binary::append() */
%warnfilter(365) Binary::operator+=;
#endif
%include "msg.h"
%include "ptp.h"
%include "sock.h"
%include "bin.h"
%include "proc.h"
%include "sig.h"
%include "mngIds.h"
%include "cpointer.i"
/* Handle management and signalig vectors inside structures */
namespace std {
  %template(FaultRecord_v) vector<FaultRecord_t>;
  %template(ClockIdentity_v) vector<ClockIdentity_t>;
  %template(PortAddress_v) vector<PortAddress_t>;
  %template(AcceptableMaster_v) vector<AcceptableMaster_t>;
  %template(SigTime) vector<SLAVE_RX_SYNC_TIMING_DATA_rec_t>;
  %template(SigComp) vector<SLAVE_RX_SYNC_COMPUTED_DATA_rec_t>;
  %template(SigEvent) vector<SLAVE_TX_EVENT_TIMESTAMPS_rec_t>;
  %template(SigDelay) vector<SLAVE_DELAY_TIMING_DATA_NP_rec_t>;
};
/* Allow script to convert a string to a buffer
 * The script need to ensure the string length is proper */
%pointer_cast(char*, void*, conv_buf);
/* convert management tlv from base pointer */
#define caseUF(n) %pointer_cast(BaseMngTlv*, n##_t*, conv_##n);
#define A(n, v, sc, a, sz, f) case##f(n)
%include "ids.h"
/* convert TLV from signaling message from base pointer */
#define sigCnv(n) %pointer_cast(BaseSigTlv*, n##_t*, conv_##n);
sigCnv(ORGANIZATION_EXTENSION)
sigCnv(PATH_TRACE)
sigCnv(ALTERNATE_TIME_OFFSET_INDICATOR)
sigCnv(ENHANCED_ACCURACY_METRICS)
sigCnv(L1_SYNC)
sigCnv(PORT_COMMUNICATION_AVAILABILITY)
sigCnv(PROTOCOL_ADDRESS)
sigCnv(SLAVE_RX_SYNC_TIMING_DATA)
sigCnv(SLAVE_RX_SYNC_COMPUTED_DATA)
sigCnv(SLAVE_TX_EVENT_TIMESTAMPS)
sigCnv(CUMULATIVE_RATE_RATIO)
sigCnv(SLAVE_DELAY_TIMING_DATA_NP)
