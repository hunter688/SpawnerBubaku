modded class ZombieBase {

    int m_trigger_id;

    override void EEKilled(Object killer)
	{
        SpawnerBubaku plugin = SpawnerBubaku.Cast(GetPluginManager().GetPluginByType(SpawnerBubaku));
		if(m_trigger_id)
		{
			plugin.RemoveSpawnedInstance(m_trigger_id, GetID());
		}
        super.EEKilled(killer);
    }

    void SetTriggerId(int trigger_id)
    {
        m_trigger_id = trigger_id;
    }
}
