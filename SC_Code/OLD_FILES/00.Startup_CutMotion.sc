/*
This class is used as a startup file
OSCFunc.trace(true)
Aris Bezas Igoumeninja 140723

*/

Startup_InOut {

	*initClass {
		StartUp add: {
			this.startupInOut;
		}
	}

	*startupInOut {
		Task({
			if (not(Server.default.serverRunning)) { Server.default.boot };
			Server.default.doWhenBooted {
				~sendOnsets = SendOnsets.new(0);
				0.04.wait;
			};
		}).play;
	}

}