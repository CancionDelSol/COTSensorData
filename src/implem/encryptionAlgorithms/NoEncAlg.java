package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;


public class NoEncAlg extends EncAlgBase {

    @Override
    protected String _encrypt(String input) {
        return input;
    }

    @Override
    protected String _decrypt(String input) {
        return input;
    }
    
    public NoEncAlg() {
        super("None");
    }
}
