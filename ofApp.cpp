#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto radius = 200;
	int deg_span = 4;

	vector<ofColor> color_list;
	vector<float> noise_seed_list;

	ofColor color;
	for (int i = 0; i < 6; i++) {

		color.setHsb(ofMap(i, 0, 6, 0, 255), 150, 230);
		color_list.push_back(color);
	}

	for (int i = 0; i < color_list.size(); i++) {

		auto noise_seed = ofRandom(1000);
		noise_seed_list.push_back(noise_seed + ofRandom(1000, 2000));
	}
	
	for (int deg = 0; deg < 360; deg += deg_span) {

		int param = deg % (deg_span * color_list.size());
		auto len = 10;

		for (int i = 0; i < color_list.size(); i++) {

			if (param == deg_span * i) {

				//len = ofMap(ofNoise(noise_seed_list[i], cos(deg * DEG_TO_RAD) * 0.1, sin(deg * DEG_TO_RAD) * 0.1, ofGetFrameNum() * 0.02), 0, 1, radius * 0.25, radius);
				len = ofMap(ofNoise(noise_seed_list[i], ofGetFrameNum() * 0.02), 0, 1, radius * 0.25, radius);
				ofSetColor(color_list[i]);
			}
		}

		auto location_1 = glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD));
		auto location_2 = glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD));

		ofDrawLine(location_1, location_2);
		ofDrawCircle(location_1, 3);
		ofDrawCircle(location_2, 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}