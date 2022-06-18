package implem.protocols;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

public class DummyCommProto implements ICommProto {

    //region Properties
    private String _stubName = "DummyCommProto";
    @Override
    public boolean getIsConnected() {
        return true;
    }

    @Override
    public String getName() {
        return _stubName;
    }
    //endregion

    //region Methods
    public DummyCommProto(String stubName) {
        if (stubName != null & !stubName.equals(""))
            _stubName = stubName;
    }


    @Override
    public boolean RoundTripMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }


    @Override
    public boolean ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }
    //endregion
    
}
