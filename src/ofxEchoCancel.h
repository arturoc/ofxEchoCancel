/*
 * ofxEchoCancel.h
 *
 *  Created on: Oct 3, 2013
 *      Author: arturo
 */

#ifndef OFXECHOCANCEL_H_
#define OFXECHOCANCEL_H_

#include "modules/audio_processing/interface/audio_processing.h"
#include "modules/interface/module_common_types.h"
#include "ofParameter.h"
#include "ofConstants.h"
#include "ofParameterGroup.h"

class ofxEchoCancel {
public:
	ofxEchoCancel();
	virtual ~ofxEchoCancel();

	void setup();
	void analyzeReverse(webrtc::AudioFrame & frame);
	void process(webrtc::AudioFrame & frame);

	webrtc::AudioProcessing* getAudioProcessing();

	ofParameter<bool> echoCancelEnabled;
	ofParameter<bool> gainControlEnabled;
	ofParameter<bool> noiseSuppressionEnabled;
	ofParameter<bool> highPassFilterEnabled;
	ofParameter<bool> voiceDetectionEnabled;
	ofParameter<bool> driftCompensationEnabled;
	ofParameterGroup parameters;

private:
	void echoCancelEnabledChanged(bool & enabled);
	void gainControlEnabledChanged(bool & enabled);
	void noiseSuppressionEnabledChanged(bool & enabled);
	void highPassFilterEnabledChanged(bool & enabled);
	void voiceDetectionEnabledChanged(bool & enabled);
	void driftCompensationEnabledChanged(bool & enabled);

	webrtc::AudioProcessing* ap;
	webrtc::AudioFrame remoteFrame, localFrame;
};

#endif /* OFXECHOCANCEL_H_ */
