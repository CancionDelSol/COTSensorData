package implem;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

public class WifiTransceiver implements ICommProto {
//region Fields

    //endregion

    //region Properties
    @Override
    public boolean getIsConnected() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public String getName() {
        return "WifiTranceiver";
    }
    //endregion

    //region Constructor
    
    //endregion

    //region Methods
    @Override
    public boolean RoundTripMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO 
        return false;
    }
    //endregion
}
