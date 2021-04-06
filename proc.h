/* SPDX-License-Identifier: LGPL-3.0-or-later */

/** @file
 * @brief PTP management TLV structures
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2021 Erez Geva
 *
 */

#ifndef __PMC_PROC_H
#define __PMC_PROC_H

#include <cstdint>
#include <vector>
#include "msg.h"

/** Clock description TLV */
struct CLOCK_DESCRIPTION_t : public BaseMngTlv {
    uint16_t clockType; /**< Clock type bit mask */
    PTPText_t physicalLayerProtocol; /**< Physical protocol */
    UInteger16_t physicalAddressLength; /**< Address length */
    Binary physicalAddress; /**< Physical address */
    PortAddress_t protocolAddress; /**< Protocol address */
    Octet_t manufacturerIdentity[3]; /**< IEEE OUI */
    PTPText_t productDescription; /**< Product description */
    PTPText_t revisionData; /**< Revision data */
    PTPText_t userDescription; /**< User description */
    Octet_t profileIdentity[6]; /**< Profile ID */
};
/** User description TLV */
struct USER_DESCRIPTION_t : public BaseMngTlv {
    PTPText_t userDescription; /**< User description */
};
const uint16_t INITIALIZE_EVENT = 0x0000; /**< Initialize event */
/** Initialize TLV */
struct INITIALIZE_t : public BaseMngTlv {
    uint16_t initializationKey; /**< Initialization key */
};
/** Fault logging table TLV */
struct FAULT_LOG_t : public BaseMngTlv {
    UInteger16_t numberOfFaultRecords; /**< Number of fault records */
    std::vector<FaultRecord_t> faultRecords; /**< Fault records table */
};
/** Default data settings */
struct DEFAULT_DATA_SET_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: TSC defaultDS.twoStepFlag
     * @li bit 1: SO  defaultDS.slaveOnly
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x3; /**< Mask for flags */
    UInteger16_t numberPorts; /**< Number of ports */
    UInteger8_t priority1; /**< Priority 1 */
    ClockQuality_t clockQuality; /**< Clock quality */
    UInteger8_t priority2; /**< Priority 2 */
    ClockIdentity_t clockIdentity; /**< Clock ID */
    UInteger8_t domainNumber; /**< Domain ID number */
};
/** Current data setting TLV */
struct CURRENT_DATA_SET_t : public BaseMngTlv {
    UInteger16_t stepsRemoved; /**< Steps removed */
    TimeInterval_t offsetFromMaster; /**< Offset from source clock */
    TimeInterval_t meanPathDelay; /**< Mean path delay to source */
};
/** Parent data set TLV */
struct PARENT_DATA_SET_t : public BaseMngTlv {
    PortIdentity_t parentPortIdentity; /**< Port ID of parent */
    /**
     * Bit fields flag
     * @li bit 0: PS parentDS.parentStats
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
    /** The variance of the parent clock's phase as
        measured by the local clock */
    UInteger16_t observedParentOffsetScaledLogVariance;
    /** Estimate of the parent clock's phase change rate as
        measured by the client clock */
    Integer32_t observedParentClockPhaseChangeRate;
    UInteger8_t grandmasterPriority1; /**< Grand source Priority 1 */
    ClockQuality_t grandmasterClockQuality; /**< Grand source clock quality */
    UInteger8_t grandmasterPriority2; /**< Grand source Priority 1 */
    ClockIdentity_t grandmasterIdentity; /**< Grand source clock ID */
};
/** Time properties data set TLV */
struct TIME_PROPERTIES_DATA_SET_t : public BaseMngTlv {
    Integer16_t currentUtcOffset; /**< current TAI to UTC offset, leap seconds */
    /**
     * Bit fields flag
     * @li bit 0: LI-61 timePropertiesDS.leap61
     * @li bit 1: LI-59 timePropertiesDS.leap59
     * @li bit 2: UTCV  timePropertiesDS.currentUtcOffsetValid
     * @li bit 3: PTP   timePropertiesDS.ptpTimescale
     * @li bit 4: TTRA  timePropertiesDS.timeTraceable
     * @li bit 5: FTRA  timePropertiesDS.frequencyTraceable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x3f; /**< Mask for flags */
    timeSource_e timeSource; /**< Source clock type */
};
/** Port data set TLV */
struct PORT_DATA_SET_t : public BaseMngTlv {
    PortIdentity_t portIdentity; /**< Port ID */
    portState_e portState; /**< Port state */
    /** the minimum permitted mean time interval between
        successive Delay_Req messages */
    Integer8_t logMinDelayReqInterval;
    TimeInterval_t peerMeanPathDelay; /**< Mean path delay to peer */
    /** the mean time interval between successive Announce messages */
    Integer8_t logAnnounceInterval;
    /** specify the number of announceInterval that has to
        pass without receipt of an Announce */
    UInteger8_t announceReceiptTimeout;
    /** the mean time interval between successive Sync messages */
    Integer8_t logSyncInterval;
    /**
     * Delay mechanism values
     * @li 1: E2E - end to end, delay request-response
     * @li 2: P2P - peer to peer, peer delay
     * @li 0xfe:  - disabled
     */
    uint8_t delayMechanism;
    /** the minimum permitted mean time interval between
        successive Pdelay_Req messages */
    Integer8_t logMinPdelayReqInterval;
    /**
     * PTP version in use on port
     * @li Nibble:  major version
     * @li Nibble:  reserved. Probably minor version in next versions
     */
    Nibble_t versionNumber;
};
/** Priority 1 TLV */
struct PRIORITY1_t : public BaseMngTlv {
    UInteger8_t priority1; /**< Priority 1 */
};
/** Priority 2 TLV */
struct PRIORITY2_t : public BaseMngTlv {
    UInteger8_t priority2; /**< Priority 2 */
};
/** Domain TLV */
struct DOMAIN_t : public BaseMngTlv {
    UInteger8_t domainNumber; /**< Domain ID number */
};
/** Client only flag TLV */
struct SLAVE_ONLY_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: SO  defaultDS.slaveOnly
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Log announce interval TLV */
struct LOG_ANNOUNCE_INTERVAL_t : public BaseMngTlv {
    /** the mean time interval between successive Announce messages */
    Integer8_t logAnnounceInterval;
};
/** Announce receipt timeout TLV */
struct ANNOUNCE_RECEIPT_TIMEOUT_t : public BaseMngTlv {
    /** Specify the number of announce interval that must
        pass without receipt of an announce */
    UInteger8_t announceReceiptTimeout;
};
/** Log synchronization interval TLV */
struct LOG_SYNC_INTERVAL_t : public BaseMngTlv {
    /** the mean time interval between successive Sync messages */
    Integer8_t logSyncInterval;
};
/** Version number TLV */
struct VERSION_NUMBER_t : public BaseMngTlv {
    /**
     * PTP version in use on port
     * @li Nibble:  major version
     * @li Nibble:  reserved. Probably minor version in next versions
     */
    Nibble_t versionNumber;
};
/** Current time TLV */
struct TIME_t : public BaseMngTlv {
    Timestamp_t currentTime; /**< Current time stamp */
};
/** Clock accuracy TLV */
struct CLOCK_ACCURACY_t : public BaseMngTlv {
    clockAccuracy_e clockAccuracy; /**< Clock accuracy */
};
/** Utc properties TLV */
struct UTC_PROPERTIES_t : public BaseMngTlv {
    Integer16_t currentUtcOffset; /**< current TAI to UTC offset, leap seconds */
    /**
     * Bit fields flag
     * @li bit 0: LI-61 timePropertiesDS.leap61
     * @li bit 1: LI-59 timePropertiesDS.leap59
     * @li bit 2: UTCV  timePropertiesDS.currentUtcOffsetValid
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x7; /**< Mask for flags */
};
/** Traceability properties TLV */
struct TRACEABILITY_PROPERTIES_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 4: TTRA  timePropertiesDS.timeTraceable
     * @li bit 5: FTRA  timePropertiesDS.frequencyTraceable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x30; /**< Mask for flags */
};
/** Timescale properties TLV */
struct TIMESCALE_PROPERTIES_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 3: PTP   timePropertiesDS.ptpTimescale
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x8; /**< Mask for flags */
    timeSource_e timeSource; /**< Source clock type */
};
/** Unicast negotiation enables TLV */
struct UNICAST_NEGOTIATION_ENABLE_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EN - unicastNegotiationPortDS.enable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Path trace list TLV */
struct PATH_TRACE_LIST_t : public BaseMngTlv {
    std::vector<ClockIdentity_t> pathSequence; /**< clock id per path */
};
/** Path-trace enable TLV */
struct PATH_TRACE_ENABLE_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EN pathTraceDS.enable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Grand source cluster table TLV */
struct GRANDMASTER_CLUSTER_TABLE_t : public BaseMngTlv {
    /** logarithm to the base 2 of the mean interval in seconds between
        unicast Announce messages from grand source */
    Integer8_t logQueryInterval;
    UInteger8_t actualTableSize; /**< Number of addresses table */
    /** Port addresses of grand sources cluster */
    std::vector<PortAddress_t> PortAddress;
};
/** Unicast source table TLV */
struct UNICAST_MASTER_TABLE_t : public BaseMngTlv {
    /** logarithm to the base 2 of the mean interval in seconds between
        unicast Announce messages from source */
    Integer8_t logQueryInterval;
    UInteger16_t actualTableSize; /**< Number of addresses table */
    /** Port addresses of unicast sources */
    std::vector<PortAddress_t> PortAddress;
};
/** Unicast source maximum table size TLV */
struct UNICAST_MASTER_MAX_TABLE_SIZE_t : public BaseMngTlv {
    /** Maximum number of addresses in unicast sources table */
    UInteger16_t maxTableSize;
};
/** Acceptable source table TLV */
struct ACCEPTABLE_MASTER_TABLE_t : public BaseMngTlv {
    Integer16_t actualTableSize; /**< Number of addresses table */
    /** Acceptable source table records */
    std::vector<AcceptableMaster_t> list;
};
/** Acceptable source table enabled TLV */
struct ACCEPTABLE_MASTER_TABLE_ENABLED_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EN acceptableMasterPortDS.enable.
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Acceptable source maximum table size TLV */
struct ACCEPTABLE_MASTER_MAX_TABLE_SIZE_t : public BaseMngTlv {
    /** The maximum permitted number of addresses
         in the Acceptable source table */
    UInteger16_t maxTableSize;
};
/** Alternate source TLV */
struct ALTERNATE_MASTER_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: S - alternateMasterPortDS.transmitAlternateMulticastSync
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
    /** Logarithm to the base 2 of the mean period in seconds
        between Sync messages used by alternate source */
    Integer8_t logAlternateMulticastSyncInterval;
    /** Number of alternate sources */
    UInteger8_t numberOfAlternateMasters;
};
/** Alternate time offset enables TLV */
struct ALTERNATE_TIME_OFFSET_ENABLE_t : public BaseMngTlv {
    UInteger8_t keyField; /**< the index to the alternate timescale offsets */
    /**
     * Bit fields flag
     * @li bit 0: EN alternateTimescaleOffsetsDS.list[keyField].enable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Alternate time offset name TLV */
struct ALTERNATE_TIME_OFFSET_NAME_t : public BaseMngTlv {
    UInteger8_t keyField; /**< the index to the alternate timescale offsets */
    PTPText_t displayName; /**< Name of the alternate timescale offset */
};
/** Alternate time offset maximum key TLV */
struct ALTERNATE_TIME_OFFSET_MAX_KEY_t : public BaseMngTlv {
    UInteger8_t maxKey; /**< number of alternate timescales maintained */
};
/** Alternate time offset properties TLV */
struct ALTERNATE_TIME_OFFSET_PROPERTIES_t : public BaseMngTlv {
    UInteger8_t keyField; /**< the index to the alternate timescale offsets */
    Integer32_t currentOffset; /**< Current offset */
    Integer32_t jumpSeconds; /**< Jump seconds */
    UInteger48_t timeOfNextJump; /**< Time of next jump */
};
/** Transparent clock port data set TLV */
struct TRANSPARENT_CLOCK_PORT_DATA_SET_t : public BaseMngTlv {
    PortIdentity_t portIdentity; /**< Port ID */
    /**
     * Bit fields flag
     * @li bit 0: FLT transparentClockPortDS.faultyFlag
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
    /** the minimum permitted mean time interval between
        successive Pdelay_Req messages */
    Integer8_t logMinPdelayReqInterval;
    TimeInterval_t peerMeanPathDelay; /**< Mean path delay to peer */
};
/** Log min pdelay req interval TLV */
struct LOG_MIN_PDELAY_REQ_INTERVAL_t : public BaseMngTlv {
    /** the minimum permitted mean time interval between
        successive Pdelay_Req messages */
    Integer8_t logMinPdelayReqInterval;
};
/** Transparent clock default data set TLV */
struct TRANSPARENT_CLOCK_DEFAULT_DATA_SET_t : public BaseMngTlv {
    ClockIdentity_t clockIdentity; /**< Clock ID */
    UInteger16_t numberPorts; /**< Number of ports */
    /**
     * Delay mechanism values
     * @li 1: E2E - end to end, delay request-response
     * @li 2: P2P - peer to peer, peer delay
     * @li 0xfe:  - disabled
     */
    uint8_t delayMechanism;
    UInteger8_t primaryDomain; /**< Primary Domain ID number */
};
/** Primary domain TLV */
struct PRIMARY_DOMAIN_t : public BaseMngTlv {
    UInteger8_t primaryDomain; /**< Primary Domain ID number */
};
/** Delay mechanism TLV */
struct DELAY_MECHANISM_t : public BaseMngTlv {
    /**
     * Delay mechanism values
     * @li 1: E2E - end to end, delay request-response
     * @li 2: P2P - peer to peer, peer delay
     * @li 0xfe:  - disabled
     */
    uint8_t delayMechanism;
};
/** External port configuration enabled TLV */
struct EXTERNAL_PORT_CONFIGURATION_ENABLED_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EPC defaultDS.externalPortConfigurationEnabled
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Source only TLV */
struct MASTER_ONLY_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: MO - portDS.masterOnly
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** Holdover-upgrade enable TLV */
struct HOLDOVER_UPGRADE_ENABLE_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EN holdoverUpgradeDS.enable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
};
/** External port config port data setting TLV */
struct EXT_PORT_CONFIG_PORT_DATA_SET_t : public BaseMngTlv {
    /**
     * Bit fields flag
     * @li bit 0: EN acceptableMasterPortDS.enable.
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x1; /**< Mask for flags */
    portState_e desiredState; /**< Desired port state */
};
/** TIME_STATUS_NP.cumulativeScaledRateOffset scale factor */
const double P41 = 1ULL << 41;
/** Time status TLV
 * @note linuxptp implementation specific
 */
