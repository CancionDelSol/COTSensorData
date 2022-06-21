package implem.protocols;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import util.ConfigurableBase;

public class WifiCommProtoProto extends ConfigurableBase implements ICommProto {
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
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO 
        return message;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("UseESP", "false");
        SetSetting("Timeout", "15000");
    }
    //endregion
}
