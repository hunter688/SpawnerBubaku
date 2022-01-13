class BubakPlace
{
    string name;
	string triggerpos;
	string triggermins;
	string triggermaxs;
	float triggerradius;
	string notification;
	int notificationtime;
	int triggerdelay;
    ref TStringArray spawnerpos;
	int bubaknum;
	int onlyfilluptobubaknum;
	ref TStringArray bubaci;

    void BubakPlace(string nam, string trxz, string trmin, string trmax, float trrad, string notf, int notftim, int trd, TStringArray spawnpos, int bubn, int onlyfillup, TStringArray bub) 
	{
        name = nam;
		triggerpos = trxz;
		triggermins = trmin;
		triggermaxs = trmax;
		triggerradius = trrad;
		notification = notf;
		notificationtime = notftim;
		triggerdelay = trd;
		spawnerpos = spawnpos;
		bubaknum = bubn;
		onlyfilluptobubaknum = onlyfillup;
		bubaci = bub;
    }
}

class BuBuConfig
{
	int loglevel;
	ref array< ref BubakPlace > BubakLocations;
	
	void BuBuConfig()
	{
		loglevel = 0;
		BubakLocations = new ref array< ref BubakPlace >;
	}
}

class BubakConfig
{

    protected const static string m_ConfigRoot = "$profile:\\SpawnerBubaku\\";

    static void LoadConfig(string configName, out BuBuConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            SPBLogger.GetInstance().Log("'" + configName + "' does not exist, creating default config", SPBLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<BuBuConfig>.JsonLoadFile(configPath, configData);
        SPBLogger.GetInstance().Log("'" + configName + "' found, loading existing config", SPBLogger.LOGLEVEL_CRITICAL);
    }

    protected static void SaveConfig(string configName, BuBuConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            SPBLogger.GetInstance().Log("'" + m_ConfigRoot + "' does not exist, creating directory", SPBLogger.LOGLEVEL_CRITICAL);
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<BuBuConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out BuBuConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            SPBLogger.GetInstance().Log("'"  + configName + "' does not exist, creating default config", SPBLogger.LOGLEVEL_CRITICAL);
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<BuBuConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...

		if(!configData.loglevel) configData.loglevel = 0;

		for ( int i=0; i < configData.BubakLocations.Count(); i++)
		{
			if (!configData.BubakLocations.Get(i).notification)
			{
				configData.BubakLocations.Get(i).notification = "";
				configData.BubakLocations.Get(i).notificationtime = 2;
			}
			
			if (!configData.BubakLocations.Get(i).triggerradius)
			{
				configData.BubakLocations.Get(i).triggerradius = 0;
			}

			if (!configData.BubakLocations.Get(i).onlyfilluptobubaknum)
			{
				configData.BubakLocations.Get(i).onlyfilluptobubaknum = 0;
			}
		}
			
        JsonFileLoader<BuBuConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out BuBuConfig configData)
    {
        configData = new BuBuConfig();
		configData.BubakLocations.Insert( new BubakPlace("trigger1", "1683 457 14219", "-1 -0.2 -1", "1 1 1" ,0 ,"" , 2, 1800, {"1683 457 14219", "1684 457 14218"}, 4, 1, {"ZmbM_ClerkFat_White", "ZmbM_SoldierNormal"} ));
		configData.BubakLocations.Insert( new BubakPlace("trigger2", "1530 0 8", "-1 -0.2 -1", "1 1 1" ,0, "", 2, 3600, {"1358 500 25", "0 0 0"}, 20, 0, {"ZmbM_ClerkFat_White", "ZmbM_SoldierNormal"} ));
	}
}
