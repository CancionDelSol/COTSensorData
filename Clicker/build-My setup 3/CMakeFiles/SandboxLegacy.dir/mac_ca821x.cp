#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 1 "mac_ca821x.h"
#line 6 "mac_ca821x.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;


typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 7 "mac_ca821x.h"
#line 8 "mac_ca821x.h"
#line 1 "ca821x_api.h"
#line 45 "ca821x_api.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stddef.h"



typedef long ptrdiff_t;


typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 46 "ca821x_api.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 47 "ca821x_api.h"
#line 48 "ca821x_api.h"
#line 1 "mac_messages.h"
#line 25 "mac_messages.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 26 "mac_messages.h"
#line 27 "mac_messages.h"
#line 1 "ieee_802_15_4.h"
#line 28 "mac_messages.h"
#line 1 "hwme_tdme.h"
#line 29 "mac_messages.h"










struct FullAddr {

	uint8_t         AddressMode;
	uint8_t         PANId[2];

	uint8_t         Address[8];
};


union MacAddr {
	uint16_t        ShortAddress;
	uint8_t         IEEEAddress[8];
};


struct SecSpec {

	uint8_t         SecurityLevel;

	uint8_t         KeyIdMode;

	uint8_t         KeySource[8];

	uint8_t         KeyIndex;
};


struct PanDescriptor {
	struct FullAddr Coord;
	uint8_t         LogicalChannel;
	uint8_t         SuperframeSpec[2];
#line 72 "mac_messages.h"
	uint8_t         GTSPermit;
	uint8_t         LinkQuality;

	uint8_t         TimeStamp[4];

	uint8_t         SecurityFailure;

	struct SecSpec  Security;
};

struct PendAddrSpec {
	uint8_t         ShortAddrCount : 3;
	uint8_t                        : 1;
	uint8_t         ExtAddrCount   : 3;
	uint8_t                        : 1;
};
#line 96 "mac_messages.h"
struct MCPS_DATA_request_pset {
	uint8_t         SrcAddrMode;
	struct FullAddr Dst;
	uint8_t         MsduLength;
	uint8_t         MsduHandle;
	uint8_t         TxOptions;
	uint8_t         Msdu[ (114) ];
};




struct MLME_ASSOCIATE_request_pset {
	uint8_t         LogicalChannel;
	struct FullAddr Dst;

	uint8_t         CapabilityInfo;
	struct SecSpec  Security;
};


struct MLME_ASSOCIATE_response_pset {

	uint8_t         DeviceAddress[8];
	uint8_t         AssocShortAddress[2];
	uint8_t         Status;
	struct SecSpec  Security;
};


struct MLME_DISASSOCIATE_request_pset {
	struct FullAddr DevAddr;
	uint8_t         DisassociateReason;
	uint8_t         TxIndirect;
 	struct SecSpec  Security;
};


struct MLME_GET_request_pset {
	uint8_t         PIBAttribute;
	uint8_t         PIBAttributeIndex;
};


struct MLME_ORPHAN_response_pset {
	uint8_t         OrphanAddress[8];
	uint8_t         ShortAddress[2];
	uint8_t         AssociatedMember;
	struct SecSpec  Security;
};


struct MLME_POLL_request_pset {
	struct FullAddr CoordAddress;
	uint8_t         Interval[2];


	struct SecSpec  Security;
};


struct MLME_RX_ENABLE_request_pset {
	uint8_t         DeferPermit;
	uint8_t         RxOnTime[4];
	uint8_t         RxOnDuration[4];
};


struct MLME_SCAN_request_pset {
	uint8_t         ScanType;
	uint8_t         ScanChannels[4];
	uint8_t         ScanDuration;
	struct SecSpec  Security;
};


struct MLME_SET_request_pset {
	uint8_t         PIBAttribute;
	uint8_t         PIBAttributeIndex;
	uint8_t         PIBAttributeLength;
	uint8_t         PIBAttributeValue[ (250) ];
};


struct MLME_START_request_pset {
	uint8_t         PANId[2];
	uint8_t         LogicalChannel;
	uint8_t         BeaconOrder;
	uint8_t         SuperframeOrder;
	uint8_t         PANCoordinator;
	uint8_t         BatteryLifeExtension;
	uint8_t         CoordRealignment;
	struct SecSpec  CoordRealignSecurity;
	struct SecSpec  BeaconSecurity;
};




