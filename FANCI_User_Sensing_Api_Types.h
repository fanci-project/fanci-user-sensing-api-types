/**
*
* Copyright (c) 2017 The FANCI User Sensing API Authors. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#ifndef __FANCI_USER_SENSING_API_TYPES__
#define __FANCI_USER_SENSING_API_TYPES__

#define MAX_LANDMARK_COUNT					170
#define HAND_COUNT							2
#define FINGER_COUNT						5

#include "FANCI_User_Sensing_Api.h"
#include <vector>
#include <string>

namespace fanci 
{
	// Image pointer
	typedef void* FaceAnalysisImage;

	/*********************************Eye Tracking*****************************************/
	enum TrackingState { normal = 0, recovery = 1, stopped = 2, calibrating = 3 };
	enum TrackerPosition { Unknown = 0, Center = 1, Left = 2, Right = 3 };
	// Eye position
	struct EyePosition
	{
		// Absolute
		float										fabsX;
		float										fabsY;
		float										fabsZ;

		// Normalized
		float										fnormX;
		float										fnormY;
		float										fnormZ;
	};

	struct EyePositionOutput
	{
		EyePosition									sEyeLeft;
		EyePosition									sEyeRight;
	};

	// Gaze
	struct GazeOutput
	{
		float										fMilliSeconds;
		float										fX;
		float										fY;
	};

	// Fixation
	struct FixationOutput
	{
		std::string									strDescription;
		float										fMilliSeconds;
		float										fX;
		float										fY;
	};

	// Overall Eyetracking pipeline output
	struct EyeTrackingOutput
	{
		EyePositionOutput							sEyePosition;
		GazeOutput									sEyeGaze;
		FixationOutput								sEyeFixation;
		TrackerPosition								sTracker;
	};


	/*********************************Face Analysis*****************************************/

	// Input image format
	enum ImageFormat { Image_RGB = 0, Image_IR = 1 };

	// Face localization input
	struct FaceLocalizationInput
	{
		enum AlgoType {NV = 0, KL = 1};
		
		FaceAnalysisImage							pImage;
		ImageFormat									tFormat;
		AlgoType									tAlgoType;
	};

	// Face bounding box
	struct FaceBoundingBox
	{
		float										fTopLeftX;
		float										fTopLeftY;
		float										fWidth;
		float										fHeight;
	};

	// Face localization output
	struct FaceLocalizationOutput
	{
		int											nDetectedFaceCount;
		std::vector<FaceBoundingBox>				vFaceLocations;
	};

	// Facial landmark
	struct FaceLandmark
	{
		float										nX;
		float										nY;
		float										nZ;
	};

	// Face landmarks input
	struct FaceLandmarkInput
	{
		FaceAnalysisImage							pImage;
		ImageFormat									tFormat;
		FaceBoundingBox								sBoundingBox;
	};

	// Face landmarks output
	struct FaceLandmarkOutput
	{
		int											nLandmarkCount;
		FaceLandmark								Landmarks[MAX_LANDMARK_COUNT];
	};

	// Headpose input
	struct HeadposeInput
	{
		// Process mode
		enum HeadposeMode { Landmarks = 0, FaceLocalization = 1 };
		
		FaceAnalysisImage							pImage;
		ImageFormat									tFormat;
		FaceLandmarkOutput							sLandmarks;
		FaceBoundingBox								sBoundingBox;
		HeadposeMode								tMode;
	};

	// Headpose output
	struct HeadposeOutput
	{
		float										fYaw;
		float										fPitch;
		float										fRoll;
	};

	// Facial gesture mouth
	enum FacialGestureMouth { MOUTH_CLOSED = 0, MOUTH_OPEN = 1 };

	// Facial gesture eyes
	enum FacialGestureEyes { EYES_CLOSED = 0, EYES_OPEN = 1 };

	// Facial gesture input
	struct FacialGestureInput
	{
		FaceLandmarkOutput							sLandmarks;
	};

	// Facial gesture output
	struct FacialGestureOutput
	{
		FacialGestureEyes							tEyes;
		FacialGestureMouth							tMouth;
	};

	// Emotion recognition input
	struct EmotionRecognitionInput
	{
		FaceAnalysisImage							pImage;
		ImageFormat									tFormat;
		FaceLandmarkOutput							sLandmarks;
		FaceBoundingBox								sBoundingBox;
	};

	// Emotion recognition output
	struct EmotionRecognitionOutput
	{
		float										fAnger;
		float										fDisgust;
		float										fFear;
		float										fHappiness;
		float										fNeutral;
		float										fSadness;
		float										fSurprise;
	};

	// Face biometric model
	struct FaceBiometricModel
	{
		std::string									strFaceID;
		void*										pModel;
	};


	// Face authentication input 
	struct FaceAuthenticationInput
	{
		FaceAnalysisImage							pImage;
		ImageFormat									tFormat;
		FaceBoundingBox								sBoundingBox;
		std::vector<FaceBiometricModel>				vModels;
	};

	// Authentication score for a ID
	struct PersonAuthenticationScore
	{
		std::string									strID;
		float										fScore;
	};

	// Facial authentication output
	struct FaceAuthenticationOutput
	{
		std::vector<PersonAuthenticationScore>		vScores;
	};

    // Overall facial analysis output
    struct FaceAnalysisOutput
    {
        FaceLocalizationOutput						sFaces;

        // For each face
        std::vector<FaceLandmarkOutput>				vLandmarks;
        std::vector<HeadposeOutput>					vHeadpose;
        std::vector<FacialGestureOutput>			vFaceGesture;
        std::vector<EmotionRecognitionOutput>		vEmotions;
        std::vector<FaceAuthenticationOutput>		vAuthentication;
    };

    // Face enrollment input
	struct FaceEnrollmentInput
	{
		std::string									strFaceID;
		std::vector<FaceAnalysisImage>				vImages;
		ImageFormat									tFormat;
		std::vector<FaceBoundingBox>				vBoundingBoxes;
	};

	// Face enrollment output
	struct FaceEnrollmentOutput
	{
		FaceBiometricModel							FaceModel;
		EmotionRecognitionOutput					sEmotions;
	};
	
	// Face enrollment status
	enum FaceEnrollmentStatus 
	{
		SUCCESS = 0,
		NO_FACE_DETECTED = 1,
		NOT_ENOUGH_FACES_DETECTED = 2,
		MULTIPLE_FACES_DETECTED = 3,
		INTERNAL_ERROR = 4,
		CAMERA_BUSY = 5,
		CAMERA_FAIL =6
	};

	/*********************************Audio Analysis*****************************************/
	// Audio pointer
	typedef void* VoiceAnalysisAudio;

	// Pitch detection input
	struct VoicePitchDetectionInput
	{
		VoiceAnalysisAudio							pAudio;
	};

	// Pitch detection output
	struct VoicePitchDetectionOutput
	{
		std::vector<float>							vHertzFrequency;
	};

	// Tone detection input
	struct VoiceToneDetectionInput
	{
		VoiceAnalysisAudio							pAudio;
		VoicePitchDetectionOutput					sVoicePitch;
	};

	// Tone detection output
	struct VoiceToneDetectionOutput
	{
		float										fStressLevel;
		EmotionRecognitionOutput					sEmotions;
	};

	// Voice biometric model
	struct VoiceBiometricModel
	{
		std::string									strVoiceID;
		void*										pModel;
	};

	// Voice authentication input
	struct VoiceAuthenticationInput
	{
		VoiceAnalysisAudio							pAudio;
		std::vector<VoiceBiometricModel>			vModels;
	};

	// Voice authentication output
	struct VoiceAuthenticationOutput
	{
		std::vector<PersonAuthenticationScore>		vScores;
	};

	struct VoiceAnalysisOutput
	{
		VoicePitchDetectionOutput					sPitchOutput;
		VoiceToneDetectionOutput					sToneOutput;
		VoiceAuthenticationOutput					vAuthentication;
	};

	// Voice enrollment input
	struct VoiceEnrollmentInput
	{
		std::string									strVoiceID;
		std::vector<VoiceAnalysisAudio>				vAudios;
	};

	typedef VoiceBiometricModel VoiceEnrollmentOutput;


	/*********************************Hand Gesture Analysis*****************************************/

	// Tracking status for hands
	enum HandTrackingStatus
	{
		HAND_INACTIVE = 0,				// The hand or finger is not tracked
		HAND_DETECTED = 1,				// The hand or finger is detected for the first time
		HAND_TRACKED = 2,				// The hand or finger is tracked
		HAND_EXTRAPOLATED = 3			// Unused
	};

	// Open status for hands 
	enum HandOpenStatus
	{
		HAND_OPENSTATUS_UNKNOWN = 0,
		HAND_CLOSED = 1,
		HAND_OPEN = 2
	};

	// Tracking status for finger
	enum FingerTrackingStatus
	{
		FINGER_INACTIVE = 0,			// The hand or finger is not tracked
		FINGER_DETECTED = 1,			// The hand or finger is detected for the first time
		FINGER_TRACKED = 2,				// The hand or finger is tracked
		FINGER_EXTRAPOLATED = 3			// Unused
	};

	// Hand side
	enum HandSide
	{
		HAND_UNKNOWN = 0,
		HAND_LEFT = 1,
		HAND_RIGHT = 2
	};

	// Hand Position
	struct HandPosition
	{
		float										fX;
		float										fY;
		float										fZ;
	};

	// Hand tip
	struct HandTip
	{
		float										fX;
		float										fY;
		float										fZ;
	};

	// Finger tip
	struct FingerTip
	{
		float										fX;
		float										fY;
		float										fZ;
	};

	// One finger struct
	struct Finger
	{
		FingerTrackingStatus						tTrackingStatus;
		FingerTip									sTip;
	};

	// One hand struct
	struct Hand
	{
		HandTrackingStatus							tTrackingStatus;
		HandOpenStatus								tOpenStatus;
		HandSide									tSide;
		HandPosition								sPosition;
		std::string									strHandGesture;
		HandTip										sTip;
		Finger										sFingers[FINGER_COUNT];
		std::string 								strMovingGestureEvent;

	};

	// Overall hand gesture analysis output
	struct HandGestureOutput
	{
		Hand										sHands[HAND_COUNT];

	};
}

#endif //__FANCI_USER_SENSING_API_TYPES__
