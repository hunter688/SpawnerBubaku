#ifdef SERVER
modded class PluginManager
{
	override void Init()
	{	
		RegisterPlugin( "SpawnerBubaku", false,	true ); //server side
		RegisterPlugin( "PluginStaticBubakManager", false,	true ); //server side
		super.Init();
	}
}
#endif