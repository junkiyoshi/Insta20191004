﻿#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void draw_arc(vector<glm::vec2> vertices_1, vector<glm::vec2> vertices_2, ofColor color);

	vector<ofColor> color_list;

	vector<glm::vec2> location_list;
	vector<int> color_index_list;
	vector<int> rotate_param_list;
	vector<int> deg_start_list;
	vector<int> deg_end_list;
	vector<bool> flag_list;
};