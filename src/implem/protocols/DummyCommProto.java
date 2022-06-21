package implem.protocols;

import java.util.Random;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import util.CommonMath;
import util.ConfigurableBase;

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
        super(stubName + "Config");
        if (stubName != null & !stubName.equals(""))
            _stubName = stubName;
    }

    /**
     * Sleep for a short amount of time to simulate
     *  a round trip message
     */
    @Override
    public boolean RoundTripMessage(String message, IEncryptionAlg encryptionAlg) {

        // Sleep for a random amount of time
        try {
            Thread.sleep(CommonMath.Uniform(0L, 5000L));
        } catch (Exception exc) {
            return false;
        }
        
        // Randomly return failure
        //  5% of the time
        return CommonMath.Uniform(0, 100) > 5 ? true : false;
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
