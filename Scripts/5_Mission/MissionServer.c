modded class MissionServer
{
	void MissionServer()
    {
		BuBuConfig config;
		FileAttr fileAttr;
		string fileName;
		TStringArray fajly;
		fajly = new TStringArray();
		FindFileHandle handle = FindFile("$profile:\\SpawnerBubaku\\SpawnerBubaku*.json", fileName, fileAttr, 0);
		fajly.Insert(fileName);
		//SPBLogger.GetInstance().Log("Filename " + fileName, SPBLogger.LOGLEVEL_CRITICAL);
		while ( FindNextFile(handle, fileName, fileAttr))
		{
			fajly.Insert(fileName);
			//SPBLogger.GetInstance().Log("Filename " + fileName, SPBLogger.LOGLEVEL_CRITICAL);
		}
		fileName = fajly.GetRandomElement();
		fileName = fajly.GetRandomElement();
		if (fajly.Count()>1)
		{
			SPBLogger.GetInstance().Log("Selected Filename " + fileName, SPBLogger.LOGLEVEL_CRITICAL);
		}
		
		BubakConfig.UpgradeConfig(fileName, config);
        GetDayZGame().SetBubakConfig(config);

		if (GetGame().IsServer()) 
        {
			SpawnerBubaku.ClearInstance();
			SpawnerBubaku.GetInstance();
        }
		
    }
};
