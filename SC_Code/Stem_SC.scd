// Stem Orchestra Performance

OF.projection(0,2);
OF.filter(2);
OF.filter(0);
OF.videoPos(0,0)

(
~delayTime = 0.2;
k = {
	inf.do{
		OF.videoPos(rrand(0,2).asInt,rrand(200000,100000240).asInt);
		OF.videoSpeed(rrand(0,2).asInt,1);
		~delayTime.wait;
	}
}.fork
)

//:Trigger responder
(
~responder1.remove;
~responder1 = OSCresponder.new(nil, "onset", {
	arg time, resp, msg;
	"ok"+xrand(10).postln;
	{
		1.do{ |i|
			OF.imgID(xrand(57));
			0.04.wait;
			OF.filter(xrand(7));
			0.1.wait;
			OF.filter(0);

		}
	}.fork;
} ).add;
)



/* Inside Outside
"/Users/ari/Downloads/download_pictures/""/Users/ari/Media/images/ambiantWorkshop/ALL2/ELENHSPHOTOS2/"

OF.rect(0,0,400,400)
OF.imgID(6)
*/

//:Load images to oF
(
~imageLib = MultiLevelIdentityDictionary.new;
~loadImages2oF = { | path = "/Users/ari/Media/images/ambiantWorkshop/ALL2/ELENHSPHOTOS2/*"|
	var folders, files, imageDict;
	imageDict = IdentityDictionary.new;
	folders = path.pathMatch;
	folders do: { | f |
		f.basename.postln;
		imageDict[f.basename.asSymbol] = format("%*", f).pathMatch;
		postf("FOLDER LOADED: \n%\n", f);
	};
	{
		var index = 0;
		imageDict keysValuesDo: { | folder, files |
 			files do: { | path, i |
	 			postf("LOADING: %, %, %\n", index, folder, path.basename);
	 			OF.loadImage(index, path);
				~imageLib.put(folder, i, index);
	 			index = index + 1;
				0.01.wait;
 			}
		}

	}.fork;
};
)
~loadImages2oF.value;


//:Play a fork
(
~delayTime = 0.1;
k = {
	~delayTime = 0.1;
	~countX = 0;
	~countY = 0;
	~screenWidth = 1280;
	~screenHeight = 780;
	~fotoWidth = ~fotoHeight = ~screenWidth/20;
	~fotoHeight = ~fotoWidth;
	inf.do{
		57.do{ |i|
			186.postln;
			//OF.img(72.rand.asInteger, 0,0, ~screenWidth, ~screenHeight);
			OF.imgID(20.rand.asInteger);
			~delayTime.wait;
		}
	}
}.fork
)
// Onset Detection
b = SendOnsets.new
b.start
b.threshold(0.2)

b.stop

OSCFunc.trace(true)
~sendOnsets = SendOnsets.new(0);

//:Trigger responder
(
~responder.remove;
~responder = OSCresponder.new(nil, "onset", {
	arg time, resp, msg;
	"ok"+xrand(10).postln;
	{
		1.do{ |i|
			OF.imgID(xrand(57));
			0.04.wait;
			OF.filter(xrand(7));
			0.1.wait;
			OF.filter(0);

		}
	}.fork;
} ).add;
)

//FIlters
OF.filter(0);
xrand(10)


//
(
{
		inf.do{ |i|
			OF.imgID(xrand(57));
			0.02.wait;
			OF.filter(xrand(7));
			0.05.wait;
			OF.filter(0);

		}
	}.fork;
)