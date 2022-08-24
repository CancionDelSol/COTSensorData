package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;


public class ECCEncryptionAlg extends EncAlgBase {

    @Override
    protected String _encrypt(String input) {
        return input;
    }

    @Override
    protected String _decrypt(String input) {
        return input;
    }
    
    public ECCEncryptionAlg() {
        super("ECC");
    }
}
