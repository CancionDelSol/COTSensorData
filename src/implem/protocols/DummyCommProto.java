package implem.protocols;

import java.util.Random;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import util.CommonMath;
import util.ConfigurableBase;
import util.Logger;

public class DummyCommProto extends ConfigurableBase implements ICommProto {

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
        super(stubName + "Config.cfg");
        if (stubName != null & !stubName.equals(""))
            _stubName = stubName;
    }

    /**
     * Sleep for a short amount of time to simulate
     *  a round trip message
     */
    @Override
    public boolean RequestAndVerifySensorData(IEncryptionAlg encryptionAlg) {

        // Sleep for a random amount of time
        try {
            long sleepTime = CommonMath.Uniform(1L, 5000L);
            Thread.sleep(sleepTime);
            
        } catch (Exception exc) {
            Logger.Error("Can't sleep: " + exc.getMessage());
            return false;
        }
        
        // Randomly return failure
        //  5% of the time
        return true;
    }


    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // Fake failure
        return message;
    }
    //endregion
    
    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("TestSettingOne", "TestValueOne");
        SetSetting("TestSettingTwo", "TestValueTwo");
        SetSetting("TestSettingThree", "TestValueThree");
        SetSetting("TestSettingFour", "TestValueFour");
        SetSetting("TestSettingFive", "TestValueFive");
        SetSetting("TestSettingSix", "TestValueSix");
    }
    //endregion
}
