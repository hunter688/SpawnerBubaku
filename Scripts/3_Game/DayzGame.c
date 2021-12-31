modded class DayZGame
{	
	protected ref BuBuConfig m_BubakConfig;

	
    void SetBubakConfig(BuBuConfig config)
    {
        m_BubakConfig = config;
    }

    BuBuConfig GetBubakConfig()
    {
		return m_BubakConfig;
    }
};