struct HWME_SET_request_pset {
	uint8_t         HWAttribute;
	uint8_t         HWAttributeLength;
	uint8_t         HWAttributeValue[ 16 ];
};


struct HWME_GET_request_pset {
	uint8_t         HWAttribute;
};


struct HWME_HAES_request_pset {
	uint8_t            HAESMode;
	uint8_t            HAESData[16];
};




struct TDME_SETSFR_request_pset {
	uint8_t         SFRPage;
	uint8_t         SFRAddress;
	uint8_t         SFRValue;
};


struct TDME_GETSFR_request_pset {
	uint8_t         SFRPage;
	uint8_t         SFRAddress;
};


struct TDME_TESTMODE_request_pset {
	uint8_t            TestMode;
};


struct TDME_SET_request_pset {
	uint8_t         TDAttribute;
	uint8_t         TDAttributeLength;
	uint8_t         TDAttributeValue[ 2 ];
};


struct TDME_TXPKT_request_pset {
	uint8_t            TestPacketDataType;
	uint8_t            TestPacketSequenceNumber;
	uint8_t            TestPacketLength;
	uint8_t            TestPacketData[128];
};


struct TDME_LOTLK_request_pset {
	uint8_t            TestChannel;
	uint8_t            TestRxTxb;
};
#line 262 "mac_messages.h"
struct MCPS_DATA_confirm_pset {
	uint8_t            MsduHandle;
	uint8_t            Status;
	uint8_t            TimeStamp[4];
};


struct MCPS_PURGE_confirm_pset {
	uint8_t            MsduHandle;
	uint8_t            Status;
};


struct MCPS_DATA_indication_pset {
    struct FullAddr    Src;
    struct FullAddr    Dst;
    uint8_t            MsduLength;
    uint8_t            MpduLinkQuality;
    uint8_t            DSN;
    uint8_t            TimeStamp[4];
    uint8_t            Msdu[ (114) ];
};




struct MLME_ASSOCIATE_indication_pset {
	uint8_t            DeviceAddress[8];
	uint8_t            CapabilityInformation;
	struct SecSpec     Security;
};


struct MLME_ASSOCIATE_confirm_pset {
	uint8_t            AssocShortAddress[2];
	uint8_t            Status;
	struct SecSpec     Security;
};


struct MLME_DISASSOCIATE_confirm_pset {
	uint8_t            Status;
	struct FullAddr    Address;
};


struct MLME_DISASSOCIATE_indication_pset {
	uint8_t            DevAddr[8];
	uint8_t            Reason;
	struct SecSpec     Security;
};


struct MLME_BEACON_NOTIFY_indication_pset {
	uint8_t              BSN;
#line 319 "mac_messages.h"
	struct PanDescriptor PanDescriptor;



};


struct MLME_GET_confirm_pset {
	uint8_t            Status;
	uint8_t            PIBAttribute;
	uint8_t            PIBAttributeIndex;
	uint8_t            PIBAttributeLength;
	uint8_t            PIBAttributeValue[ (250) ];
};






struct MLME_SCAN_confirm_pset {
	uint8_t            Status;
	uint8_t            ScanType;
	uint8_t            UnscannedChannels[4];
	uint8_t            ResultListSize;
	uint8_t            ResultList[ (16) ];
};


struct MLME_COMM_STATUS_indication_pset {
	uint8_t            PANId[2];
	uint8_t            SrcAddrMode;
	uint8_t            SrcAddr[8];
	uint8_t            DstAddrMode;
	uint8_t            DstAddr[8];
	uint8_t            Status;
	struct SecSpec     Security;
};


struct MLME_ORPHAN_indication_pset {
	uint8_t            OrphanAddr[8];
	struct SecSpec     Security;
};


struct MLME_SYNC_LOSS_indication_pset {
	uint8_t            LossReason;
	uint8_t            PANId[2];
	uint8_t            LogicalChannel;
	struct SecSpec     Security;
};




struct HWME_SET_confirm_pset {
	uint8_t            Status;
	uint8_t            HWAttribute;
};


struct HWME_GET_confirm_pset {
	uint8_t            Status;
	uint8_t            HWAttribute;
	uint8_t            HWAttributeLength;
	uint8_t            HWAttributeValue[ 16 ];
};


struct HWME_HAES_confirm_pset {
	uint8_t            Status;
	uint8_t            HAESData[16];
};


struct HWME_WAKEUP_indication_pset {
	uint8_t            WakeUpCondition;
};




