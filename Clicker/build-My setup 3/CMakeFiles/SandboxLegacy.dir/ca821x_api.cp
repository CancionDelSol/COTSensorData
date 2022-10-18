#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
#line 51 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
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
#line 52 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
#line 32 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 33 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
#line 60 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
const void * memchr( const void * ptr, char ch, unsigned int num );
#line 74 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
int memcmp( const void * str1, const void * str2, int num );
#line 88 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void * memcpy( void * dest_ptr, const void * src_ptr, int num );
#line 102 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void * memmove( void * dest_ptr, const void * src_ptr, int num );
#line 115 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void * memset( void * ptr, char chr, int num );
#line 130 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strcat( char * dest_ptr, const char * src_ptr );
#line 143 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
const char * strchr( const char * ptr, char chr );
#line 155 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
int strcmp( const char * str1, const char * str2 );
#line 167 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strcpy( char * dest_ptr, const char * src_ptr );
#line 177 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
int strlen( const char * str );
#line 191 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strncat( char * dest_ptr, const char * src_ptr, int size );
#line 204 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strncpy( char * dest_ptr, const char * src_ptr, int size );
#line 216 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
int strspn( const char * str1, const char * str2 );
#line 229 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char strcspn( const char * str1, const char * str2 );
#line 242 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
int strncmp( const char * str1, const char * str2, char len );
#line 255 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strpbrk( const char * str1, const char * str2 );
#line 269 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
const char * strrchr( const char * ptr, char chr );
#line 282 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strstr( const char * str1, const char * str2 );
#line 293 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
char * strtok( char * str1, char * str2 );
#line 302 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_cut_chr( char * str, char num );
#line 312 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_replace_chr( char * str, char chr_old, char chr_new );
#line 320 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_cut_left( char * str, int num );
#line 328 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_cut_right( char * str, int num );
#line 338 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_split( char * str1, char * str2, int num );
#line 347 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/string.h"
void str_insert_chr( char * str, char chr, int num );
#line 53 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdio.h"
#line 54 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
#line 55 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
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
#line 56 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
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
#line 57 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"

uint8_t MAC_Workarounds = 0;
uint8_t MAC_MPW         = 0;


