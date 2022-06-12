package interfaces;

public interface IConfigurable {
    //region Properties
    boolean getIsConfigured();
    //endregion

    //region Methods
    void LoadConfiguration(String configPath);
    void SaveConfiguration(String configPath);
    Object GetSetting(String name);
    void SetSetting(String name, Object value);
    //endregion
}
