package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;


public class DESEncryptionAlg extends EncAlgBase {

    @Override
    protected String _encrypt(String input) {
        return input;
    }

    @Override
    protected String _decrypt(String input) {
        return input;
    }
    
    public DESEncryptionAlg() {
        super("DES");
    }
}