struct TDME_SETSFR_confirm_pset {
	uint8_t            Status;
	uint8_t            SFRPage;
	uint8_t            SFRAddress;
};


struct TDME_GETSFR_confirm_pset {
	uint8_t            Status;
	uint8_t            SFRPage;
	uint8_t            SFRAddress;
	uint8_t            SFRValue;
};


struct TDME_TESTMODE_confirm_pset {
	uint8_t            Status;
	uint8_t            TestMode;
};


struct TDME_SET_confirm_pset {
	uint8_t            Status;
	uint8_t            TDAttribute;
};


struct TDME_TXPKT_confirm_pset {
	uint8_t            Status;
	uint8_t            TestPacketSequenceNumber;
	uint8_t            TestPacketLength;
	uint8_t            TestPacketData[128];
};


struct TDME_RXPKT_indication_pset {
	uint8_t            Status;
	uint8_t            TestPacketEDValue;
	uint8_t            TestPacketCSValue;
	uint8_t            TestPacketFoffsValue;
	uint8_t            TestPacketLength;
	uint8_t            TestPacketData[128];
};


struct TDME_EDDET_indication_pset {
	uint8_t            TestEDThreshold;
	uint8_t            TestEDValue;
	uint8_t            TestCSValue;
	uint8_t            TestTimeAboveThreshold_us[2];
};


struct TDME_ERROR_indication_pset {
	uint8_t            ErrorCode;
};


struct TDME_LOTLK_confirm_pset {
	uint8_t            Status;
	uint8_t            TestChannel;
	uint8_t            TestRxTxb;
	uint8_t            TestLOFDACValue;
	uint8_t            TestLOAMPValue;
	uint8_t            TestLOTXCALValue;
};
#line 486 "mac_messages.h"
struct M_KeyIdLookupDesc {
    uint8_t      LookupData[9];
    uint8_t      LookupDataSizeCode;
};

struct M_DeviceDescriptor {
	uint8_t      PANId[2];
	uint8_t      ShortAddress[2];
	uint8_t      ExtAddress[8];
	uint8_t      FrameCounter[4];
	uint8_t      Exempt;
};

struct M_SecurityLevelDescriptor {
	uint8_t    FrameType;
	uint8_t    CommandFrameIdentifier;
	uint8_t    SecurityMinimum;
	uint8_t    DeviceOverrideSecurityMinimum;
};

struct M_KeyDeviceDesc {



	uint8_t      Flags;

};








struct M_KeyUsageDesc {


	uint8_t      Flags;
};








struct M_KeyTableEntryFixed {
	uint8_t    KeyIdLookupListEntries;
	uint8_t    KeyDeviceListEntries;
	uint8_t    KeyUsageListEntries;
	uint8_t    Key[16];
};

struct M_KeyDescriptor {
	struct M_KeyTableEntryFixed    Fixed;
	struct M_KeyIdLookupDesc       KeyIdLookupList[ (5) ];
	struct M_KeyDeviceDesc         KeyDeviceList[ (10) ];
	struct M_KeyUsageDesc          KeyUsageList[ (2) ];
};
#line 617 "mac_messages.h"
struct MAC_Message {
	uint8_t      CommandId;
	uint8_t      Length;
	union {

		struct MCPS_DATA_request_pset               DataReq;
		struct MLME_ASSOCIATE_request_pset          AssocReq;
		struct MLME_ASSOCIATE_response_pset         AssocRsp;
		struct MLME_DISASSOCIATE_request_pset       DisassocReq;
		struct MLME_GET_request_pset                GetReq;
		struct MLME_ORPHAN_response_pset            OrphanRsp;
		struct MLME_POLL_request_pset               PollReq;
		struct MLME_RX_ENABLE_request_pset          RxEnableReq;
		struct MLME_SCAN_request_pset               ScanReq;
		struct MLME_SET_request_pset                SetReq;
		struct MLME_START_request_pset              StartReq;
		struct MCPS_DATA_confirm_pset               DataCnf;
		struct MCPS_PURGE_confirm_pset              PurgeCnf;
		struct MCPS_DATA_indication_pset            DataInd;
		struct MLME_ASSOCIATE_indication_pset       AssocInd;
		struct MLME_ASSOCIATE_confirm_pset          AssocCnf;
		struct MLME_DISASSOCIATE_indication_pset    DisassocInd;
		struct MLME_DISASSOCIATE_confirm_pset       DisassocCnf;
		struct MLME_BEACON_NOTIFY_indication_pset   BeaconInd;
		struct MLME_GET_confirm_pset                GetCnf;
		struct MLME_SCAN_confirm_pset               ScanCnf;
		struct MLME_COMM_STATUS_indication_pset     CommStatusInd;
		struct MLME_SYNC_LOSS_indication_pset       SyncLossInd;
		struct MLME_ORPHAN_indication_pset          OrphanInd;

