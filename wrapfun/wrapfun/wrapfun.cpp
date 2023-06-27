#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "comm/datalayer/datalayer.h"
#include "comm/datalayer/datalayer_system.h"
#include "shared_lib.h"

SharedLib Toast("192.168.1.1", "boschrexroth", "boschrexroth", 443);

extern "C" {
    __declspec(dllexport) const char* Connectstring(const char* ip, const char* user, const char* password,int myPort) {
        const char* a = Toast.getConnectionString(ip,user,password,443);
        return a;
    }
    __declspec(dllexport) const char* read(const char* str, const char* corepipe) {
        //comm::datalayer::IClient* client = Toast.Connectclient();
        Toast.Connectclient(corepipe);
        const char* b = "";
        b = Toast.Readclient(str);
        return b;
    }
    __declspec(dllexport) void Looseclient() {
        Toast.Deleteclient();
    }
    
}

