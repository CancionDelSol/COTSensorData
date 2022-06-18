package interfaces;

import interfaces.callbacks.IErrorCallback;

public interface IConfigurable {
    //region Properties
    boolean getIsConfigured();
    //endregion

    //region Methods
    boolean LoadConfiguration(String configPath, IErrorCallback onError);
    boolean SaveConfiguration(String configPath, IErrorCallback onError);
    String GetSetting(String name, IErrorCallback onError);
    void SetSetting(String name, String value, IErrorCallback onError);
    //endregion
}