		struct HWME_SET_request_pset                HWMESetReq;
		struct HWME_GET_request_pset                HWMEGetReq;
		struct HWME_HAES_request_pset               HWMEHAESReq;
		struct HWME_SET_confirm_pset                HWMESetCnf;
		struct HWME_GET_confirm_pset                HWMEGetCnf;
		struct HWME_HAES_confirm_pset               HWMEHAESCnf;
		struct HWME_WAKEUP_indication_pset          HWMEWakeupInd;

		struct TDME_SETSFR_request_pset             TDMESetSFRReq;
		struct TDME_GETSFR_request_pset             TDMEGetSFRReq;
		struct TDME_TESTMODE_request_pset             TDMETestModeReq;
		struct TDME_SET_request_pset                TDMESetReq;
		struct TDME_TXPKT_request_pset                TDMETxPktReq;
		struct TDME_LOTLK_request_pset              TDMELOTlkReq;
		struct TDME_SETSFR_confirm_pset             TDMESetSFRCnf;
		struct TDME_GETSFR_confirm_pset             TDMEGetSFRCnf;
		struct TDME_TESTMODE_confirm_pset             TDMETestModeCnf;
		struct TDME_SET_confirm_pset                TDMESetCnf;
		struct TDME_TXPKT_confirm_pset                TDMETxPktCnf;
		struct TDME_RXPKT_indication_pset           TDMERxPktInd;
		struct TDME_EDDET_indication_pset           TDMEEDDetInd;
		struct TDME_ERROR_indication_pset           TDMEErrorInd;
		struct TDME_LOTLK_confirm_pset              TDMELOTlkCnf;

		uint8_t                                     u8Param;
		uint8_t                                     Status;
		uint8_t                                     Payload[254];
	} PData;
};
#line 49 "ca821x_api.h"
#line 76 "ca821x_api.h"
struct ca821x_api_callbacks {
	int (*MCPS_DATA_indication) (
		struct MCPS_DATA_indication_pset *params);
	int (*MCPS_DATA_confirm) (
		struct MCPS_DATA_confirm_pset *params);
	int (*MLME_ASSOCIATE_indication) (
		struct MLME_ASSOCIATE_indication_pset *params);
	int (*MLME_ASSOCIATE_confirm) (
		struct MLME_ASSOCIATE_confirm_pset *params);
	int (*MLME_DISASSOCIATE_indication) (
		struct MLME_DISASSOCIATE_indication_pset *params);
	int (*MLME_DISASSOCIATE_confirm) (
		struct MLME_DISASSOCIATE_confirm_pset *params);
	int (*MLME_BEACON_NOTIFY_indication) (
		struct MLME_BEACON_NOTIFY_indication_pset *params);
	int (*MLME_ORPHAN_indication) (
		struct MLME_ORPHAN_indication_pset *params);
	int (*MLME_SCAN_confirm) (
		struct MLME_SCAN_confirm_pset *params);
	int (*MLME_COMM_STATUS_indication) (
		struct MLME_COMM_STATUS_indication_pset *params);
	int (*MLME_SYNC_LOSS_indication) (
		struct MLME_SYNC_LOSS_indication_pset *params);
	int (*HWME_WAKEUP_indication) (
		struct HWME_WAKEUP_indication_pset *params);
	int (*TDME_MESSAGE_indication) (
		const char *message,
		size_t      len);
	int (*TDME_RXPKT_indication) (
		struct TDME_RXPKT_indication_pset *params);
	int (*TDME_EDDET_indication) (
		struct TDME_EDDET_indication_pset *params);
	int (*TDME_ERROR_indication) (
		struct TDME_ERROR_indication_pset *params);
	int (*generic_dispatch) (
		const uint8_t *buf,
		size_t         len);
};