struct TIME_STATUS_NP_t : public BaseMngTlv {
    int64_t master_offset; /**< Offset from source clock in nanoseconds */
    int64_t ingress_time;  /**< Ingress time in nanoseconds */
    /** Cumulative scaled rate offset */
    Integer32_t cumulativeScaledRateOffset;
    /** Scaled last grand source phase change */
    Integer32_t scaledLastGmPhaseChange;
    /** Grand source time base indicator */
    UInteger16_t gmTimeBaseIndicator;
    /** Scaled last grand source phase change, MSB part of nanoseconds */
    uint16_t nanoseconds_msb;
    /** Scaled last grand source phase change, LSB part of nanoseconds */
    uint64_t nanoseconds_lsb;
    /** Scaled last grand source phase change, nanosecond fraction */
    uint16_t fractional_nanoseconds;
    Integer32_t gmPresent; /**< Flag for grand source presence */
    ClockIdentity_t gmIdentity; /**< Grand source clock ID */
};
/** Grand source settings TLV
 * @note linuxptp implementation specific
 */
struct GRANDMASTER_SETTINGS_NP_t : public BaseMngTlv {
    ClockQuality_t clockQuality; /**< Clock quality */
    Integer16_t currentUtcOffset; /**< current TAI to UTC offset, leap seconds */
    /**
     * Bit fields flag
     * @li bit 0: LI-61 timePropertiesDS.leap61
     * @li bit 1: LI-59 timePropertiesDS.leap59
     * @li bit 2: UTCV  timePropertiesDS.currentUtcOffsetValid
     * @li bit 3: PTP   timePropertiesDS.ptpTimescale
     * @li bit 4: TTRA  timePropertiesDS.timeTraceable
     * @li bit 5: FTRA  timePropertiesDS.frequencyTraceable
     */
    uint8_t flags;
    const uint8_t flagsMask = 0x3f; /**< Mask for flags */
    timeSource_e timeSource; /**< Source clock type */
};
/** Port data setting TLV
 * @note linuxptp implementation specific
 */
