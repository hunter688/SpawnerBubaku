

class SpawnerBubaku
{

	protected static ref SpawnerBubaku Instance;
	protected ref map<int, ref TIntArray> spawned_instances;
	protected ref array<BubakTrigger> m_Triggers;

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
	array<BubakTrigger> GetTriggers()
	{
		return m_Triggers;
	}
	
	void AddTrigger(BubakTrigger trigger)
	{
		m_Triggers.Insert(trigger);
		SPBLogger.GetInstance().Log( "Added trigger to pool " + m_Triggers.Count() );
	}
	
	void SpawnerBubaku()
    {
        
		SPBLogger.GetInstance().Log( "SpawnerBubaku started!" );
		m_Triggers = new array<BubakTrigger>;
		spawned_instances = new map<int, ref TIntArray>;

		BuBuConfig config = GetDayZGame().GetBubakConfig();
		BubakTrigger trigger;
		vector mins, maxs;
		float radius, cylradius, cylheight, spawnradius;
		for ( int i=0; i < config.BubakLocations.Count(); i++)
		{
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
			if (pos.Contains(","))
			{
				SPBLogger.GetInstance().Log("Trigger position contains commas, thats wrong! Only one space between numbers! Fix yours config according example!!!", SPBLogger.LOGLEVEL_CRITICAL);
			}
			else
			{
				SPBLogger.GetInstance().Log("Created trigger " + config.BubakLocations.Get(i).name + " at " + pos + " ori: " + rot, SPBLogger.LOGLEVEL_CRITICAL);
			}
			trigger = BubakTrigger.Cast(GetGame().CreateObject("BubakTrigger", pos.ToVector() ));
			trigger.SetOrientation(rot.ToVector());
			
			mins = config.BubakLocations.Get(i).triggermins.ToVector();
			maxs = config.BubakLocations.Get(i).triggermaxs.ToVector();
			radius = config.BubakLocations.Get(i).triggerradius;
			cylradius = config.BubakLocations.Get(i).triggercylradius;
			cylheight = config.BubakLocations.Get(i).triggercylheight;
			if (radius == 0 && cylradius == 0)
			{
				trigger.SetExtents(mins, maxs);
			} else if (radius > 0 && cylradius == 0)
			{
				trigger.SetCollisionSphere(radius);
			} else if (radius ==0 && cylradius > 0) 
			{
				trigger.SetCollisionCylinder(cylradius, cylheight);
			} 
			
			trigger.SetTriggerName(config.BubakLocations.Get(i).name);
			trigger.SetTriggerNotification(config.BubakLocations.Get(i).notification);
			trigger.SetTriggerNotificationTime(config.BubakLocations.Get(i).notificationtime);
			trigger.SetSpawnLocations(config.BubakLocations.Get(i).spawnerpos);
			trigger.SetSpawnRadius(config.BubakLocations.Get(i).spawnradius);
			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}			if (!configData.BubakLocations.Get(i).bubakinventory)
			{
				configData.BubakLocations.Get(i).bubakinventory = {"TunaCan", "Rag", "Pajka"};
			}
			trigger.SetBubaci(config.BubakLocations.Get(i).bubaci);
			trigger.SetLastTriggerTime(-1 * config.BubakLocations.Get(i).triggerdelay);
			trigger.SetTriggerDelay(config.BubakLocations.Get(i).triggerdelay);
			trigger.SetBubakNum(config.BubakLocations.Get(i).bubaknum);
			trigger.SetOnlyFillUpToBubaknum(config.BubakLocations.Get(i).onlyfilluptobubaknum);
			trigger.SetRandomDamage(config.BubakLocations.Get(i).itemrandomdmg);
			trigger.SetWorkingHours(config.BubakLocations.Get(i).workinghours);
			trigger.SetBubaciInventory(config.BubakLocations.Get(i).bubakinventory);
			trigger.SetTriggerDependency(config.BubakLocations.Get(i).triggerdependency);
			
			AddTrigger(trigger);
		}
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
		SPBLogger.GetInstance().Log("SpawnerBubaku.RemoveSpawnedInstance(" + trigger_id + ", " + bubak_id + ")");
		spawned_instances.Get(trigger_id).RemoveItem(bubak_id);
	}

	TIntArray GetSpawnedInstances(int trigger_id)
	{
		if(spawned_instances) return spawned_instances.Get(trigger_id);
		return NULL;
	}
}

