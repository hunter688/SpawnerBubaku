class CfgPatches
{
	class SpawnerBubaku
	{
		units[]= {};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods			
{
	class SpawnerBubaku
	{
        dir = "SpawnerBubaku";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 0;
        name = "SpawnerBubaku";
        credits = "Hunterz";
        author = "Hunterz";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";
		class defs
		{
			class gameScriptModule
            {
                value = "";
                files[] = {"SpawnerBubaku/scripts/3_Game"};
            };	
			class worldScriptModule
			{
				value = "";
				files[] = {"SpawnerBubaku/Scripts/4_World"};
			};
			class missionScriptModule
            {
                value="";
                files[]={"SpawnerBubaku/Scripts/5_Mission"};
            };
		}
    };
};