static struct ca821x_api_callbacks callbacks;
#line 82 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
int (*ca821x_api_downstream)(
        const uint8_t *buf,
        size_t len,
        uint8_t *response,
        void *pDeviceRef
);
#line 107 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
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
)
{
        struct SecSpec *pSec;
        struct MAC_Message Command;

        Command.CommandId =  ( (0x00) ) ;
        (Command.PData.DataReq) .SrcAddrMode = SrcAddrMode;
        (Command.PData.DataReq) .Dst.AddressMode = DstAddrMode;
        if (DstAddrMode !=  ((unsigned)0x00) ) {
                (Command.PData.DataReq) .Dst.PANId[0] =  ((uint8_t)((DstPANId)&0xFF)) ;
                (Command.PData.DataReq) .Dst.PANId[1] =  ((uint8_t)(((DstPANId)>>8)&0xFF)) ;
                if (DstAddrMode ==  ((unsigned)0x02) ) {
                        (Command.PData.DataReq) .Dst.Address[0] =  ((uint8_t)((pDstAddr->ShortAddress)&0xFF)) ;
                        (Command.PData.DataReq) .Dst.Address[1] =  ((uint8_t)(((pDstAddr->ShortAddress)>>8)&0xFF)) ;
                } else {
                        memcpy( (Command.PData.DataReq) .Dst.Address, pDstAddr->IEEEAddress, 8);
                }
        }
        (Command.PData.DataReq) .MsduLength = MsduLength;
        (Command.PData.DataReq) .MsduHandle = MsduHandle;
        (Command.PData.DataReq) .TxOptions = TxOptions;
        memcpy( (Command.PData.DataReq) .Msdu, pMsdu, MsduLength);
        pSec = (struct SecSpec*)( (Command.PData.DataReq) .Msdu + MsduLength);
        Command.Length = sizeof(struct MCPS_DATA_request_pset) -  (114)  + MsduLength;
        if ( (pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0) ) {
                pSec->SecurityLevel = 0;
                Command.Length += 1;
        } else {
                *pSec = *pSecurity;
                Command.Length += sizeof(struct SecSpec);
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;

}
#line 167 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MCPS_PURGE_request_sync(
        uint8_t     *MsduHandle,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x01) + (0x40) ) ;
        Command.Length = 1;
        Command.PData.u8Param = *MsduHandle;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x02) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        *MsduHandle = Response.PData.PurgeCnf.MsduHandle;

        return Response.PData.PurgeCnf.Status;
}
#line 203 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_ASSOCIATE_request(
        uint8_t          LogicalChannel,
        uint8_t          DstAddrMode,
        uint16_t         DstPANId,
        union MacAddr   *pDstAddr,
        uint8_t          CapabilityInfo,
        struct SecSpec  *pSecurity,
        void            *pDeviceRef
)
{
        uint8_t status;
        struct MAC_Message Command;

        status = TDME_ChannelInit(LogicalChannel, pDeviceRef);
        if (status)
                return status;

        Command.CommandId =  ( (0x02) ) ;
        Command.Length = sizeof(struct MLME_ASSOCIATE_request_pset);
        (Command.PData.AssocReq) .LogicalChannel = LogicalChannel;
        (Command.PData.AssocReq) .Dst.AddressMode = DstAddrMode;
        (Command.PData.AssocReq) .Dst.PANId[0] =  ((uint8_t)((DstPANId)&0xFF)) ;
        (Command.PData.AssocReq) .Dst.PANId[1] =  ((uint8_t)(((DstPANId)>>8)&0xFF)) ;
        switch (DstAddrMode) {
        case  ((unsigned)0x02) :
                (Command.PData.AssocReq) .Dst.Address[0] =  ((uint8_t)((pDstAddr->ShortAddress)&0xFF)) ;
                (Command.PData.AssocReq) .Dst.Address[1] =  ((uint8_t)(((pDstAddr->ShortAddress)>>8)&0xFF)) ;
                break;
        case  ((unsigned)0x03) :
                memcpy( (Command.PData.AssocReq) .Dst.Address, pDstAddr->IEEEAddress, 8);
                break;
        default:
                memset( (Command.PData.AssocReq) .Dst.Address, 0 , 8);
                break;
        }
        (Command.PData.AssocReq) .CapabilityInfo = CapabilityInfo;
        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                (Command.PData.AssocReq) .Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                (Command.PData.AssocReq) .Security = *pSecurity;
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;

}
#line 266 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_ASSOCIATE_response(
        uint8_t         *pDeviceAddress,
        uint16_t         AssocShortAddress,
        uint8_t          Status,
        struct SecSpec  *pSecurity,
        void            *pDeviceRef
)
{
        struct MAC_Message Command;
        Command.CommandId =  ( (0x03) ) ;
        Command.Length = sizeof(struct MLME_ASSOCIATE_response_pset);

        memcpy( (Command.PData.AssocRsp) .DeviceAddress, pDeviceAddress, 8 );
        (Command.PData.AssocRsp) .AssocShortAddress[0] =  ((uint8_t)((AssocShortAddress)&0xFF)) ;
        (Command.PData.AssocRsp) .AssocShortAddress[1] =  ((uint8_t)(((AssocShortAddress)>>8)&0xFF)) ;
        (Command.PData.AssocRsp) .Status = Status;
        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                (Command.PData.AssocRsp) .Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                (Command.PData.AssocRsp) .Security = *pSecurity;
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;

}
#line 309 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_DISASSOCIATE_request(
        struct FullAddr    DevAddr,
        uint8_t            DisassociateReason,
        uint8_t            TxIndirect,
        struct SecSpec    *pSecurity,
        void              *pDeviceRef
)
{
        struct MAC_Message Command;
        Command.CommandId =  ( (0x04) ) ;
        Command.Length = sizeof(struct MLME_DISASSOCIATE_request_pset);

        Command.PData.DisassocReq.DevAddr = DevAddr;
        Command.PData.DisassocReq.DisassociateReason = DisassociateReason;
        Command.PData.DisassocReq.TxIndirect = TxIndirect;

        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                Command.PData.DisassocReq.Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                Command.PData.DisassocReq.Security = *pSecurity;
        }

        if(ca821x_api_downstream(&Command.CommandId, Command.Length + 2,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;
}
#line 351 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_GET_request_sync(
        uint8_t      PIBAttribute,
        uint8_t      PIBAttributeIndex,
        uint8_t     *pPIBAttributeLength,
        void        *pPIBAttributeValue,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;


        if (PIBAttribute ==  (0x02) ) {
                (Response.PData.GetCnf) .Status = TDME_GetTxPower(((uint8_t*)pPIBAttributeValue), pDeviceRef);
                *pPIBAttributeLength = 1;
        } else {
                Command.CommandId =  ( (0x05) + (0x40) ) ;
                Command.Length = sizeof(struct MLME_GET_request_pset);
                (Command.PData.GetReq) .PIBAttribute = PIBAttribute;
                (Command.PData.GetReq) .PIBAttributeIndex = PIBAttributeIndex;

                if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                        return  (0xFF) ;

                if (Response.CommandId !=  ( (0x08) + (0x20) + (0x40) ) )
                        return  (0xFF) ;

                if ( (Response.PData.GetCnf) .Status ==  (0x00) ) {
                        *pPIBAttributeLength =  (Response.PData.GetCnf) .PIBAttributeLength;
                        memcpy(pPIBAttributeValue,  (Response.PData.GetCnf) .PIBAttributeValue,  (Response.PData.GetCnf) .PIBAttributeLength);
                }
        }

        return  (Response.PData.GetCnf) .Status;


}
#line 401 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_ORPHAN_response(
        uint8_t          *pOrphanAddress,
        uint16_t          ShortAddress,
        uint8_t           AssociatedMember,
        struct SecSpec   *pSecurity,
        void             *pDeviceRef
)
{
        struct MAC_Message Command;

        Command.CommandId =  ( (0x06) ) ;
        Command.Length = sizeof(struct MLME_ORPHAN_response_pset);
        memcpy( (Command.PData.OrphanRsp) .OrphanAddress, pOrphanAddress, 8 );
        (Command.PData.OrphanRsp) .ShortAddress[0] =  ((uint8_t)((ShortAddress)&0xFF)) ;
        (Command.PData.OrphanRsp) .ShortAddress[1] =  ((uint8_t)(((ShortAddress)>>8)&0xFF)) ;
        (Command.PData.OrphanRsp) .AssociatedMember = AssociatedMember;
        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                (Command.PData.OrphanRsp) .Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                (Command.PData.OrphanRsp) .Security = *pSecurity;
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;

}
#line 441 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_RESET_request_sync(uint8_t SetDefaultPIB, void *pDeviceRef)
{
        uint8_t status;
        struct MAC_Message Command, Response;


        Command.CommandId =  ( (0x07) + (0x40) ) ;
        Command.Length = 1;
        (Command.PData) .u8Param = SetDefaultPIB;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x0A) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        status =  (Response.PData) .Status;


        if (MAC_Workarounds && SetDefaultPIB && (!status))
                status = TDME_SETSFR_request_sync(0, 0xD8, 0, pDeviceRef);

        return status;


}
#line 480 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_RX_ENABLE_request_sync(
        uint8_t      DeferPermit,
        uint32_t     RxOnTime,
        uint32_t     RxOnDuration,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x08) + (0x40) ) ;
        Command.Length = sizeof(struct MLME_RX_ENABLE_request_pset);;

        Command.PData.RxEnableReq.DeferPermit     = DeferPermit;
        Command.PData.RxEnableReq.RxOnTime[0]     =  ((uint8_t)((RxOnTime)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnTime[1]     =  ((uint8_t)(((RxOnTime)>>8)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnTime[2]     =  ((uint8_t)(((RxOnTime)>>16)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnTime[3]     =  ((uint8_t)(((RxOnTime)>>24)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnDuration[0] =  ((uint8_t)((RxOnDuration)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnDuration[1] =  ((uint8_t)(((RxOnDuration)>>8)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnDuration[2] =  ((uint8_t)(((RxOnDuration)>>16)&0xFF)) ;
        Command.PData.RxEnableReq.RxOnDuration[3] =  ((uint8_t)(((RxOnDuration)>>24)&0xFF)) ;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x0B) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.Status;
}
#line 523 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_SCAN_request(
        uint8_t          ScanType,
        uint32_t         ScanChannels,
        uint8_t          ScanDuration,
        struct SecSpec  *pSecurity,
        void            *pDeviceRef
)
{
        struct MAC_Message Command;

        Command.CommandId =  ( (0x09) ) ;
        Command.Length = sizeof(struct MLME_SCAN_request_pset);
        (Command.PData.ScanReq) .ScanType = ScanType;
        (Command.PData.ScanReq) .ScanChannels[0] =  ((uint8_t)((ScanChannels)&0xFF)) ;
        (Command.PData.ScanReq) .ScanChannels[1] =  ((uint8_t)(((ScanChannels)>>8)&0xFF)) ;
        (Command.PData.ScanReq) .ScanChannels[2] =  ((uint8_t)(((ScanChannels)>>16)&0xFF)) ;
        (Command.PData.ScanReq) .ScanChannels[3] =  ((uint8_t)(((ScanChannels)>>24)&0xFF)) ;
        (Command.PData.ScanReq) .ScanDuration = ScanDuration;
        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                (Command.PData.ScanReq) .Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                (Command.PData.ScanReq) .Security = *pSecurity;
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2,  ((void *)0) , pDeviceRef))
                return  (0xFF) ;

        return  (0x00) ;

}
#line 568 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_SET_request_sync(
        uint8_t       PIBAttribute,
        uint8_t       PIBAttributeIndex,
        uint8_t       PIBAttributeLength,
        const void   *pPIBAttributeValue,
        void         *pDeviceRef
)
{
        uint8_t status;
        struct MAC_Message Command, Response;



        if (TDME_CheckPIBAttribute(PIBAttribute, PIBAttributeLength, pPIBAttributeValue))
                return  (0xE8) ;

        if (PIBAttribute ==  (0x00) ) {
                status = TDME_ChannelInit(*((uint8_t*)pPIBAttributeValue), pDeviceRef);
                if (status) {
                        return status;
                }
        }

        if (PIBAttribute ==  (0x02) )
                return(TDME_SetTxPower(*((uint8_t*)pPIBAttributeValue), pDeviceRef));

        Command.CommandId =  ( (0x0A) + (0x40) ) ;
        Command.Length = sizeof(struct MLME_SET_request_pset) -  (250)  + PIBAttributeLength;
        (Command.PData.SetReq) .PIBAttribute = PIBAttribute;
        (Command.PData.SetReq) .PIBAttributeIndex = PIBAttributeIndex;
        (Command.PData.SetReq) .PIBAttributeLength = PIBAttributeLength;
        memcpy(  (Command.PData.SetReq) .PIBAttributeValue, pPIBAttributeValue, PIBAttributeLength );

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x0E) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return  (Response.PData) .Status;


}
#line 632 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
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
)
{
        uint8_t status;
        struct SecSpec *pBS;
        struct MAC_Message Command, Response;


        status = TDME_ChannelInit(LogicalChannel, pDeviceRef);
        if (status)
                return status;

        Command.CommandId =  ( (0x0B) + (0x40) ) ;
        Command.Length = sizeof(struct MLME_START_request_pset);
        (Command.PData.StartReq) .PANId[0] =  ((uint8_t)((PANId)&0xFF)) ;
        (Command.PData.StartReq) .PANId[1] =  ((uint8_t)(((PANId)>>8)&0xFF)) ;
        (Command.PData.StartReq) .LogicalChannel = LogicalChannel;
        (Command.PData.StartReq) .BeaconOrder = BeaconOrder;
        (Command.PData.StartReq) .SuperframeOrder = SuperframeOrder;
        (Command.PData.StartReq) .PANCoordinator = PANCoordinator;
        (Command.PData.StartReq) .BatteryLifeExtension = BatteryLifeExtension;
        (Command.PData.StartReq) .CoordRealignment = CoordRealignment;
        if ((pCoordRealignSecurity ==  ((void *)0) ) || (pCoordRealignSecurity->SecurityLevel == 0)) {
                (Command.PData.StartReq) .CoordRealignSecurity.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
                pBS = (struct SecSpec*)(& (Command.PData.StartReq) .CoordRealignSecurity.SecurityLevel + 1);
        } else {
                (Command.PData.StartReq) .CoordRealignSecurity = *pCoordRealignSecurity;
                pBS = & (Command.PData.StartReq) .BeaconSecurity;
        } if ((pBeaconSecurity ==  ((void *)0) ) || (pBeaconSecurity->SecurityLevel == 0)) {
                pBS->SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                *pBS = *pBeaconSecurity;
        }

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x0F) + (0x20) + (0x40) )  )
                return  (0xFF) ;

        return Response.PData.Status;

}
#line 700 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t MLME_POLL_request_sync(
        struct FullAddr   CoordAddress,
        uint8_t           Interval[2],


        struct SecSpec   *pSecurity,
        void             *pDeviceRef
)
{
        struct MAC_Message Command, Response;

        Command.CommandId =  ( (0x0D) + (0x40) ) ;
        Command.Length = sizeof(struct MLME_POLL_request_pset);
        (Command.PData.PollReq) .CoordAddress = CoordAddress;
        (Command.PData.PollReq) .Interval[0] = Interval[0];
        (Command.PData.PollReq) .Interval[1] = Interval[1];
        if ((pSecurity ==  ((void *)0) ) || (pSecurity->SecurityLevel == 0)) {
                (Command.PData.PollReq) .Security.SecurityLevel = 0;
                Command.Length -= sizeof(struct SecSpec) - 1;
        } else {
                (Command.PData.PollReq) .Security = *pSecurity;
        }

        if(ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x11) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.Status;

}
#line 745 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t HWME_SET_request_sync(
        uint8_t      HWAttribute,
        uint8_t      HWAttributeLength,
        uint8_t     *pHWAttributeValue,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x0E) + (0x40) ) ;
        Command.Length = 2 + HWAttributeLength;
        Command.PData.HWMESetReq.HWAttribute = HWAttribute;
        Command.PData.HWMESetReq.HWAttributeLength = HWAttributeLength;
        memcpy(Command.PData.HWMESetReq.HWAttributeValue, pHWAttributeValue, HWAttributeLength);

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x12) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.HWMESetCnf.Status;
}
#line 780 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t HWME_GET_request_sync(
        uint8_t      HWAttribute,
        uint8_t     *HWAttributeLength,
        uint8_t     *pHWAttributeValue,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x0F) + (0x40) ) ;
        Command.Length = 1;
        Command.PData.HWMEGetReq.HWAttribute = HWAttribute;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x13) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        if (Response.PData.HWMEGetCnf.Status ==  (0x00) ) {
                *HWAttributeLength = Response.PData.HWMEGetCnf.HWAttributeLength;
                memcpy(pHWAttributeValue, Response.PData.HWMEGetCnf.HWAttributeValue, *HWAttributeLength);
        }

        return Response.PData.HWMEGetCnf.Status;
}
#line 817 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t HWME_HAES_request_sync(
        uint8_t      HAESMode,
        uint8_t     *pHAESData,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x10) + (0x40) ) ;
        Command.Length = 17;
        Command.PData.HWMEHAESReq.HAESMode = HAESMode;
        memcpy(Command.PData.HWMEHAESReq.HAESData, pHAESData, 16);

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x14) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        if (Response.PData.HWMEHAESCnf.Status ==  (0x00) )
                memcpy(pHAESData, Response.PData.HWMEHAESCnf.HAESData, 16);

        return Response.PData.HWMEHAESCnf.Status;
}
#line 853 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_SETSFR_request_sync(
        uint8_t      SFRPage,
        uint8_t      SFRAddress,
        uint8_t      SFRValue,
        void         *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x11) + (0x40) ) ;
        Command.Length = 3;
        Command.PData.TDMESetSFRReq.SFRPage    = SFRPage;
        Command.PData.TDMESetSFRReq.SFRAddress = SFRAddress;
        Command.PData.TDMESetSFRReq.SFRValue   = SFRValue;
        Response.CommandId = 0xFF;
        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x17) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.TDMESetSFRCnf.Status;
}
#line 888 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_GETSFR_request_sync(
        uint8_t      SFRPage,
        uint8_t      SFRAddress,
        uint8_t     *SFRValue,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x12) + (0x40) ) ;
        Command.Length = 2;
        Command.PData.TDMEGetSFRReq.SFRPage = SFRPage;
        Command.PData.TDMEGetSFRReq.SFRAddress = SFRAddress;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x18) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        *SFRValue = Response.PData.TDMEGetSFRCnf.SFRValue;

        return Response.PData.TDMEGetSFRCnf.Status;
}
#line 922 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_TESTMODE_request_sync(
        uint8_t      TestMode,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x13) + (0x40) ) ;
        Command.Length = 1;
        Command.PData.TDMETestModeReq.TestMode = TestMode;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x19) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.TDMETestModeCnf.Status;
}
#line 953 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_SET_request_sync(
        uint8_t      TestAttribute,
        uint8_t      TestAttributeLength,
        void        *pTestAttributeValue,
        void        *pDeviceRef
)
{
        uint8_t status;
        struct MAC_Message Command, Response;
        if (TestAttribute ==  (0x00) ) {
                status = TDME_ChannelInit(*((uint8_t*)pTestAttributeValue), pDeviceRef);
                if(status)
                        return status;
        }

        Command.CommandId =  ( (0x14) + (0x40) ) ;
        Command.Length = 2 + TestAttributeLength;
        Command.PData.TDMESetReq.TDAttribute = TestAttribute;
        Command.PData.TDMESetReq.TDAttributeLength = TestAttributeLength;
        memcpy(Command.PData.TDMESetReq.TDAttributeValue, pTestAttributeValue, TestAttributeLength);

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x1A) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        return Response.PData.TDMESetCnf.Status;
}
#line 996 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_TXPKT_request_sync(
        uint8_t      TestPacketDataType,
        uint8_t     *TestPacketSequenceNumber,
        uint8_t     *TestPacketLength,
        void        *pTestPacketData,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x15) + (0x40) ) ;
        if (TestPacketDataType ==  (0x03) ) {
                Command.Length = 3 + *TestPacketLength;
        } else {
                Command.Length = 3;
        }

        Command.PData.TDMETxPktReq.TestPacketDataType       = TestPacketDataType;
        Command.PData.TDMETxPktReq.TestPacketSequenceNumber = *TestPacketSequenceNumber;
        Command.PData.TDMETxPktReq.TestPacketLength         = *TestPacketLength;

        if (TestPacketDataType ==  (0x03) )
                memcpy(Command.PData.TDMETxPktReq.TestPacketData, pTestPacketData, *TestPacketLength);

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x1B) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        if (Response.PData.TDMETxPktCnf.Status ==  (0x00) ) {
                *TestPacketLength = Response.PData.TDMETxPktCnf.TestPacketLength;
                *TestPacketSequenceNumber = Response.PData.TDMETxPktCnf.TestPacketSequenceNumber;
                memcpy(pTestPacketData, Response.PData.TDMETxPktCnf.TestPacketData, *TestPacketLength);
        }

        return Response.PData.TDMETxPktCnf.Status;
}
#line 1048 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_LOTLK_request_sync(
        uint8_t     *TestChannel,
        uint8_t     *TestRxTxb,
        uint8_t     *TestLOFDACValue,
        uint8_t     *TestLOAMPValue,
        uint8_t     *TestLOTXCALValue,
        void        *pDeviceRef
)
{
        struct MAC_Message Command, Response;
        Command.CommandId =  ( (0x16) + (0x40) ) ;
        Command.Length = 2;
        Command.PData.TDMELOTlkReq.TestChannel = *TestChannel;
        Command.PData.TDMELOTlkReq.TestRxTxb = *TestRxTxb;

        if (ca821x_api_downstream(&Command.CommandId, Command.Length + 2, &Response.CommandId, pDeviceRef))
                return  (0xFF) ;

        if (Response.CommandId !=  ( (0x1F) + (0x20) + (0x40) ) )
                return  (0xFF) ;

        if (Response.PData.TDMELOTlkCnf.Status ==  (0x00) ) {
                *TestChannel = Response.PData.TDMELOTlkCnf.TestChannel;
                *TestRxTxb = Response.PData.TDMELOTlkCnf.TestRxTxb;
                *TestLOFDACValue = Response.PData.TDMELOTlkCnf.TestLOFDACValue;
                *TestLOAMPValue = Response.PData.TDMELOTlkCnf.TestLOAMPValue;
                *TestLOTXCALValue = Response.PData.TDMELOTlkCnf.TestLOTXCALValue;
        }

        return Response.PData.TDMELOTlkCnf.Status;
}
#line 1089 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_ChipInit(void *pDeviceRef)
{
        uint8_t status;

        if((status = TDME_SETSFR_request_sync(1, 0xE1, 0x29, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE2, 0x54, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE3, 0x6C, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE4, 0x7A, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE5, 0x84, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE6, 0x8B, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE7, 0x92, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xE9, 0x96, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xD3, 0x5B, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(1, 0xD1, 0x5A, pDeviceRef)))
                return(status);
        if((status = TDME_SETSFR_request_sync(0, 0xFE, 0x3F, pDeviceRef)))
                return(status);

        return  (0x00) ;
}
#line 1129 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_ChannelInit(uint8_t channel, void *pDeviceRef)
{
        uint8_t txcalval;

        if (       channel >= 25) {
                txcalval = 0xA7;
        } else if (channel >= 23) {
                txcalval = 0xA8;
        } else if (channel >= 22) {
                txcalval = 0xA9;
        } else if (channel >= 20) {
                txcalval = 0xAA;
        } else if (channel >= 17) {
                txcalval = 0xAB;
        } else if (channel >= 16) {
                txcalval = 0xAC;
        } else if (channel >= 14) {
                txcalval = 0xAD;
        } else if (channel >= 12) {
                txcalval = 0xAE;
        } else {
                txcalval = 0xAF;
        }

        return TDME_SETSFR_request_sync(1, 0xBF, txcalval, pDeviceRef);
}
#line 1167 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_CheckPIBAttribute(
        uint8_t      PIBAttribute,
        uint8_t      PIBAttributeLength,
        const void   *pPIBAttributeValue
)
{
        uint8_t status =  (0x00) ;
        uint8_t value;

        value  = *((uint8_t*)pPIBAttributeValue);

        switch (PIBAttribute) {

        case  (0x02) :
                if (value > 0x3F)
                        status =  (0xE8) ;
                break;
        case  (0x03) :
                if (value > 0x03)
                        status =  (0xE8) ;
                break;

        case  (0x44) :
                if ((value < 6) || (value > 41))
                        status =  (0xE8) ;
                break;
        case  (0x45) :
                if (PIBAttributeLength >  ( (127) - (75) ) )
                        status =  (0xE8) ;
                break;
        case  (0x46) :
                if (value >  ( (127) - (75) ) )
                        status =  (0xE8) ;
                break;
        case  (0x47) :
                if (value > 15)
                        status =  (0xE8) ;
                break;
        case  (0x57) :
                if ((value < 3) || (value > 8))
                        status =  (0xE8) ;
                break;
        case  (0x4e) :
                if (value > 5)
                        status =  (0xE8) ;
                break;
        case  (0x59) :
                if (value > 7)
                        status =  (0xE8) ;
                break;
        case  (0x4f) :
                if (value > 8)
                        status =  (0xE8) ;
                break;
        case  (0x5A) :
                if ((value < 2) || (value > 64))
                        status =  (0xE8) ;
                break;
        case  (0x54) :
                if (value > 15)
                        status =  (0xE8) ;
                break;

        case  (0x56) :
        case  (0x41) :
        case  (0x42) :
        case  (0x43) :
        case  (0x4d) :
        case  (0x51) :
        case  (0x52) :
        case  (0x5D) :
                if (value > 1)
                        status =  (0xE8) ;
                break;

        case  (0x78) :
                if (value > 7)
                        status =  (0xE8) ;
                break;
        case  (0x79) :
                if (value > 3)
                        status =  (0xE8) ;
                break;
        default:
                break;
        }

        return status;
}
#line 1271 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_SetTxPower(uint8_t txp, void *pDeviceRef)
{
        uint8_t status;
        int8_t txp_val;
        uint8_t txp_ext;
        uint8_t paib;


        txp_ext = 0x3F & txp;
        if (txp_ext & 0x20)
                txp_ext += 0xC0;
        txp_val = (int8_t)txp_ext;

        if (MAC_MPW) {
                if (txp_val > 0) {
                        paib = 0xD3;
                } else {
                        paib = 0x73;
                }

                status = TDME_SETSFR_request_sync(0, 0xB1, paib, pDeviceRef);
        } else {

                if(       txp_val  >  8) {
                        paib = 0x3F;
                } else if(txp_val ==  8) {
                        paib = 0x32;
                } else if(txp_val ==  7) {
                        paib = 0x22;
                } else if(txp_val ==  6) {
                        paib = 0x18;
                } else if(txp_val ==  5) {
                        paib = 0x10;
                } else if(txp_val ==  4) {
                        paib = 0x0C;
                } else if(txp_val ==  3) {
                        paib = 0x08;
                } else if(txp_val ==  2) {
                        paib = 0x05;
                } else if(txp_val ==  1) {
                        paib = 0x03;
                } else if(txp_val ==  0) {
                        paib = 0x01;
                } else                     {
                        paib = 0x00;
                }

                status = TDME_SETSFR_request_sync(0, 0xFE, paib, pDeviceRef);
        }

        return status;
}
#line 1339 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
uint8_t TDME_GetTxPower(
        uint8_t *txp,
        void    *pDeviceRef
)
{
        uint8_t status;
        uint8_t paib;
        int8_t txp_val;

        if (MAC_MPW) {
                status = TDME_GETSFR_request_sync(0, 0xB1, &paib, pDeviceRef);

                if(paib & 0x80) {
                        txp_val =  4;
                } else {
                        txp_val = -6;
                }


                *txp = (uint8_t)(txp_val) & 0x3F;
                *txp += (0x01 << 6);
        } else {
                status = TDME_GETSFR_request_sync(0, 0xFE, &paib, pDeviceRef);

                if (     paib  >= 0x32)  txp_val =  8;
                else if (paib  >= 0x22)  txp_val =  7;
                else if (paib  >= 0x18)  txp_val =  6;
                else if (paib  >= 0x10)  txp_val =  5;
                else if (paib  >= 0x0C)  txp_val =  4;
                else if (paib  >= 0x08)  txp_val =  3;
                else if (paib  >= 0x05)  txp_val =  2;
                else if (paib  >= 0x03)  txp_val =  1;
                else if (paib  >  0x00)  txp_val =  0;
                else                     txp_val = -1;


                *txp = (uint8_t)(txp_val) & 0x3F;




        }

        return status;
}
#line 1392 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
void ca821x_register_callbacks(struct ca821x_api_callbacks *in_callbacks)
{
        memcpy(&callbacks, in_callbacks, sizeof(struct ca821x_api_callbacks));
}
#line 1408 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
int ca821x_downstream_dispatch(const uint8_t *buf, size_t len)
{
        int ret;


        switch (buf[0]) {
        case  ( (0x00) + (0x20) ) :
                if (callbacks.MCPS_DATA_indication) {
                        return callbacks.MCPS_DATA_indication(
                                (struct MCPS_DATA_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x01) + (0x20) ) :
                if (callbacks.MCPS_DATA_confirm) {
                        return callbacks.MCPS_DATA_confirm(
                                (struct MCPS_DATA_confirm_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x03) + (0x20) ) :
                if (callbacks.MLME_ASSOCIATE_indication) {
                        return callbacks.MLME_ASSOCIATE_indication(
                                (struct MLME_ASSOCIATE_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x04) + (0x20) ) :
                if (callbacks.MLME_ASSOCIATE_confirm) {
                        return callbacks.MLME_ASSOCIATE_confirm(
                                (struct MLME_ASSOCIATE_confirm_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x05) + (0x20) ) :
                if (callbacks.MLME_DISASSOCIATE_indication) {
                        return callbacks.MLME_DISASSOCIATE_indication(
                                (struct MLME_DISASSOCIATE_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x06) + (0x20) ) :
                if (callbacks.MLME_DISASSOCIATE_confirm) {
                        return callbacks.MLME_DISASSOCIATE_confirm(
                                (struct MLME_DISASSOCIATE_confirm_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x07) + (0x20) ) :
                if (callbacks.MLME_BEACON_NOTIFY_indication) {
                        return callbacks.MLME_BEACON_NOTIFY_indication(
                                (struct MLME_BEACON_NOTIFY_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x09) + (0x20) ) :
                if (callbacks.MLME_ORPHAN_indication) {
                        return callbacks.MLME_ORPHAN_indication(
                                (struct MLME_ORPHAN_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x0C) + (0x20) ) :
                if (callbacks.MLME_SCAN_confirm) {
                        return callbacks.MLME_SCAN_confirm(
                                (struct MLME_SCAN_confirm_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x0D) + (0x20) ) :
                if (callbacks.MLME_COMM_STATUS_indication) {
                        return callbacks.MLME_COMM_STATUS_indication(
                                (struct MLME_COMM_STATUS_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x10) + (0x20) ) :
                if (callbacks.MLME_SYNC_LOSS_indication) {
                        return callbacks.MLME_SYNC_LOSS_indication(
                                (struct MLME_SYNC_LOSS_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x15) + (0x20) ) :
                if (callbacks.HWME_WAKEUP_indication) {
                        return callbacks.HWME_WAKEUP_indication(
                                (struct HWME_WAKEUP_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x16) + (0x20) ) :
                if (callbacks.TDME_MESSAGE_indication) {
                        return callbacks.TDME_MESSAGE_indication(
                                (char *)(buf + 2),
                                len
                        );
                }
                break;
        case  ( (0x1C) + (0x20) ) :
                if (callbacks.TDME_RXPKT_indication) {
                        return callbacks.TDME_RXPKT_indication(
                                (struct TDME_RXPKT_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x1D) + (0x20) ) :
                if (callbacks.TDME_EDDET_indication) {
                        return callbacks.TDME_EDDET_indication(
                                (struct TDME_EDDET_indication_pset*)(buf + 2)
                        );
                }
                break;
        case  ( (0x1E) + (0x20) ) :
                if (callbacks.TDME_ERROR_indication) {
                        return callbacks.TDME_ERROR_indication(
                                (struct TDME_ERROR_indication_pset*)(buf + 2)
                        );
                }
                break;
        default:




                return  -1;

                break;
        }
#line 1539 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ca821x_api.c"
        if (callbacks.generic_dispatch) {
                ret = callbacks.generic_dispatch(buf, len);
                if (ret) {
                        return ret;
                }
        }

        return 0;
}
