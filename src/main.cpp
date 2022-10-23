#include "ofAppGLFWWindow.h"
#include "ofMain.h"
#include "ofApp.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "LensApp.hpp"
#include "Lens.hpp"
#include "State.hpp"

//========================================================================
int main( ){


		#ifdef OF_TARGET_OPENGLES
			ofGLESWindowSettings settings;
			settings.glesVersion = 2;
		#else
			ofGLWindowSettings settings;
			settings.setGLVersion(3, 2);
		#endif

		// ofGLFWWindowSettings settings;

		settings.setSize(1600, 1000);
		settings.setPosition(glm::vec2(0,1000));
		// settings.resizable = true;
		settings.title = "MEMS PLANE VISUALISATION";

		shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

		settings.setSize(1600, 1000);
		settings.setPosition(glm::vec2(1650,1000));
		// settings.resizable = false;
		settings.title = "LENS - INTERFACE";

		shared_ptr<ofAppBaseWindow> lensWindow = ofCreateWindow(settings);

		shared_ptr<ofApp> mainApp(new ofApp);
		shared_ptr<LensApp> lensApp(new LensApp);
		shared_ptr<State> shrd(new State);


		mainApp->shrd = shrd;
		mainApp->lenses = lensApp;

		lensApp->shrd = shrd;


		ofRunApp(lensWindow, lensApp);
		ofRunApp(mainWindow, mainApp);
		ofRunMainLoop();
}
