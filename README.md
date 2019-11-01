# Protibadi App
*(platform: Tizen OS, Tested on: Samsung Galaxy Z1)*
### A Tizen OS based mobile app and IoT for seeking help against harassment 
**How to use it -**
- Pre-requisites
    - An active SIM card should be kept inserted into the phone.
    - The cellular account must have sufficient balance for successfully sending SMS.
    - Location service of the phone should be turned on.
    - For successfully sending email, an email account should be registered with the default email app.
    - Several numbers and email addresses added in the default *Contacts* app; Those numbers and emails will be used to send help message in this current version of Protibadi.
- Running the app
    - Launch **Protibadi BT**.
    - Press *Enable receiver* button. It will then start receiving Bluetooth signal from the signal sender
    - Pressing *Ask for help* button will immediately trigger the app to send *Help* message and email without waiting for Bluetooth signal.
    - SMS will be sent containing the current *Longitude* and *Latitude* of user.
    - Email will be sent containing an embedded Google map link with the current location of user.
- If you don't have the Bluetooth signal sender device
    - Download **ArduDroid** in an Android phone.
    - In the source code (Protibadi - BT/src/user_callbacks.c) , edit the following line (715) and add your Android phone's Bluetooth MAC address in the place of "20:14....." -
```
const char *remote_server_address = "20:14:10:29:02:66"; //comment this line
const char *remote_server_address = "your:phone's:MAC:address"; //add this line
```
- Pair your Tizen phone with Android phone.
- Launch *ArduDroid* and press *connect me to a Bluetooth device* from menu and select your Tizen phone from the list.
- Launch **Protibadi BT** and in your Android Write 'l' (small l) and press the *Send data* button at least 10 times (10 is for ensuring noise less signal, it can be changed)

**Build manual-**
*For the current version, receiver and processor are two different stand alone apps*
- At first build and install the *Protibadi - Processor* project.
- Then, build and install the *Protibadi - BT* project.

**Developers have re-used some fragments of codes from following sources-**
- Bluetooth (Sample app)
- Telephony (Sample app)
- For contacts listing https://developer.tizen.org/dev-guide/2.3.1/org.tizen.native.mobile.apireference/group__
- Examples of API documentations.

**Developers' names-**
1. Md. Asimuzzaman Mansib (@asimuzzaman)
2. Farah Hossain (@farahowo)
