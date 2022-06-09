package implem;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

public class DummyCommProto implements ICommProto {

    private String _stubName = "DummyCommProto";
    @Override
    public boolean getIsConnected() {
        return true;
    }

    @Override
    public boolean RoundTripMessage(String message) {
        return true;
    }

    @Override
    public boolean EncryptedRoundTrip(String message, IEncryptionAlg encryptionAlg) {
        return false;
    }

    @Override
    public String getName() {
        return _stubName;
    }

    public DummyCommProto(String stubName) {
        if (stubName != null & !stubName.equals(""))
            _stubName = stubName;
    }
    
}
