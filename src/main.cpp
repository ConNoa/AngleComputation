#include "ofMain.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "LensApp.hpp"
#include "ofAppGLFWWindow.h"
#include "ofApp.h"
#include "Lens.hpp"

//========================================================================
int main( ){

		ofGLFWWindowSettings settings;

		settings.setSize(1100, 1000);
		settings.setPosition(glm::vec2(0,1000));
		settings.resizable = true;
		shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

		settings.setSize(1550, 1000);
		settings.setPosition(glm::vec2(1200,1000));
		settings.resizable = false;
		shared_ptr<ofAppBaseWindow> lensWindow = ofCreateWindow(settings);

		shared_ptr<ofApp> mainApp(new ofApp);
		shared_ptr<LensApp> lensApp(new LensApp);
		mainApp->lenses = lensApp;

		ofRunApp(lensWindow, lensApp);
		ofRunApp(mainWindow, mainApp);
		ofRunMainLoop();
}
