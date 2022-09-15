package telemetry;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

/**
 * This class will store information
 *  about a round-trip communication
 *  attempt. This class should not
 *  be instantiated until a "trip"
 *  is fully completed. For use with
 *  report creation
 * 
 * Properties:
 *  - TotalDuration
 *  - ProcedureStartTimeStamp
 *  - RequestSentFromTransTimeStamp
 *  - RequestRecByRecTimeStamp
 *  - RespSentFrom
 RecTimeStamp
 *  - RespRecByTransTimeStamp
 */
public class RoundTripResult {
    
    //region Fields
    private long _duration;
    private long _procStartTimeStamp;
    private long _reqSentFromTransTimeStamp;
    private long _reqRecByRecTimeStamp;
    private long _respSentFromRecTimeStamp;
    private long _respRecByTransTimeStamp;
    private String _commProtoName;
    private String _encAlgName;
    private String _serverMessage;
    private String _status;
    //endregion

    //region Properties
    public long getDuration() { return _duration; }
    public String getCommProtoName() { return _commProtoName; }
    public String getEncAlgName() { return _encAlgName; }
    public String getServerMessage() { return _serverMessage; }
    public String getStatus() { return _status; }
    //endregion

    //region Constructor
    /**
     * Failure constructor
     */
    public RoundTripResult(ICommProto protocolUsed,
                            IEncryptionAlg encryptionAlgUsed,
                            String status) {
        this(0L, 0L, 0L, 0L, 0L,0L,
        protocolUsed,
        encryptionAlgUsed,
        status
        );
    }

    public RoundTripResult(long duration,
                            long procStartTimeStamp,
                            long reqSentFromTransTimeStamp,
                            long reqRecByRecTimeStamp,
                            long respSentFromRecTimeStamp,
                            long respRecByTransTimeStamp,
                            ICommProto protocolUsed,
                            IEncryptionAlg encryptionAlgUsed,
                            String status) {

        _duration = duration;
        _procStartTimeStamp = procStartTimeStamp;
        _reqSentFromTransTimeStamp = reqSentFromTransTimeStamp;
        _reqRecByRecTimeStamp = reqRecByRecTimeStamp;
        _respSentFromRecTimeStamp = respSentFromRecTimeStamp;
        _respRecByTransTimeStamp = respRecByTransTimeStamp;
        _commProtoName = protocolUsed.getName();
        _encAlgName = encryptionAlgUsed.getName();
        _status = status;
    }
    //endregion

    //region Object
    @Override
    public String toString() {
        StringBuilder bldr = new StringBuilder();
        bldr.append(" EncAlg: ")
            .append(_encAlgName)
            .append('\n')
            .append(" Duration: ")
            .append(_duration)
            .append('\n')
            .append(" Start: ")
            .append(_procStartTimeStamp)
            .append('\n')
            .append(" SentFromTrans: ")
            .append(_reqSentFromTransTimeStamp)
            .append('\n')
            .append(" RecByReceiver: ")
            .append(_reqRecByRecTimeStamp)
            .append('\n')
            .append(" RespSentByReceiver: ")
            .append(_respSentFromRecTimeStamp)
            .append('\n')
            .append(" RespRecByTransmitter: ")
            .append(_respRecByTransTimeStamp)
            .append('\n')
            .append(" Status: ")
            .append(_status)
            .append('\n');
        return bldr.toString();

    }

    public String asRow() {
        StringBuilder bldr = new StringBuilder();
        bldr.append(_duration)
            .append(",")
            .append(_procStartTimeStamp)
            .append(",")
            .append(_reqSentFromTransTimeStamp)
            .append(",")
            .append(_reqRecByRecTimeStamp)
            .append(",")
            .append(_respSentFromRecTimeStamp)
            .append(",")
            .append(_respRecByTransTimeStamp);
        
        return bldr.toString();
    }

    public static String getHeader() {
        StringBuilder bldr = new StringBuilder();

        bldr.append("Duration")
            .append(",")
            .append("ProcStartTime")
            .append(",")
            .append("ReqSentFromTrans")
            .append(",")
            .append("ReqRecByReceiv")
            .append(",")
            .append("RespSentByRec")
            .append(",")
            .append("RespRecByTrans");

        return bldr.toString();
    }
    //endregion
}
