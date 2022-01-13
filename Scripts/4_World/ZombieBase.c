modded class ZombieBase extends DayZInfected {

    int m_trigger_id;

    override void EEKilled(Object killer)
	{
        if(m_trigger_id) SpawnerBubaku.GetInstance().RemoveSpawnedInstance(m_trigger_id, GetID());
        super.EEKilled(killer);
    }

    void SetTriggerId(int trigger_id)
    {
        m_trigger_id = trigger_id;
    }
}
