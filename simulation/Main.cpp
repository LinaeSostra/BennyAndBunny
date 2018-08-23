#include "Main.h"
#include <fstream>

using namespace std;

// This code is to run simulation the Semi-gradient RL algorithm
// for 50 episodes to verify the algorithm works as intended, and
// then for verfication to be placed on the firmwire of Benny and Bunny

// Heavy Reference of Nick S Walker's Arduino RL code was used while 
// writing this coding:
// https://github.com/nickswalker/ArduinoRL/blob/master/TwoJoint/TwoJoint.ino

Action nextAction = Stay;

double lastReward = 0.0;

double cumulativeReward = 0.0;
int currentEpisodeStep = 0; 
int currentEpisode = 0;

void logStepInformation() {
	cout << "\n(Current Episode, Cumulative Reward):\t(" << currentEpisodeStep << " , " << cumulativeReward << ")\n";
}

void markEpisodeStart() {
	cout << "\n!!!\n";
}

void markEpisodeEnd() {
	cout << "\n***\n";
}

void completedLearning() {
	cout << "\nFinished RL Learning after 50 episodes";
}

void cleanFile() {
	ofstream file;
	file.open("test.csv", ios::out);
}

void recordEpisodeToFile() {
	ofstream file;
	file.open("test.csv", ios::app);
	file << currentEpisode << "," << currentEpisodeStep << "," << cumulativeReward << "\n";
}

void restartEpisode() {
	recordEpisodeToFile();
	//drawGrid(currentState);
	logStepInformation();
	logWeights();
	resetPosition();
	cumulativeReward = 0.0;
	currentEpisodeStep = 0;
	markEpisodeEnd();
	currentEpisode += 1;
}

int main() {
	cleanFile();
	bool stillLearning = true;
	//logWeights(); //TODO:REMOVES!!!
	while(stillLearning) {
		//cout << "~~~~~~~~~~~~~~~~\nCurrent Episode Step:\t" << currentEpisodeStep << "\n";
		//Populates current and previous state for us
		apply(nextAction);
		//cout << "Action Movement: " << nextAction << "\n";
		//cout << "Previous State: (" << previousState.xPosition << ", " << previousState.yPosition << ", " << previousState.angle << ")" << "\n";
		//cout << "Current State: (" << currentState.xPosition << ", " << currentState.yPosition << ", " << currentState.angle << ")" << "\n";
		
		// Log values from firmwire here, but not applicable in simulation
		//logWeights();

		// TODO(Rebecca): I don't think this comment is correct
		// RL algorithm populates next action for us
		Action previousAction = nextAction;
		update(previousState, previousAction, currentState);

		// Update & Log progress of episode
		currentEpisodeStep += 1;
		cumulativeReward += lastReward; 
		//logStepInformation();
		//drawGrid(currentState);

		// Start new episode if agent meets terminal conditions
		bool reachedMaxEpisodeSteps = currentEpisodeStep >= EVALUATION_MAX_STEPS;
		if(stateIsTerminal(currentState) || reachedMaxEpisodeSteps) {
			restartEpisode();
			// If enough episodes were conducted, stop learning
			bool finishedLearning = EVALUATION_MODE && currentEpisode > EVALUATION_SWITCH_POINT;
			if(finishedLearning) {
				stillLearning = false;
			} else {
				markEpisodeStart();
				logWeights();

			}
		}
	}
	completedLearning();
}