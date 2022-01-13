

class SpawnerBubaku
{

	protected static ref SpawnerBubaku Instance;
	protected ref map<int, ref TIntArray> spawned_instances;

	static SpawnerBubaku GetInstance()
	{
		if (!Instance)
        {
            Instance = new SpawnerBubaku();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
	void SpawnerBubaku()
    {
        
		SPBLogger.Log( "SpawnerBubaku started!" );

		spawned_instances = new map<int, ref TIntArray>;

		BuBuConfig config = GetDayZGame().GetBubakConfig();
		BubakTrigger trigger;
		vector mins, maxs;
		float radius;
		for ( int i=0; i < config.BubakLocations.Count(); i++)
		{
			
			//
			
			string posrot = config.BubakLocations.Get(i).triggerpos;
			TStringArray loc = new TStringArray;
			posrot.Split( "|", loc );
			string pos = loc.Get(0);
			string rot = loc.Get(1);
			if (!rot)
			{
				pos = config.BubakLocations.Get(i).triggerpos;
				rot = "0 0 0";
			}
			SPBLogger.Log("Created trigger " + config.BubakLocations.Get(i).name + " at " + pos + " ori: " + rot);
			trigger = BubakTrigger.Cast(GetGame().CreateObject("BubakTrigger", pos.ToVector() ));
			trigger.SetOrientation(rot.ToVector());
			
			mins = config.BubakLocations.Get(i).triggermins.ToVector();
			maxs = config.BubakLocations.Get(i).triggermaxs.ToVector();
			radius = config.BubakLocations.Get(i).triggerradius;
			if (radius == 0)
			{
				trigger.SetExtents(mins, maxs);
			} else {
				trigger.SetCollisionCylinder(radius, 1.8);
			} 
			
			trigger.SetTriggerName(config.BubakLocations.Get(i).name);
			trigger.SetTriggerNotification(config.BubakLocations.Get(i).notification);
			trigger.SetTriggerNotificationTime(config.BubakLocations.Get(i).notificationtime);
			trigger.SetSpawnLocations(config.BubakLocations.Get(i).spawnerpos);
			trigger.SetBubaci(config.BubakLocations.Get(i).bubaci);
			trigger.SetLastTriggerTime(-1 * config.BubakLocations.Get(i).triggerdelay);
			trigger.SetTriggerDelay(config.BubakLocations.Get(i).triggerdelay);
			trigger.SetBubakNum(config.BubakLocations.Get(i).bubaknum);
			trigger.SetOnlyFillUpToBubaknum(config.BubakLocations.Get(i).onlyfilluptobubaknum);
		}
		//GetGame().CreateObject("MyCustomTrigger", "1683 457 14219");
		//GetGame().CreateObject("Bone", "1683 457 14219");		
	}

	void AddSpawnedInstance(int trigger_id, int bubak_id)
	{
		TIntArray spawned_trigger_instances = spawned_instances.Get(trigger_id);
		if(!spawned_trigger_instances) spawned_trigger_instances = new TIntArray;
		spawned_trigger_instances.Insert(bubak_id);
		spawned_instances.Set(trigger_id, spawned_trigger_instances);
	}

	void RemoveSpawnedInstance(int trigger_id, int bubak_id)
	{
		SPBLogger.Log("SpawnerBubaku.RemoveSpawnedInstance(" + trigger_id + ", " + bubak_id + ")");
		spawned_instances.Get(trigger_id).RemoveItem(bubak_id);
	}

	TIntArray GetSpawnedInstances(int trigger_id)
	{
		if(spawned_instances) return spawned_instances.Get(trigger_id);
		return NULL;
	}
}

