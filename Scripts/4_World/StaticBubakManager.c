class PluginStaticBubakManager extends PluginBase
{
	
	void PluginStaticBubakManager()
    {
		
		StatBubConfig statconfig;
		StaticBubakConfig.LoadConfig("StaticBubakSpawner.json", statconfig);
        GetDayZGame().SetStaticBubakConfig(statconfig);
		
		
		StatBubConfig config = GetDayZGame().GetStaticBubakConfig();
		SPBLogger.GetInstance().Log("Static Bubak Spawner running.", SPBLogger.LOGLEVEL_CRITICAL);
		for(int i = 0; i < config.BubakObjectLocations.Count(); i++)
		{
			TStringArray objects = config.BubakObjectLocations.Get(i).objects;
			TStringArray positions =  config.BubakObjectLocations.Get(i).pos;
			int objectsnum = config.BubakObjectLocations.Get(i).number;
			int rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
			
			if (objectsnum <= positions.Count())
			{
				for (int j = 0; j< objectsnum; j++)
				{
					//iteruj na lokacich
					string objectclass = objects.GetRandomElement();
					objectclass = objects.GetRandomElement();
					objectclass = objects.GetRandomElement();

					rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
					rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
					
					string posrot = positions.Get(rndnum);
					TStringArray loc = new TStringArray;
					posrot.Split( "|", loc );
					string pos = loc.Get(0);
					string rot = loc.Get(1);
					//add check for commas in pos!
					if (pos.Contains(","))
					{
						SPBLogger.GetInstance().Log("Position contains commas, thats wrong! Only one space between numbers! Fix yours config according example!!!", SPBLogger.LOGLEVEL_CRITICAL);
					}
					else {
						SpawnObject(objectclass, pos.ToVector(), rot.ToVector());
						SPBLogger.GetInstance().Log("Static Spawned " + objectclass, SPBLogger.LOGLEVEL_CRITICAL);
						positions.RemoveOrdered(rndnum);
					}
					
					
				}
				
			}
			
			/*
			for(int j = 0; j < config.SiSpObjectLocations.Get(i).pos.Count(); j++)
			{
				string posrot = config.SiSpObjectLocations.Get(i).pos.Get(j);
				TStringArray loc = new TStringArray;
				posrot.Split( "|", loc );
				string pos = loc.Get(0);
				string rot = loc.Get(1);
				
				///SpawnObject(config.SiSpObjectLocations.Get(i).name, pos.ToVector(), rot.ToVector());
				

				
			}
			*/
		}
		//SEffectManager.PlaySoundEnviroment("Prison_Ambient_SoundSet", "2772 30.05 1304.4".ToVector(), 0, 0, true);
		//GetGame().CreateObject("Static_stone11", "2823 26.305 1213.39");
	}
	
	void SpawnObject( string type, vector position, vector orientation )
	{
	    auto obj = GetGame().CreateObject( type, position, false, true, true );

	}
}