uint8_t MCPS_DATA_request(
	uint8_t          SrcAddrMode,
	uint8_t          DstAddrMode,
	uint16_t         DstPANId,
	union MacAddr   *pDstAddr,
	uint8_t          MsduLength,
	uint8_t         *pMsdu,
	uint8_t          MsduHandle,
	uint8_t          TxOptions,
	struct SecSpec  *pSecurity,
	void            *pDeviceRef
);

uint8_t MCPS_PURGE_request_sync(
	uint8_t     *MsduHandle,
	void        *pDeviceRef
);

uint8_t MLME_ASSOCIATE_request(
	uint8_t          LogicalChannel,
	uint8_t          DstAddrMode,
	uint16_t         DstPANId,
	union MacAddr   *pDstAddr,
	uint8_t          CapabilityInfo,
	struct SecSpec  *pSecurity,
	void            *pDeviceRef
);

uint8_t MLME_ASSOCIATE_response(
	uint8_t         *pDeviceAddress,
	uint16_t         AssocShortAddress,
	uint8_t          Status,
	struct SecSpec  *pSecurity,
	void            *pDeviceRef
);

uint8_t MLME_DISASSOCIATE_request(
	struct FullAddr    DevAddr,
	uint8_t            DisassociateReason,
	uint8_t            TxIndirect,
	struct SecSpec    *pSecurity,
	void              *pDeviceRef
);

uint8_t MLME_GET_request_sync(
	uint8_t      PIBAttribute,
	uint8_t      PIBAttributeIndex,
	uint8_t     *pPIBAttributeLength,
	void        *pPIBAttributeValue,
	void        *pDeviceRef
);

uint8_t MLME_ORPHAN_response(
	uint8_t          *pOrphanAddress,
	uint16_t          ShortAddress,
	uint8_t           AssociatedMember,
	struct SecSpec   *pSecurity,
	void             *pDeviceRef
);

uint8_t MLME_RESET_request_sync(uint8_t SetDefaultPIB, void *pDeviceRef);

uint8_t MLME_RX_ENABLE_request_sync(
	uint8_t      DeferPermit,
	uint32_t     RxOnTime,
	uint32_t     RxOnDuration,
	void        *pDeviceRef
);

uint8_t MLME_SCAN_request(
	uint8_t          ScanType,
	uint32_t         ScanChannels,
	uint8_t          ScanDuration,
	struct SecSpec  *pSecurity,
	void            *pDeviceRef
);

uint8_t MLME_SET_request_sync(
	uint8_t       PIBAttribute,
	uint8_t       PIBAttributeIndex,
	uint8_t       PIBAttributeLength,
	const void   *pPIBAttributeValue,
	void         *pDeviceRef
);

uint8_t MLME_START_request_sync(
	uint16_t          PANId,
	uint8_t           LogicalChannel,
	uint8_t           BeaconOrder,
	uint8_t           SuperframeOrder,
	uint8_t           PANCoordinator,
	uint8_t           BatteryLifeExtension,
	uint8_t           CoordRealignment,
	struct SecSpec   *pCoordRealignSecurity,
	struct SecSpec   *pBeaconSecurity,
	void             *pDeviceRef
);

uint8_t MLME_POLL_request_sync(
	struct FullAddr   CoordAddress,
	uint8_t           Interval[2],


	struct SecSpec   *pSecurity,
	void             *pDeviceRef
);





uint8_t HWME_SET_request_sync(
	uint8_t      HWAttribute,
	uint8_t      HWAttributeLength,
	uint8_t     *pHWAttributeValue,
	void        *pDeviceRef
);

uint8_t HWME_GET_request_sync(
	uint8_t      HWAttribute,
	uint8_t     *HWAttributeLength,
	uint8_t     *pHWAttributeValue,
	void        *pDeviceRef
);

uint8_t HWME_HAES_request_sync(
	uint8_t      HAESMode,
	uint8_t     *pHAESData,
	void        *pDeviceRef
);





uint8_t TDME_SETSFR_request_sync(
	uint8_t      SFRPage,
	uint8_t      SFRAddress,
	uint8_t      SFRValue,
	void         *pDeviceRef
);

uint8_t TDME_GETSFR_request_sync(
	uint8_t      SFRPage,
	uint8_t      SFRAddress,
	uint8_t     *SFRValue,
	void        *pDeviceRef
);

uint8_t TDME_TESTMODE_request_sync(
	uint8_t      TestMode,
	void        *pDeviceRef
);

