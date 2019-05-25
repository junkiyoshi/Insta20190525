#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto rect_width = 30;
	auto rect_length = 180;
	for (int x = rect_length * 0.5; x < ofGetWidth(); x += rect_length) {

		for (int y = rect_length * 0.5; y < ofGetHeight(); y += rect_length) {

			auto noise_seed_y = ofRandom(1000);
			auto noise_seed_x = ofRandom(1000);
			for (int len = rect_width; len < rect_length; len += rect_width) {

				ofPushMatrix();
				ofTranslate(x, y);
				ofRotateY(ofMap(ofNoise(noise_seed_y, len * 0.003 + ofGetFrameNum() * 0.003), 0, 1, -180, 180));
				ofRotateX(ofMap(ofNoise(noise_seed_x, len * 0.003 + ofGetFrameNum() * 0.003), 0, 1, -180, 180));

				vector<glm::vec2> vertices, inner_vertices;

				auto tmp_len = len - 5;
				vertices.push_back(glm::vec2(-tmp_len * 0.5, -tmp_len * 0.5));
				vertices.push_back(glm::vec2(tmp_len * 0.5, -tmp_len * 0.5));
				vertices.push_back(glm::vec2(tmp_len * 0.5, tmp_len * 0.5));
				vertices.push_back(glm::vec2(-tmp_len * 0.5, tmp_len * 0.5));

				auto inner_len = len - rect_width;
				inner_vertices.push_back(glm::vec2(-inner_len * 0.5, -inner_len * 0.5));
				inner_vertices.push_back(glm::vec2(inner_len * 0.5, -inner_len * 0.5));
				inner_vertices.push_back(glm::vec2(inner_len * 0.5, inner_len * 0.5));
				inner_vertices.push_back(glm::vec2(-inner_len * 0.5, inner_len * 0.5));

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				ofVertices(vertices);
				ofNextContour(true);
				ofVertices(inner_vertices);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				ofVertices(vertices);
				ofNextContour(true);
				ofVertices(inner_vertices);
				ofEndShape(true);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}