modded class DayZGame
{	
	protected ref BuBuConfig m_BubakConfig;
	protected ref StatBubConfig m_StaticBubakConfig;

	
    void SetBubakConfig(BuBuConfig config)
    {
        m_BubakConfig = config;
    }

    BuBuConfig GetBubakConfig()
    {
  		return m_BubakConfig;
    }
	
	void SetStaticBubakConfig(StatBubConfig config)
    {
        m_StaticBubakConfig = config;
    }

    StatBubConfig GetStaticBubakConfig()
    {
		return m_StaticBubakConfig;
    }

};
