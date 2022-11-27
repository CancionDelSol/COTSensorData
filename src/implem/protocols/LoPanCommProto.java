package implem.protocols;

import java.util.Date;

import implem.ESPAbridged;
import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import telemetry.RoundTripResult;
import util.ConfigurableBase;
import util.Globals;
import util.Logger;

public class LoPanCommProto extends ConfigurableBase implements ICommProto {
    //region Fields
    private static ESPAbridged _espModule = ESPAbridged.getModule();
    //endregion

    //region Properties
    @Override
    public boolean getIsConnected() {
        return _espModule != null;
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
        if (_espModule == null) {
            Logger.Error("No module available");
            return new RoundTripResult(this, encryptionAlg, "Failure, no active module");
        }

        long procStartTime = (new Date()).getTime();
        Logger.Debug("Procedure Start Time: " + procStartTime);

        RoundTripResult res = null;
        try {
            Logger.Debug("Sending request to ESP module");
            String resp = _espModule.DataRequest(encryptionAlg);

            res = new RoundTripResult((new Date()).getTime() - procStartTime,
                procStartTime,
                0, // Request sent by transmitter
                0, // Request received by the receiver
                0, // Response sent by receiver
                0, // Response received by transmitter
                this,
                encryptionAlg,
                "Success");
            
        } catch (Exception exc) {
            Logger.Error("Error requesting data: " + exc.getMessage());
            res = new RoundTripResult(this, encryptionAlg, "Failure, no active module");

        }

        return res;
    }

    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        return message;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("UseESP", "true");
        SetSetting("Timeout", "15000");
    }
    //endregion
}
