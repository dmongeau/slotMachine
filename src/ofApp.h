#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxTextBlock.h"

class ofApp : public ofBaseApp{

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
        void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void exit();
    
        ofxTCPServer        server;
        ofSerial            serial;		
    
        float               money;
        float               displayMoney;
    
        ofxTextBlock        priceText;

};
