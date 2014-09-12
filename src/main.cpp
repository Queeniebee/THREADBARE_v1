#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
        
    ofAppGLFWWindow window;
	ofSetupOpenGL(&window, 1400,1050,OF_WINDOW); // <-------- setup the GL context
//    window.setMultiDisplayFullscreen(true);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
    
}