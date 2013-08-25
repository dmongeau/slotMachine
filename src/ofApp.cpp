#include "ofApp.h"

// trim trailing spaces
string ofxTrimStringRight(string str) {
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

// trim trailing spaces
string ofxTrimStringLeft(string str) {
    size_t startpos = str.find_first_not_of(" \t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

string ofxTrimString(string str) {
    return ofxTrimStringLeft(ofxTrimStringRight(str));;
}


string ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    while ((ch=serial.readByte())>0 && ttl-->0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    if (ch==until) {
        string tmp=str;
        str="";
        return ofxTrimString(tmp);
    } else {
        return "";
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    
    money = 0.00;
    displayMoney = -0.01;
    
    serial.setup("/dev/ttyACM0", 9600);
    
    server.setup(7678);
    server.setVerbose(true);
    
    priceText.init("courrier.ttf", 120);
    
    priceText.setText("0.00 $");
    
    //Initially wrap the text to the screen width
    priceText.wrapTextX(ofGetWidth());
}


//--------------------------------------------------------------
void ofApp::update(){
    
    if(server.isConnected() && server.getNumClients() > 0) {
        string response = ofxTrimString(server.receive(0));
        if(response.length() > 0) {
            cout << "Receive: " << response << endl;
            unsigned char* chars = (unsigned char*) response.c_str(); // cast from string to unsigned char*
            int length = response.length();
            serial.writeBytes(chars,length);
            money += (ofToFloat(response)*0.25);
        }
    }
    
    if(displayMoney < money) {
        displayMoney += 0.01;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    priceText.setColor(255,255,255,255);
    priceText.setText(ofToString(displayMoney,2)+" $");
    priceText.drawCenter(ofGetWidth()/2,(ofGetHeight()-priceText.getHeight()*1.5)/2);
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit(){
	server.close();
    cout << "Server closed";
}