struct PORT_DATA_SET_NP_t : public BaseMngTlv {
    /** Neighbour proper delay threshold in nanoseconds */
    UInteger32_t neighborPropDelayThresh;
    Integer32_t asCapable; /**< Flag for 802@.1AS Capable */
};
/** SUBSCRIBE_EVENTS_NP.bitmask size */
const int EVENT_BITMASK_CNT = 64;
/** Notify port state offset in SUBSCRIBE_EVENTS_NP.bitmask */
const int NOTIFY_PORT_STATE = 0;
/** Notify time synchronization offset in SUBSCRIBE_EVENTS_NP.bitmask */
const int NOTIFY_TIME_SYNC = 1;
/** Set bit in SUBSCRIBE_EVENTS_NP.bitmask */
#define EVENT_BIT_SET(bitmask, event)\
    do{ bitmask[event / 8] |= (1 << (event % 8)); }while(false)
/** Clear bit in SUBSCRIBE_EVENTS_NP.bitmask */
#define EVENT_BIT_CLEAR(bitmask, event)\
    do{ bitmask[event / 8] &= ~((uint8_t)(1 << (event % 8))); }while(false)
/** Read bit value in SUBSCRIBE_EVENTS_NP.bitmask */
#define EVENT_BIT(bitmask, event)\
    (bitmask[event / 8] & (1 << (event % 8))?"on":"off")
