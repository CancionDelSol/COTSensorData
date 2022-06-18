package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;

public class DummyEncAlg implements IEncryptionAlg {

    String _stubName = "DummyEncryptionAlgorithm";

    @Override
    public String Encrypt(String input) {
        return input + "|->Encrypted @ " + new Date();
    }

    @Override
    public String Decrypt(String input) {
        return input + "|->Decrypted @ " + new Date();
    }

    @Override
    public String getName() {
        return _stubName;
    }
    
    public DummyEncAlg(String stubName) {
        if (stubName != null && !stubName.equals("")) 
        _stubName = stubName;

    }
}
