modded class MissionServer
{
	void MissionServer()
    {
		BuBuConfig config;
		BubakConfig.UpgradeConfig("SpawnerBubaku.json", config);
        GetDayZGame().SetBubakConfig(config);

		if (GetGame().IsServer()) 
        {
			SpawnerBubaku.ClearInstance();
			SpawnerBubaku.GetInstance();
        }
		
    }
};