/** Subscribe events TLV
 * @note linuxptp implementation specific
 */
struct SUBSCRIBE_EVENTS_NP_t : public BaseMngTlv {
    uint16_t duration; /**< duration in seconds */
    uint8_t bitmask[EVENT_BITMASK_CNT]; /**< bitmask of events state */
};
/** Port properties TLV
 * @note linuxptp implementation specific
 */
struct PORT_PROPERTIES_NP_t : public BaseMngTlv {
    PortIdentity_t portIdentity; /**< Port ID */
    portState_e portState; /**< Port state */
    linuxptpTimeStamp_e timestamping; /**< time stamping in linuxptp format */
    PTPText_t interface; /**< Linux interface name */
};
/** size of PORT_STATS_NP rxMsgType and txMsgType */
const int MAX_MESSAGE_TYPES = 16;
/** Sync messages count in PORT_STATS_NP */
const int STAT_SYNC = 0;
/** Delay_Req messages count in PORT_STATS_NP */
const int STAT_DELAY_REQ = 1;
/** Pdelay_Req messages count in PORT_STATS_NP */
const int STAT_PDELAY_REQ = 2;
/** Pdelay_Resp messages count in PORT_STATS_NP */
const int STAT_PDELAY_RESP = 3;
/** Follow_Up messages count in PORT_STATS_NP */
const int STAT_FOLLOW_UP = 8;
/** Delay_Resp messages count in PORT_STATS_NP */
const int STAT_DELAY_RESP = 9;
/** Pdelay_Resp_Follow_Up messages count in PORT_STATS_NP */
const int STAT_PDELAY_RESP_FOLLOW_UP = 10;
/** Announce messages count in PORT_STATS_NP */
const int STAT_ANNOUNCE = 11;
/** Signaling messages count in PORT_STATS_NP */
const int STAT_SIGNALING = 12;
/** Management messages count in PORT_STATS_NP */
const int STAT_MANAGEMENT = 13;
/** Port statistics TLV
 * @note linuxptp implementation specific
 */
struct PORT_STATS_NP_t : public BaseMngTlv {
    PortIdentity_t portIdentity; /**< Port ID */
    /** Port received messages count per PTP message type */
    uint64_t rxMsgType[MAX_MESSAGE_TYPES];
    /** Port transmitted messages count per PTP message type */
    uint64_t txMsgType[MAX_MESSAGE_TYPES];
};
/** SYNCHRONIZATION_UNCERTAIN_NP uncertain false state */
const uint8_t SYNC_UNCERTAIN_FALSE = 0;
/** SYNCHRONIZATION_UNCERTAIN_NP uncertain true state */
const uint8_t SYNC_UNCERTAIN_TRUE = 1;
/** SYNCHRONIZATION_UNCERTAIN_NP uncertain do not care state */
const uint8_t SYNC_UNCERTAIN_DONTCARE = 0xff;
/** Synchronization uncertain TLV
 * @note linuxptp implementation specific
 */
struct SYNCHRONIZATION_UNCERTAIN_NP_t : public BaseMngTlv {
    /**
     * synchronization uncertain state
     * @li 0:       False
     * @li 1:       True
     * @li 0xff:    Do not care
     */
    uint8_t val;
};

#endif /*__PMC_PROC_H*/
