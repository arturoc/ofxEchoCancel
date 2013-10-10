/*
 * ofxEchoCancel.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: arturo
 */

#include "ofxEchoCancel.h"

ofxEchoCancel::ofxEchoCancel()
:ap(NULL){

}

ofxEchoCancel::~ofxEchoCancel() {
}

void ofxEchoCancel::setup(){
	ap = webrtc::AudioProcessing::Create(0);
	ap->Initialize();
	ap->set_num_channels(1,1);
	ap->set_num_reverse_channels(2);
	ap->set_sample_rate_hz(32000);

	ap->echo_cancellation()->Enable(true);
	ap->echo_cancellation()->set_suppression_level(webrtc::EchoCancellation::kHighSuppression);
	ap->echo_cancellation()->enable_drift_compensation(false);
	ap->echo_cancellation()->set_device_sample_rate_hz(44100);

	ap->gain_control()->Enable(true);
	ap->gain_control()->set_mode(webrtc::GainControl::kAdaptiveAnalog);
	ap->gain_control()->set_analog_level_limits(0, 0x10000U-1);

	ap->noise_suppression()->Enable(true);
	ap->noise_suppression()->set_level(webrtc::NoiseSuppression::kVeryHigh);

	ap->high_pass_filter()->Enable(true);

	ap->voice_detection()->Enable(true);
	ap->voice_detection()->set_likelihood(webrtc::VoiceDetection::kLowLikelihood);

	parameters.setName("echo cancel");
	parameters.add(echoCancelEnabled.set("echoCancelEnabled",true));
	parameters.add(gainControlEnabled.set("gainControlEnabled",true));
	parameters.add(noiseSuppressionEnabled.set("noiseSuppressionEnabled",true));
	parameters.add(highPassFilterEnabled.set("highPassFilterEnabled",true));
	parameters.add(voiceDetectionEnabled.set("voiceDetectionEnabled",true));
	parameters.add(driftCompensationEnabled.set("driftCompensationEnabled",false));


	echoCancelEnabled.addListener(this,&ofxEchoCancel::echoCancelEnabledChanged);
	gainControlEnabled.addListener(this,&ofxEchoCancel::gainControlEnabledChanged);
	noiseSuppressionEnabled.addListener(this,&ofxEchoCancel::noiseSuppressionEnabledChanged);
	highPassFilterEnabled.addListener(this,&ofxEchoCancel::highPassFilterEnabledChanged);
	voiceDetectionEnabled.addListener(this,&ofxEchoCancel::voiceDetectionEnabledChanged);
	driftCompensationEnabled.addListener(this,&ofxEchoCancel::driftCompensationEnabledChanged);
}

void ofxEchoCancel::analyzeReverse(webrtc::AudioFrame & frame){
	if(echoCancelEnabled || gainControlEnabled)
		ap->AnalyzeReverseStream(&frame);
}

void ofxEchoCancel::process(webrtc::AudioFrame & frame){
	ap->ProcessStream(&frame);
}

webrtc::AudioProcessing* ofxEchoCancel::getAudioProcessing(){
	return ap;
}

void ofxEchoCancel::echoCancelEnabledChanged(bool & enabled){
	ap->echo_cancellation()->Enable(enabled);
}

void ofxEchoCancel::gainControlEnabledChanged(bool & enabled){
	ap->gain_control()->Enable(enabled);
}

void ofxEchoCancel::noiseSuppressionEnabledChanged(bool & enabled){
	ap->noise_suppression()->Enable(enabled);
}

void ofxEchoCancel::highPassFilterEnabledChanged(bool & enabled){
	ap->high_pass_filter()->Enable(enabled);
}

void ofxEchoCancel::voiceDetectionEnabledChanged(bool & enabled){
	ap->voice_detection()->Enable(enabled);
}

void ofxEchoCancel::driftCompensationEnabledChanged(bool & enabled){
	ap->echo_cancellation()->enable_drift_compensation(enabled);
}
