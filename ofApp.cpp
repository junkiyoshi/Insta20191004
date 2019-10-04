#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}

	int size = 60;
	for (int x = size * 0.5; x <= ofGetWidth() - size * 0.5; x += size) {

		for (int y = size * 0.5; y <= ofGetHeight() - size * 0.5; y += size) {

			this->location_list.push_back(glm::vec2(x, y));

			int color_index = ofRandom(this->color_list.size());
			this->color_index_list.push_back(color_index);

			int rotate_param = ofRandom(4);
			this->rotate_param_list.push_back(rotate_param);

			this->deg_start_list.push_back(0);
			this->deg_end_list.push_back(90);
			this->flag_list.push_back(false);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->location_list.size(); i++) {

		if (ofGetFrameNum() % 45 == 0) {

			if (ofRandom(100) < 10) { this->flag_list[i] = true; }
		}

		if (this->flag_list[i]) {

			if (this->deg_end_list[i] < 90) {

				this->deg_end_list[i] += 2;
			}
			else {

				this->deg_start_list[i] += 2;
				if (this->deg_start_list[i] >= 90) {

					this->deg_end_list[i] = 0;
					this->deg_start_list[i] = 0;
					this->color_index_list[i] = ofRandom(this->color_list.size());
					this->rotate_param_list[i] = (this->rotate_param_list[i] + 1) % this->rotate_param_list.size();
				}
			}

			if (this->deg_start_list[i] == 0 && this->deg_end_list[i] == 90) { this->flag_list[i] = false; }
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int size = 60;
	int radius = size * 0.5;
	int width = 5;
	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i].x, this->location_list[i].y);
		ofRotate(90 * this->rotate_param_list[i]);

		vector<glm::vec2> vertices_1, vertices_2;
		for (int deg = this->deg_start_list[i]; deg <= this->deg_end_list[i]; deg++) {

			vertices_1.push_back(glm::vec2(size * -0.5 + (radius + width) * cos(deg * DEG_TO_RAD), size * -0.5 + (radius + width) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2(size * -0.5 + (radius - width) * cos(deg * DEG_TO_RAD), size * -0.5 + (radius - width) * sin(deg * DEG_TO_RAD)));
		}

		this->draw_arc(vertices_1, vertices_2, this->color_list[this->color_index_list[i]]);

		vertices_1.clear();
		vertices_2.clear();
		for (int deg = 180 + this->deg_start_list[i]; deg <= 180 + this->deg_end_list[i]; deg++) {

			vertices_1.push_back(glm::vec2(size * 0.5 + (radius + width) * cos(deg * DEG_TO_RAD), size * 0.5 + (radius + width) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2(size * 0.5 + (radius - width) * cos(deg * DEG_TO_RAD), size * 0.5 + (radius - width) * sin(deg * DEG_TO_RAD)));
		}

		this->draw_arc(vertices_1, vertices_2, this->color_list[this->color_index_list[i]]);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::draw_arc(vector<glm::vec2> vertices_1, vector<glm::vec2> vertices_2, ofColor color) {

	ofFill();
	ofSetColor(color);

	std::reverse(vertices_2.begin(), vertices_2.end());

	ofBeginShape();
	ofVertices(vertices_1);
	ofVertices(vertices_2);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(239);

	ofBeginShape();
	ofVertices(vertices_1);
	ofEndShape(false);

	ofBeginShape();
	ofVertices(vertices_2);
	ofEndShape(false);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}