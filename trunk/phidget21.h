#ifdef __cplusplus 
extern "C" { 
#endif 

typedef struct _CPhidget CPhidget, *CPhidgetHandle;

__declspec (dllimport)
     int __stdcall CPhidget_open (CPhidgetHandle phid, int serialNumber);
__declspec (dllimport)
     int __stdcall CPhidget_close (CPhidgetHandle phid);
__declspec (dllimport)
     int __stdcall CPhidget_delete (CPhidgetHandle phid);
__declspec (dllimport)
     int __stdcall CPhidget_set_OnDetach_Handler (CPhidgetHandle, int (__stdcall * fptr) (CPhidgetHandle, void *), void *userPtr);
__declspec (dllimport)
     int __stdcall CPhidget_set_OnAttach_Handler (CPhidgetHandle, int (__stdcall * fptr) (CPhidgetHandle, void *), void *userPtr);
__declspec (dllimport)
     int __stdcall CPhidget_set_OnError_Handler (CPhidgetHandle phid, int (__stdcall * fptr) (CPhidgetHandle, void *, int, const char *), void *userPtr);
__declspec (dllimport)
     int __stdcall CPhidget_getDeviceName (CPhidgetHandle phid, const char **buffer);
__declspec (dllimport)
     int __stdcall CPhidget_getSerialNumber (CPhidgetHandle phid, int *serialNumber);
__declspec (dllimport)
     int __stdcall CPhidget_getDeviceVersion (CPhidgetHandle phid, int *devVer);
__declspec (dllimport)
     int __stdcall CPhidget_getDeviceStatus (CPhidgetHandle phid, int *status);
__declspec (dllimport)
     int __stdcall CPhidget_getLibraryVersion (const char **buffer);
__declspec (dllimport)
     int __stdcall CPhidget_getDeviceType (CPhidgetHandle phid, const char **buffer);
__declspec (dllimport)
     int __stdcall CPhidget_getDeviceLabel (CPhidgetHandle phid, const char **buffer);
__declspec (dllimport)
     int __stdcall CPhidget_setDeviceLabel (CPhidgetHandle phid, const char *buffer);
__declspec (dllimport)
     int __stdcall CPhidget_getErrorDescription (int ErrorCode, const char **buf);
__declspec (dllimport)
     int __stdcall CPhidget_waitForAttachment (CPhidgetHandle phid, int milliseconds);
__declspec (dllimport)
     int __stdcall CPhidget_getServerID (CPhidgetHandle phid, const char **serverID);
__declspec (dllimport)
     int __stdcall CPhidget_getServerAddress (CPhidgetHandle phid, const char **address, int *port);

     typedef enum
     {
      PHIDGET_DICTIONARY_VALUE_CHANGED = 1,
      PHIDGET_DICTIONARY_ENTRY_ADDED,
      PHIDGET_DICTIONARY_ENTRY_REMOVING,
      PHIDGET_DICTIONARY_CURRENT_VALUE
     } CPhidgetDictionary_keyChangeReason;

     typedef struct _CPhidgetDictionary __CPhidgetDictionary;
     typedef __CPhidgetDictionary *CPhidgetDictionaryHandle;
     typedef struct _CPhidgetDictionaryListener __CPhidgetDictionaryListener;
     typedef __CPhidgetDictionaryListener *CPhidgetDictionaryListenerHandle;

__declspec (dllimport)
     int __stdcall CPhidgetDictionary_create (CPhidgetDictionaryHandle * dict);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_close (CPhidgetDictionaryHandle dict);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_delete (CPhidgetDictionaryHandle dict);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_set_OnError_Handler (CPhidgetDictionaryHandle dict, int (__stdcall * fptr) (CPhidgetDictionaryHandle, void *, int, const char *), void *userPtr);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_addKey (CPhidgetDictionaryHandle dict, const char *key, const char *val, int persistent);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_removeKey (CPhidgetDictionaryHandle dict, const char *pattern);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_set_OnKeyChange_Handler (CPhidgetDictionaryHandle dict, CPhidgetDictionaryListenerHandle * dictlistener, const char *pattern,
                                                               int (__stdcall * fptr) (CPhidgetDictionaryHandle dict, void *userPtr, const char *key, const char *val,
                                                                                       CPhidgetDictionary_keyChangeReason reason), void *userPtr);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_remove_OnKeyChange_Handler (CPhidgetDictionaryListenerHandle keylistener);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_getKey (CPhidgetDictionaryHandle dict, const char *key, const char *val, int valsize);

     typedef struct _CPhidgetManager __CPhidgetManager;
     typedef __CPhidgetManager *CPhidgetManagerHandle;

__declspec (dllimport)
     int __stdcall CPhidgetManager_create (CPhidgetManagerHandle * phidm);
__declspec (dllimport)
     int __stdcall CPhidgetManager_open (CPhidgetManagerHandle phidm);
__declspec (dllimport)
     int __stdcall CPhidgetManager_close (CPhidgetManagerHandle phidm);
__declspec (dllimport)
     int __stdcall CPhidgetManager_delete (CPhidgetManagerHandle phidm);
__declspec (dllimport)
     int __stdcall CPhidgetManager_set_OnAttach_Handler (CPhidgetManagerHandle phidm, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *);
__declspec (dllimport)
     int __stdcall CPhidgetManager_set_OnDetach_Handler (CPhidgetManagerHandle phidm, int (__stdcall * fptr) (CPhidgetHandle phid, void *userPtr), void *);
__declspec (dllimport)
     int __stdcall CPhidgetManager_getAttachedDevices (CPhidgetManagerHandle phidm, CPhidgetHandle * phidArray[], int *count);
__declspec (dllimport)
     int __stdcall CPhidgetManager_set_OnError_Handler (CPhidgetManagerHandle phidm, int (__stdcall * fptr) (CPhidgetManagerHandle, void *, int, const char *), void *userPtr);

__declspec (dllimport)
     int __stdcall CPhidget_openRemote (CPhidgetHandle phid, int serial, const char *serverID, const char *passWord);
__declspec (dllimport)
     int __stdcall CPhidget_openRemoteIP (CPhidgetHandle phid, int serial, const char *addr, int port, const char *passWord);
__declspec (dllimport)
     int __stdcall CPhidgetManager_openRemoteIP (CPhidgetManagerHandle phidm, const char *address, int port, const char *password);
__declspec (dllimport)
     int __stdcall CPhidgetManager_openRemote (CPhidgetManagerHandle phidm, const char *serverID, const char *passWord);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_openRemoteIP (CPhidgetDictionaryHandle dict, const char *address, int port, const char *password);
__declspec (dllimport)
     int __stdcall CPhidgetDictionary_openRemote (CPhidgetDictionaryHandle dict, const char *serverID, const char *passWord);

     typedef struct _CPhidgetAccelerometer __CPhidgetAccelerometer;
     typedef __CPhidgetAccelerometer *CPhidgetAccelerometerHandle;

__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_create (CPhidgetAccelerometerHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_getAccelerationChangeTrigger (CPhidgetAccelerometerHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_setAccelerationChangeTrigger (CPhidgetAccelerometerHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_getNumAxis (CPhidgetAccelerometerHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_getAcceleration (CPhidgetAccelerometerHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAccelerometer_set_OnAccelerationChange_Handler (CPhidgetAccelerometerHandle, int (__stdcall * fptr) (CPhidgetAccelerometerHandle, void *, int, double), void *);

     typedef struct _CPhidgetAdvancedServo __CPhidgetAdvancedServo;
     typedef __CPhidgetAdvancedServo *CPhidgetAdvancedServoHandle;

__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_create (CPhidgetAdvancedServoHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_getNumMotors (CPhidgetAdvancedServoHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_getAcceleration (CPhidgetAdvancedServoHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_setAcceleration (CPhidgetAdvancedServoHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_getMaxVelocity (CPhidgetAdvancedServoHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_setMaxVelocity (CPhidgetAdvancedServoHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_getMotorPosition (CPhidgetAdvancedServoHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_setMotorPosition (CPhidgetAdvancedServoHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_getCurrent (CPhidgetAdvancedServoHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetAdvancedServo_set_OnPositionChange_Handler (CPhidgetAdvancedServoHandle, int (__stdcall * fptr) (CPhidgetAdvancedServoHandle, void *, int, double), void *);

     typedef struct _CPhidgetEncoder __CPhidgetEncoder;
     typedef __CPhidgetEncoder *CPhidgetEncoderHandle;

__declspec (dllimport)
     int __stdcall CPhidgetEncoder_create (CPhidgetEncoderHandle *);

__declspec (dllimport)
     int __stdcall CPhidgetEncoder_getEncoderPosition (CPhidgetEncoderHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetEncoder_setEncoderPosition (CPhidgetEncoderHandle, int Index, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetEncoder_getNumInputs (CPhidgetEncoderHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetEncoder_getNumEncoders (CPhidgetEncoderHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetEncoder_getInputState (CPhidgetEncoderHandle, int Index, int *pVal);

__declspec (dllimport)
     int __stdcall CPhidgetEncoder_set_OnInputChange_Handler (CPhidgetEncoderHandle, int (__stdcall * fptr) (CPhidgetEncoderHandle, void *, int, int), void *);

__declspec (dllimport)
     int __stdcall CPhidgetEncoder_set_OnPositionChange_Handler (CPhidgetEncoderHandle, int (__stdcall * fptr) (CPhidgetEncoderHandle, void *, int, int, int), void *);

     typedef struct _CPhidgetGPS __CPhidgetGPS;
     typedef __CPhidgetGPS *CPhidgetGPSHandle;

     struct __GPSTime
     {
      short tm_sec, tm_min, tm_hour;
     } typedef GPSTime;
     struct __GPSDate
     {
      short tm_mday, tm_mon, tm_year;
     } typedef GPSDate;

     struct __GPSSatInfo
     {
      short ID;
      short elevation;
      int azimuth;
      short SNR;
     } typedef GPSSatInfo;

     struct __GPGGA
     {
      GPSTime time;
      double latitude;
      double longitude;
      short fixQuality;
      short numSatellites;
      double horizontalDilution;
      double altitude;
      double heightOfGeoid;
     } typedef GPGGA;

     struct __GPGSA
     {
      char mode;

      short fixType;

      short satUsed[12];

      double posnDilution;
      double horizDilution;
      double vertDilution;
     } typedef GPGSA;

     struct __GPGSV
     {
      short satsInView;
      GPSSatInfo satInfo[12];
     } typedef GPGSV;

     struct __GPRMC
     {
      GPSTime time;
      char status;
      double latitude;
      double longitude;
      double speed;
      double heading;
      GPSDate date;
      double magneticVariation;
     } typedef GPRMC;

     struct __GPSInfo
     {
      GPGGA GGA;
      GPGSA GSA;
      GPGSV GSV;
      GPRMC RMC;
     } typedef GPSInfo;

__declspec (dllimport)
     int __stdcall CPhidgetGPS_create (CPhidgetGPSHandle *);

__declspec (dllimport)
     int __stdcall CPhidgetGPS_getLatitude (CPhidgetGPSHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_getLongitude (CPhidgetGPSHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_getAltitude (CPhidgetGPSHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_getTime (CPhidgetGPSHandle, GPSTime * pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_getRawData (CPhidgetGPSHandle, GPSInfo * pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_getPositionChangeTrigger (CPhidgetGPSHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_setPositionChangeTrigger (CPhidgetGPSHandle, double newVal);

__declspec (dllimport)
     int __stdcall CPhidgetGPS_set_OnPositionChange_Handler (CPhidgetGPSHandle, int (__stdcall * fptr) (CPhidgetGPSHandle, void *, double, double, double), void *);
__declspec (dllimport)
     int __stdcall CPhidgetGPS_set_OnNMEAData_Handler (CPhidgetGPSHandle, int (__stdcall * fptr) (CPhidgetGPSHandle, void *, const char *), void *);

     typedef struct _CPhidgetGyroscope __CPhidgetGyroscope;
     typedef __CPhidgetGyroscope *CPhidgetGyroscopeHandle;

__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_create (CPhidgetGyroscopeHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_getAngularRateChangeTrigger (CPhidgetGyroscopeHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_setAngularRateChangeTrigger (CPhidgetGyroscopeHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_getNumAxis (CPhidgetGyroscopeHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_getAngularRate (CPhidgetGyroscopeHandle, int Index, double *pVal);

__declspec (dllimport)
     int __stdcall CPhidgetGyroscope_set_OnAngularRateChange_Handler (CPhidgetGyroscopeHandle, int (__stdcall * fptr) (CPhidgetGyroscopeHandle, void *, int, double), void *);

     typedef struct _CPhidgetInterfaceKit __CPhidgetInterfaceKit;
     typedef __CPhidgetInterfaceKit *CPhidgetInterfaceKitHandle;

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_create (CPhidgetInterfaceKitHandle *);

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getOutputState (CPhidgetInterfaceKitHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_setOutputState (CPhidgetInterfaceKitHandle, int Index, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getSensorChangeTrigger (CPhidgetInterfaceKitHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_setSensorChangeTrigger (CPhidgetInterfaceKitHandle, int Index, int newVal);

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getNumInputs (CPhidgetInterfaceKitHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getNumOutputs (CPhidgetInterfaceKitHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getNumSensors (CPhidgetInterfaceKitHandle, int *pVal);

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getInputState (CPhidgetInterfaceKitHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getSensorValue (CPhidgetInterfaceKitHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getSensorRawValue (CPhidgetInterfaceKitHandle, int Index, int *pVal);

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_getRatiometric (CPhidgetInterfaceKitHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_setRatiometric (CPhidgetInterfaceKitHandle, int newVal);

__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_set_OnInputChange_Handler (CPhidgetInterfaceKitHandle, int (__stdcall * fptr) (CPhidgetInterfaceKitHandle, void *, int, int), void *);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_set_OnOutputChange_Handler (CPhidgetInterfaceKitHandle, int (__stdcall * fptr) (CPhidgetInterfaceKitHandle, void *, int, int), void *);
__declspec (dllimport)
     int __stdcall CPhidgetInterfaceKit_set_OnSensorChange_Handler (CPhidgetInterfaceKitHandle, int (__stdcall * fptr) (CPhidgetInterfaceKitHandle, void *, int, int), void *);

     typedef struct _CPhidgetLED __CPhidgetLED;
     typedef __CPhidgetLED *CPhidgetLEDHandle;

__declspec (dllimport)
     int __stdcall CPhidgetLED_create (CPhidgetLEDHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetLED_getNumLEDs (CPhidgetLEDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetLED_getDiscreteLED (CPhidgetLEDHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetLED_setDiscreteLED (CPhidgetLEDHandle, int Index, int newVal);

     typedef struct _CPhidgetMotorControl __CPhidgetMotorControl;
     typedef __CPhidgetMotorControl *CPhidgetMotorControlHandle;

__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_create (CPhidgetMotorControlHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_getNumInputs (CPhidgetMotorControlHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_getNumMotors (CPhidgetMotorControlHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_getInputState (CPhidgetMotorControlHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_getAcceleration (CPhidgetMotorControlHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_setAcceleration (CPhidgetMotorControlHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_getMotorSpeed (CPhidgetMotorControlHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_setMotorSpeed (CPhidgetMotorControlHandle, int Index, double newVal);

__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_set_OnInputChange_Handler (CPhidgetMotorControlHandle, int (__stdcall * fptr) (CPhidgetMotorControlHandle, void *, int, int), void *);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_set_OnMotorChange_Handler (CPhidgetMotorControlHandle, int (__stdcall * fptr) (CPhidgetMotorControlHandle, void *, int, double), void *);
__declspec (dllimport)
     int __stdcall CPhidgetMotorControl_set_OnCurrentChange_Handler (CPhidgetMotorControlHandle, int (__stdcall * fptr) (CPhidgetMotorControlHandle, void *, int, double), void *);

     typedef struct _CPhidgetPHSensor __CPhidgetPHSensor;
     typedef __CPhidgetPHSensor *CPhidgetPHSensorHandle;

__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_create (CPhidgetPHSensorHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_getPH (CPhidgetPHSensorHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_getPotential (CPhidgetPHSensorHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_getPHChangeTrigger (CPhidgetPHSensorHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_setPHChangeTrigger (CPhidgetPHSensorHandle, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetPHSensor_set_OnPHChange_Handler (CPhidgetPHSensorHandle, int (__stdcall * fptr) (CPhidgetPHSensorHandle, void *, double), void *);

     typedef struct _CPhidgetRFID __CPhidgetRFID;
     typedef __CPhidgetRFID *CPhidgetRFIDHandle;
__declspec (dllimport)
     int __stdcall CPhidgetRFID_create (CPhidgetRFIDHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_getNumOutputs (CPhidgetRFIDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_getOutputState (CPhidgetRFIDHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_setOutputState (CPhidgetRFIDHandle, int Index, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_getAntennaOn (CPhidgetRFIDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_setAntennaOn (CPhidgetRFIDHandle, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_getLEDOn (CPhidgetRFIDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_setLEDOn (CPhidgetRFIDHandle, int newVal);

__declspec (dllimport)
     int __stdcall CPhidgetRFID_set_OnOutputChange_Handler (CPhidgetRFIDHandle, int (__stdcall * fptr) (CPhidgetRFIDHandle, void *, int, int), void *);

__declspec (dllimport)
     int __stdcall CPhidgetRFID_getLastTag (CPhidgetRFIDHandle, unsigned char *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_set_OnTag_Handler (CPhidgetRFIDHandle, int (__stdcall * fptr) (CPhidgetRFIDHandle, void *, unsigned char *), void *);
__declspec (dllimport)
     int __stdcall CPhidgetRFID_set_OnTagLost_Handler (CPhidgetRFIDHandle, int (__stdcall * fptr) (CPhidgetRFIDHandle, void *, unsigned char *), void *);

     typedef struct _CPhidgetServo __CPhidgetServo;
     typedef __CPhidgetServo *CPhidgetServoHandle;

__declspec (dllimport)
     int __stdcall CPhidgetServo_create (CPhidgetServoHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetServo_getNumMotors (CPhidgetServoHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetServo_getMotorPosition (CPhidgetServoHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetServo_setMotorPosition (CPhidgetServoHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetServo_set_OnMotorPositionChange_Handler (CPhidgetServoHandle, int (__stdcall * fptr) (CPhidgetServoHandle, void *, int, double), void *);

     typedef struct _CPhidgetStepper __CPhidgetStepper;
     typedef __CPhidgetStepper *CPhidgetStepperHandle;

__declspec (dllimport)
     int __stdcall CPhidgetStepper_create (CPhidgetStepperHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getNumInputs (CPhidgetStepperHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getNumMotors (CPhidgetStepperHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getInputState (CPhidgetStepperHandle, int Index, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getAcceleration (CPhidgetStepperHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_setAcceleration (CPhidgetStepperHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getMotorSpeed (CPhidgetStepperHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_setMotorSpeed (CPhidgetStepperHandle, int Index, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_getMotorPosition (CPhidgetStepperHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_setMotorPosition (CPhidgetStepperHandle, int Index, double newVal);

__declspec (dllimport)
     int __stdcall CPhidgetStepper_set_OnInputChange_Handler (CPhidgetStepperHandle, int (__stdcall * fptr) (CPhidgetStepperHandle, void *, int, int), void *);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_set_OnPositionChange_Handler (CPhidgetStepperHandle, int (__stdcall * fptr) (CPhidgetStepperHandle, void *, int, double), void *);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_set_OnTorqueChange_Handler (CPhidgetStepperHandle, int (__stdcall * fptr) (CPhidgetStepperHandle, void *, int, double), void *);
__declspec (dllimport)
     int __stdcall CPhidgetStepper_set_OnSpeedChange_Handler (CPhidgetStepperHandle, int (__stdcall * fptr) (CPhidgetStepperHandle, void *, int, double), void *);

     typedef struct _CPhidgetTemperatureSensor __CPhidgetTemperatureSensor;
     typedef __CPhidgetTemperatureSensor *CPhidgetTemperatureSensorHandle;

__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_create (CPhidgetTemperatureSensorHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_getNumTemperatureInputs (CPhidgetTemperatureSensorHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_getTemperature (CPhidgetTemperatureSensorHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_getTemperatureChangeTrigger (CPhidgetTemperatureSensorHandle, int Index, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_setTemperatureChangeTrigger (CPhidgetTemperatureSensorHandle, int Index, double newVal);

__declspec (dllimport)
     int __stdcall CPhidgetTemperatureSensor_set_OnTemperatureChange_Handler (CPhidgetTemperatureSensorHandle, int (__stdcall * fptr) (CPhidgetTemperatureSensorHandle, void *, int, double), void *);

     typedef struct _CPhidgetTextLCD __CPhidgetTextLCD;
     typedef __CPhidgetTextLCD *CPhidgetTextLCDHandle;

__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_create (CPhidgetTextLCDHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getNumRows (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getNumColumns (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getBacklight (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setBacklight (CPhidgetTextLCDHandle, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getContrast (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setContrast (CPhidgetTextLCDHandle, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getCursorOn (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setCursorOn (CPhidgetTextLCDHandle, int newVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_getCursorBlink (CPhidgetTextLCDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setCursorBlink (CPhidgetTextLCDHandle, int newVal);

__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setCustomCharacter (CPhidgetTextLCDHandle, int Index, int Val1, int Val2);

__declspec (dllimport)
     int __stdcall CPhidgetTextLCD_setDisplayString (CPhidgetTextLCDHandle, int Row, char *displayString);

     typedef struct _CPhidgetTextLED __CPhidgetTextLED;
     typedef __CPhidgetTextLED *CPhidgetTextLEDHandle;

__declspec (dllimport)
     int __stdcall CPhidgetTextLED_create (CPhidgetTextLEDHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetTextLED_getNumRows (CPhidgetTextLEDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLED_getNumColumns (CPhidgetTextLEDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLED_getBrightness (CPhidgetTextLEDHandle, int *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetTextLED_setBrightness (CPhidgetTextLEDHandle, int newVal);

__declspec (dllimport)
     int __stdcall CPhidgetTextLED_setDisplayString (CPhidgetTextLEDHandle, int Row, char *displayString);

     typedef struct _CPhidgetWeightSensor __CPhidgetWeightSensor;
     typedef __CPhidgetWeightSensor *CPhidgetWeightSensorHandle;

__declspec (dllimport)
     int __stdcall CPhidgetWeightSensor_create (CPhidgetWeightSensorHandle *);
__declspec (dllimport)
     int __stdcall CPhidgetWeightSensor_getWeight (CPhidgetWeightSensorHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetWeightSensor_getWeightChangeTrigger (CPhidgetWeightSensorHandle, double *pVal);
__declspec (dllimport)
     int __stdcall CPhidgetWeightSensor_setWeightChangeTrigger (CPhidgetWeightSensorHandle, double newVal);
__declspec (dllimport)
     int __stdcall CPhidgetWeightSensor_set_OnWeightChange_Handler (CPhidgetWeightSensorHandle, int (__stdcall * fptr) (CPhidgetWeightSensorHandle, void *, double), void *);
#ifdef __cplusplus 
} 
#endif 
