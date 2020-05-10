#ifndef serverClass_H_
#define serverClass_H_


const char* ssidCredential();
const char* passwordCredential();
int readDHTTemperature();
int readDHTHumidity();
void Serversetup();
void loopServer();
void handle_OnConnect();
void handle_NotFound();

//void website();
// void bigSetUpMethod();
// void bigLoopMethod();

#endif