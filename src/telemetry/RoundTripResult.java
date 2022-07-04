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
 */
public class RoundTripResult {
    
    //region Fields
    private long _duration;
    private String _commProtoName;
    private String _encAlgName;
    private String _serverMessage;
    private String _clientResponse;
    //endregion

    //region Properties
    public long getDuration() { return _duration; }
    public String getCommProtoName() { return _commProtoName; }
    public String getEncAlgName() { return _encAlgName; }
    public String getServerMessage() { return _serverMessage; }
    public String getClientResponse() { return _clientResponse; }
    //endregion

    //region Constructor
    /**
     * Main constructor
     */
    public RoundTripResult(long duration,
                            ICommProto protocolUsed,
                            IEncryptionAlg encryptionAlgUsed,
                            String serverMessage,
                            String clientResponse) {
        _duration = duration;
        _commProtoName = protocolUsed.getName();
        _encAlgName = encryptionAlgUsed.getName();
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
            .append('\n');
        return bldr.toString();

    }
    //endregion
}
