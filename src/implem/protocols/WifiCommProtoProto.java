package implem.protocols;

import implem.ESPModule;
import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import util.ConfigurableBase;
import util.Globals;
import util.Logger;

public class WifiCommProtoProto extends ConfigurableBase implements ICommProto {
    //region Fields
    private static ESPModule _espModule = ESPModule.getModule();
    //endregion

    //region Properties
    @Override
    public boolean getIsConnected() {
        return _espModule != null;
    }

    @Override
    public String getName() {
        return "WifiTranceiver";
    }
    //endregion

    //region Constructor
    public WifiCommProtoProto() {
        super(Globals.WIFI_PROTO_CONFIG_FILE);
    }
    //endregion

    //region Methods
    @Override
    public boolean RequestAndVerifySensorData(IEncryptionAlg encryptionAlg) {
        if (_espModule == null) {
            Logger.Error("No module available");
            return false;
        }

        boolean success = true;

        try {
            String resp = ESPModule.SendMessage("DataRequest:" + encryptionAlg.getName(), true);
        } catch (Exception exc) {
            Logger.Error("Error requesting data: " + exc.getMessage());
            success = false;
        }

        return success;
    }

    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        
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
