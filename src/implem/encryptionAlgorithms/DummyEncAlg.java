package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;

public class DummyEncAlg extends EncAlgBase {

    @Override
    public String _encrypt(String input) {
        return input;
    }

    @Override
    public String _decrypt(String input) {
        return input;
    }
    
    public DummyEncAlg(String stubName) {
        super(stubName);
    }
}
