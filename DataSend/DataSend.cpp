//// Copyright (c) 2010-2018 Lockheed Martin Corporation. All rights reserved.
//// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT
////------------------------------------------------------------------------------
////
////  SimConnect Set Data Sample
//// 
////	Description:
////				When Ctrl-Shift-A is pressed, the user aircraft is moved
////				to a new location. When Ctrl+Shift+B is pressed, landing
////              lights are turned on, AMBIENT WIND VELOCITY are increased, and
////              the main exit is opened halfway.
////------------------------------------------------------------------------------
//
//#include <windows.h>
//#include <tchar.h>
//#include <stdio.h>
//#include "SimConnect.h"
//#include <strsafe.h>
//
//int     quit = 0;
//HANDLE  hSimConnect = NULL;
//
//enum GROUP_ID {
//	GROUP_INIT,
//	GROUP_STRUCT,
//};
//
//enum INPUT_ID {
//	INPUT_INIT,
//	INPUT_STRUCT,
//};
//
//enum EVENT_ID {
//	EVENT_SIM_START,
//	EVENT_INIT,
//	EVENT_STRUCT,
//};
//
//enum DATA_DEFINE_ID {
//	DEFINITION_INIT,
//	DEFINITION_STRUCT,
//};
//
//// Custom struct used to demonstrate setting different data types.
//
////struct CustomStruct
////{
////	BOOL    LandingLight;   // SIMCONNECT_DATATYPE_INT32
////	float   Health;         // SIMCONNECT_DATATYPE_FLOAT32
////	double  Exit;           // SIMCONNECT_DATATYPE_FLOAT64
////};
//struct CustomStruct
//{
//	BOOL    LandingLight;   // SIMCONNECT_DATATYPE_INT32
//	double  dWindVelocity;         // SIMCONNECT_DATATYPE_FLOAT32
//	double  dWindDirection;           // SIMCONNECT_DATATYPE_FLOAT64
//};
//
//
//
//void CALLBACK MyDispatchProcSD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
//{
//	HRESULT hr;
//
//	switch (pData->dwID)
//	{
//	case SIMCONNECT_RECV_ID_EVENT:
//	{
//		SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;
//
//		switch (evt->uEventID)
//		{
//		case EVENT_SIM_START:
//		{
//			// Turn the input events on now
//			hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_INIT, SIMCONNECT_STATE_ON);
//			hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_STRUCT, SIMCONNECT_STATE_ON);
//		}
//		break;
//
//		case EVENT_INIT:
//		{
//			SIMCONNECT_DATA_INITPOSITION Init;
//			Init.Altitude = 5000.0;
//			Init.Latitude = 47.64210;
//			Init.Longitude = -122.13010;
//			Init.Pitch = 0.0;
//			Init.Bank = -1.0;
//			Init.Heading = 180.0;
//			Init.OnGround = 0;
//			Init.Airspeed = 60;
//			hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_INIT, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(Init), &Init);
//
//			printf("\nEVENT_INIT received and data sent");
//		}
//		break;
//
//		case EVENT_STRUCT:
//		{
//			CustomStruct Struct;
//			Struct.LandingLight = 1;
//			Struct.dWindVelocity = 100.0f;
//			Struct.dWindDirection = 270;
//			hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_STRUCT, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(Struct), &Struct);
//
//			printf("\nEVENT_STRUCT received and data sent");
//		}
//		break;
//
//		default:
//			break;
//		}
//		break;
//	}
//
//	case SIMCONNECT_RECV_ID_QUIT:
//	{
//		quit = 1;
//		break;
//	}
//
//	default:
//		printf("\nReceived:%d", pData->dwID);
//		break;
//	}
//}
//
//void testDataSet()
//{
//	HRESULT hr;
//
//	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Set Data", NULL, 0, 0, 0)))
//	{
//		printf("\nConnected to Prepar3D!");
//
//		// Set up a data definition for positioning data
//		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_INIT, "INITIAL POSITION", NULL, SIMCONNECT_DATATYPE_INITPOSITION);
//
//		// Set up data definition for a custom struct with different data types
//		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_STRUCT, "LIGHT LANDING", NULL, SIMCONNECT_DATATYPE_INT32);
//		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_STRUCT, "AMBIENT WIND VELOCITY", NULL, SIMCONNECT_DATATYPE_FLOAT64);
//		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_STRUCT, "AMBIENT WIND DIRECTION", NULL, SIMCONNECT_DATATYPE_FLOAT64);
//
//		// Request a simulation start event
//		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");
//
//		// Create custom events
//		hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_INIT, "My.CTRLSHIFTA");
//		hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_STRUCT, "My.CTRLSHIFTB");
//
//		// Link the custom event to some keyboard keys, and turn the input event off
//		hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_INIT, "Ctrl+Shift+A", EVENT_INIT);
//		hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_INIT, SIMCONNECT_STATE_OFF);
//		hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_STRUCT, "Ctrl+Shift+B", EVENT_STRUCT);
//		hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_STRUCT, SIMCONNECT_STATE_OFF);
//
//		// Sign up for notifications for EVENT_INIT and EVENT_STRUCT
//		hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_INIT, EVENT_INIT);
//		hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_STRUCT, EVENT_STRUCT);
//
//		while (0 == quit)
//		{
//			SimConnect_CallDispatch(hSimConnect, MyDispatchProcSD, NULL);
//			Sleep(1);
//		}
//
//		hr = SimConnect_Close(hSimConnect);
//	}
//}
//
//int __cdecl _tmain(int argc, _TCHAR* argv[])
//{
//
//	testDataSet();
//
//	return 0;
//}
