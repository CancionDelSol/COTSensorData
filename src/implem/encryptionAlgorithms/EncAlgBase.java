package implem.encryptionAlgorithms;

import java.util.Date;

import interfaces.IEncryptionAlg;

import util.Logger;


public abstract class EncAlgBase implements IEncryptionAlg {

    String _name = "INVALID";

    @Override
    public String Encrypt(String input) {
        String response = "";
        try {
            response = _encrypt(input);
        } catch (Exception exc) {
            Logger.Error("Exception during encryption: " + exc.getMessage());
        }
        return response;
    }

    @Override
    public String Decrypt(String input) {
        String response = "";
        try {
            response = _decrypt(input);
        } catch (Exception exc) {
            Logger.Error("Exception during decryption: " + exc.getMessage());
        }
        return response;
    }

    @Override
    public String getName() {
        return _name;
    }
    
    public EncAlgBase() {

    }
    protected EncAlgBase(String encName) {
        if (encName != null && !encName.equals(""))
            _name = encName;
    }

    protected abstract String _encrypt(String input);
    
    protected abstract String _decrypt(String input);
}
