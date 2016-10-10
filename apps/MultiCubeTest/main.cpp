#include "app.h"
#include "appgl.h"
#include "apprg.h"

#include <geUtil/ArgumentObject.h>

const std::string help = 
R".(Multiple cube rendering performance test
-cubeCount n (1000)
-textureCount n (0)
-textureSize n (128)
-single|-many|-multi|-instanced
-interactive|-test|-testAll|-calibrate
).";


int main(int argc, char*argv[]) {
	ge::util::ArgumentObject args(argc,argv);

	if (args.isPresent("--help") ||
		args.isPresent("-help") || 
		args.isPresent("-h") ||
		args.isPresent("/?")) {
		std::cout << help;
		return 0;
	}


	Options opt;
	// process args
	opt.cubeCount = args.getArgi("-cubeCount", "1000");
	opt.textureCount = args.getArgi("-textureCount", "0");
	opt.textureSize = args.getArgi("-textureSize", "128");
	
	auto drawMode = args.getArg("-drawMode", "single");
	opt.drawMode = SINGLE_DRAW;
	if (drawMode == "many") opt.drawMode = MANY_DRAW;
	if (drawMode == "multi") opt.drawMode = MULTIDRAW_INDIRECT;
	if (drawMode == "instanced") opt.drawMode = INSTANCED;

	
	opt.appMode = INTERATIVE;
	//if (args.isPresent("-interactive")) opt.appMode = Options::INTERATIVE;
	if (args.isPresent("-test")) opt.appMode = TEST;
	if (args.isPresent("-testAll")) opt.appMode = TEST_ALL;
	if (args.isPresent("-calibrate")) opt.appMode = CALIBRATE;
	if (args.isPresent("-calibrateAll")) opt.appMode = CALIBRATE_ALL;
	

	if (opt.rg) {
		AppRG app(opt);
		return app.run();
	}else {
		AppGL app(opt);
		return app.run();
	}
}