uint8_t TDME_SET_request_sync(
	uint8_t      TestAttribute,
	uint8_t      TestAttributeLength,
	void        *pTestAttributeValue,
	void        *pDeviceRef
);

uint8_t TDME_TXPKT_request_sync(
	uint8_t      TestPacketDataType,
	uint8_t     *TestPacketSequenceNumber,
	uint8_t     *TestPacketLength,
	void        *pTestPacketData,
	void        *pDeviceRef
);

uint8_t TDME_LOTLK_request_sync(
	uint8_t     *TestChannel,
	uint8_t     *TestRxTxb,
	uint8_t     *TestLOFDACValue,
	uint8_t     *TestLOAMPValue,
	uint8_t     *TestLOTXCALValue,
	void        *pDeviceRef
);




uint8_t TDME_ChipInit(void *pDeviceRef);
uint8_t TDME_ChannelInit(uint8_t channel, void *pDeviceRef);
uint8_t TDME_CheckPIBAttribute(
	uint8_t      PIBAttribute,
	uint8_t      PIBAttributeLength,
	const void   *pPIBAttributeValue
);

uint8_t TDME_SetTxPower(uint8_t txp, void *pDeviceRef);
uint8_t TDME_GetTxPower(uint8_t *txp, void *pDeviceRef);





void ca821x_register_callbacks(struct ca821x_api_callbacks *in_callbacks);
int ca821x_downstream_dispatch(const uint8_t *buf, size_t len);




extern int (*ca821x_api_downstream)(
	const uint8_t *buf,
	size_t len,
	uint8_t *response,
	void *pDeviceRef
);




extern uint8_t MAC_Workarounds;
extern uint8_t MAC_MPW;
#line 9 "mac_ca821x.h"
#line 1 "ca821x_irq.h"
#line 6 "ca821x_irq.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"



typedef char _Bool;
#line 7 "ca821x_irq.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 8 "ca821x_irq.h"
#line 15 "ca821x_irq.h"
void ca821x_irq_init();
#line 23 "ca821x_irq.h"
_Bool  ca821x_irq_is_pending();
#line 31 "ca821x_irq.h"
void ca821x_irq_signal();
#line 39 "ca821x_irq.h"
uint8_t ca821x_irq_wait(uint16_t timeout_ms);
#line 47 "ca821x_irq.h"
void ca821x_irq_enable();
#line 55 "ca821x_irq.h"
void ca821x_irq_disable();
#line 10 "mac_ca821x.h"
#line 1 "ca821x_spi.h"
#line 5 "ca821x_spi.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 6 "ca821x_spi.h"

typedef unsigned long (*spi_transfer_t)(unsigned long buffer);








typedef struct MAC_Message MAC_Message_t;
typedef union MacAddr MacAddr_t;
#line 30 "ca821x_spi.h"
void ca821x_spi_init(spi_transfer_t spi_transfer);
#line 39 "ca821x_spi.h"
uint8_t ca821x_spi_receive(uint8_t *buf);
#line 11 "mac_ca821x.h"
#line 23 "mac_ca821x.h"
uint8_t mac_init();
#line 32 "mac_ca821x.h"
uint8_t mac_reset();
#line 43 "mac_ca821x.h"
uint8_t mac_send(
    uint8_t *lladdr_dst,
    uint8_t *msdu,
    uint16_t msdu_length
);
#line 58 "mac_ca821x.h"
 uint8_t mac_process();
#line 69 "mac_ca821x.h"
uint8_t mac_get_addr(uint8_t *addr);
#line 80 "mac_ca821x.h"
uint8_t mac_set_addr(uint8_t *addr);
#line 2 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 3 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 1 "ca821x_spi.h"
#line 4 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 1 "ca821x_bsp.h"
#line 4 "ca821x_bsp.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"
#line 5 "ca821x_bsp.h"
#line 12 "ca821x_bsp.h"
void ca821x_bsp_reset_low();
#line 21 "ca821x_bsp.h"
void ca821x_bsp_reset_high();
#line 30 "ca821x_bsp.h"
void ca821x_bsp_cs_low();
#line 39 "ca821x_bsp.h"
void ca821x_bsp_cs_high();
#line 48 "ca821x_bsp.h"
_Bool  ca821x_bsp_irq_sense();
#line 5 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 6 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
#line 1 "log.h"
#line 37 "log.h"
static char sep[] =
    "-------------------------------------------------------";
#line 7 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"

static uint8_t _msdu_handle;

void blink(int i);

