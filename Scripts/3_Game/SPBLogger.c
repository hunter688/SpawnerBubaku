class SPBLogger {
	
	static int LOGLEVEL_CRITICAL = 0;
	static int LOGLEVEL_DEBUG = 100;
	private int m_loglevel;

	static protected ref SPBLogger s_Instance;

	void SPBLogger()
	{
		s_Instance = this;
		m_loglevel = LOGLEVEL_CRITICAL;

 		BuBuConfig config = GetDayZGame().GetBubakConfig()
		if(config && config.loglevel) m_loglevel = config.loglevel;
	}

	static SPBLogger GetInstance()
	{
		if(!s_Instance) new SPBLogger();
		return s_Instance;
	}

	void Log(string txt, int loglevel = 100)
	{
		if(loglevel > m_loglevel) return;

		string file_path = "$profile:\\SpawnerBubaku\\SpawnerBubaku.log";
		FileHandle logFile = OpenFile(file_path, FileMode.APPEND);

		if (logFile != 0) {
				FPrintln(logFile, GetDate() + " [SpawnerBubaku] " + txt);
				CloseFile(logFile);
		}
	}
	
	private string GetDate(bool fileFriendly = false) {
		int year, month, day, hour, minute, second;

		GetYearMonthDayUTC(year, month, day);
		GetHourMinuteSecondUTC(hour, minute, second);

		string date = year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + "T"  + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2) + "Z";
		if (fileFriendly) {
			date.Replace(" ", "_");
			date.Replace(".", "-");
			date.Replace(":", "-");
		}

		return date;
	}
}