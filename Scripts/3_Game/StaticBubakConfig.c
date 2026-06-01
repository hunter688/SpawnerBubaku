class BubakSpawnObject
{
	string name;
	ref TStringArray objects;
	int number;
	ref TStringArray pos;
	
	void BubakSpawnObject(string nam, TStringArray ob, int num, TStringArray po)
	{
		name = nam;
		objects = ob;
		number = num;
		pos = po;
	}
}


class StatBubConfig
{
	ref array< ref BubakSpawnObject > BubakObjectLocations;
	
	void StatBubConfig()
	{
		BubakObjectLocations = new array< ref BubakSpawnObject >;	
	}

}

class StaticBubakConfig
{

    protected const static string m_ConfigRoot = "$profile:\\SpawnerBubaku\\";

    static void LoadConfig(string configName, out StatBubConfig configData)
    {
        string configPath = m_ConfigRoot + configName;
		
		if (!FileExist(configPath))
        {
            SPBLogger.GetInstance().Log("'" + configName + "' does not exist, creating default config", SPBLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
        JsonFileLoader<StatBubConfig>.JsonLoadFile(configPath, configData);

    }

    protected static void SaveConfig(string configName, StatBubConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<StatBubConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out StatBubConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            SPBLogger.GetInstance().Log("'"  + configName + "' does not exist, creating default config", SPBLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<StatBubConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...
			
        JsonFileLoader<StatBubConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out StatBubConfig configData)
    {
        configData = new StatBubConfig();
		configData.BubakObjectLocations.Insert( new BubakSpawnObject("Prison", {"ZmbF_BlueCollarFat_Blue"}, 2, {"2737 0 1602", "2376 0 1509", "3127 0 1200"} ));
		configData.BubakObjectLocations.Insert( new BubakSpawnObject("Skalisty", {"ZmbF_BlueCollarFat_Blue"}, 1, {"13200 0 3500"}));	
	}
}