extern sfr sbit MAC_CA821X_RST;
#line 20 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_init()
{
    _msdu_handle = 0;

    ca821x_bsp_cs_high();
    ca821x_bsp_reset_low();

    ca821x_spi_init(SPI2_Read);
    ca821x_irq_init();

    return mac_reset();
}
#line 36 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_reset()
{
    _Bool  is_timeout;
    MAC_Message_t mac_message;
    uint8_t status;
    uint8_t chipid[2];
    uint8_t attlen;

    ca821x_bsp_reset_low();
    Delay_ms(10);
    ca821x_bsp_reset_high();

    is_timeout = ca821x_irq_wait( (uint16_t)(10) );
    if (is_timeout)
    {
        UART3_Write_Text( "ERROR: " ) ; UART3_Write_Text( "\x09" ) ; ; UART3_Write_Text( "CA-821X connection timed out, check hardware." ) ; UART3_Write_Text( "\r\n" ) ; ; ;
        return 1;
    }

    status = ca821x_spi_receive((uint8_t*)&mac_message);

    if (mac_message.CommandId !=  ( (0x15) + (0x20) ) )
    {
        UART3_Write_Text( "ERROR: " ) ; UART3_Write_Text( "\x09" ) ; ; UART3_Write_Text( "Instead of wakeup indication, check status." ) ; UART3_Write_Text( "\r\n" ) ; ; ;
        return 1;
    }

    if (mac_message.PData.HWMEWakeupInd.WakeUpCondition !=  (0x00) )
    {
        UART3_Write_Text( "ERROR: " ) ; UART3_Write_Text( "\x09" ) ; ; UART3_Write_Text( "CA-821X wakeup condition not power-up, check status" ) ; UART3_Write_Text( "\r\n" ) ; ; ;
        return 1;
    }


    if(TDME_ChipInit( ((void *)0) ))
    {
        UART3_Write_Text( "ERROR: " ) ; UART3_Write_Text( "\x09" ) ; ; UART3_Write_Text( "CA-821X initialisation failed" ) ; UART3_Write_Text( "\r\n" ) ; ; ;
        return 1;
    }

    if(HWME_GET_request_sync( (0x01) , &attlen, chipid, ((void *)0) ))
    {
        UART3_Write_Text( "ERROR: " ) ; UART3_Write_Text( "\x09" ) ; ; UART3_Write_Text( "ID Failed" ) ; UART3_Write_Text( "\r\n" ) ; ; ;
    }
    else
    {
        status = 0;

        if((chipid[0] == 1) && (chipid[1] == 1))
            MAC_Workarounds = 1;
        else
            MAC_Workarounds = 0;

        if(chipid[0] == 0)
            MAC_MPW = 1;
        else
            MAC_MPW = 0;
    }

    return status;
}
#line 101 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_send(
    uint8_t *lladdr_dst,
    uint8_t *msdu,
    uint16_t msdu_length
)
{
    MacAddr_t dst_addr;
    uint8_t status;

    memcpy(&dst_addr.IEEEAddress[0], lladdr_dst, 8);

    status = MCPS_DATA_request(
        ((unsigned)0x03) ,
        ((unsigned)0x03) ,
        0xffff,
        &dst_addr,
        msdu_length,
        msdu,
        _msdu_handle++,
        0x00,
        ((void *)0) ,
        ((void *)0)
    );

    return status;
}
#line 130 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_process()
{
    MAC_Message_t mac_message;

    if (ca821x_irq_is_pending())
    {
        ca821x_spi_receive((uint8_t*)&mac_message);

        ca821x_downstream_dispatch(
            (uint8_t*)&mac_message,
            mac_message.Length + 2
        );

        mac_reset();
    }

    return 0;
}
#line 152 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_set_addr(uint8_t *addr)
{
    uint8_t status;

    status = MLME_SET_request_sync(
        (0xFF) ,
        0,
        8,
        (void*)addr,
        ((void *)0)
    );

    return status;
}
#line 170 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy Backup/mac_ca821x.c"
uint8_t mac_get_addr(uint8_t *addr)
{
    uint8_t status;
    uint8_t pib_length;
    uint8_t pib_value[16];

    status = MLME_GET_request_sync(
        (0xFF) ,
        0,
        &pib_length,
        (uint8_t*)pib_value,
        ((void *)0)
    );

    memcpy(addr, pib_value, pib_length);

    return status;
}
