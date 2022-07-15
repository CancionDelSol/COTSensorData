package implem.protocols;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import telemetry.RoundTripResult;
import util.ConfigurableBase;
import util.Globals;

public class LoPanCommProto extends ConfigurableBase implements ICommProto {
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
        return "6LoWPAN";
    }
    //endregion

    //region Constructor
    public LoPanCommProto() {
        super(Globals.SIX_LOWPAN_PROTO_CONFIG_FILE);
    }
    //endregion

    //region Methods
    @Override
    public RoundTripResult RequestAndVerifySensorData(IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return new RoundTripResult(this, encryptionAlg, "Not Implemented");
    }

    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return message;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("Timeout", "15000");
    }
    //endregion
}
