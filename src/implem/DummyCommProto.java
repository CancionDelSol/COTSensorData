package implem;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

public class DummyCommProto implements ICommProto {

    @Override
    public boolean getIsConnected() {
        // TODO Auto-generated method stub
        return true;
    }

    @Override
    public boolean RoundTripMessage(String message) {
        // TODO Auto-generated method stub
        return true;
    }

    @Override
    public boolean EncryptedRoundTrip(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public String getName() {
        // TODO Auto-generated method stub
        return null;
    }
    
}
