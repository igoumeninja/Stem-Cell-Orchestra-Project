// Stem Orchestra Performance
NetAddr(hostname:"localhost",port:12345).sendMsg("/projection",0,1,1,1,1,1,1,1,1,1,0,1,1,0,1)
NetAddr(hostname:"localhost",port:12345).sendMsg("/projection",0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,11)
NetAddr(hostname:"localhost",port:12345).sendMsg("/projection",0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)
(
NetAddr(hostname:"localhost",port:12345).sendMsg("/projection",0,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
)
)

(
~delayTime = 0.2;
k = {
	inf.do{
NetAddr(hostname:"localhost",port:12345).sendMsg("/projection",0,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
	rrand(1,16).asInt,
);
		~delayTime.wait;
	}
}.fork
)

NetAddr(hostname:"localhost",port:12345).sendMsg("/videoSpeed",0,4)

OF.projection(0,1);
OF.projection(1,0);
OF.projection(2,2);
OF.filter(2);
OF.filter(0);
OF.videoPos(2,0)

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

//PHRASES
NetAddr(hostname:"localhost", port:57120).sendMsg("phrase_1")
NetAddr(hostname:"localhost", port:57120).sendMsg("phrase_2")
(
~phrase_1.remove;
~phrase_1 = OSCresponder.new(nil, "phrase_1", {
	arg time, resp, msg;
	("ok"+xrand(10)).postln;
	{
		20.do{ |i|
			OF.filter(xrand(7));
			0.1.wait;
			OF.filter(0);
		}
	}.fork;
} ).add;
)

(
~phrase_2.remove;
~phrase_2 = OSCresponder.new(nil, "phrase_2", {
	arg time, resp, msg;
	"phrase 2".postln;
	{
		20.do{ |i|
			OF.projection(rrand(0,2).asInt,rrand(0,2).asInt);
			0.1.wait;
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