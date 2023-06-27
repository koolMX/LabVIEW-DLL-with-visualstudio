#pragma once
#include"pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "comm/datalayer/datalayer.h"
#include "comm/datalayer/datalayer_system.h"



#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_FOR_X64
#ifdef _WIN64
#define SHARED_LIB __declspec(dllexport)
#endif
#else
#ifdef _WIN64
#define SHARED_LIB __declspec(dllimport)
#endif
#endif

    class SHARED_LIB SharedLib
    {
    public:
        const char* _ip;
        const char* _user;
        const char* _password;
        int _sslPort;
        std::stringstream _output;
        comm::datalayer::IClient* _client;
        comm::datalayer::DlResult _result;
        comm::datalayer::Variant _data;
        comm::datalayer::DatalayerSystem _datalayerSystem;
        SharedLib(const const char* ip, const const char* user, const char* password, int sslPort);

        const char* getConnectionString(const char* ip, const char* user, const char* password, int sslPort);

        comm::datalayer::IClient* Connectclient(const char* constr);

        const char* Readclient(const char* str);

        void Deleteclient();
        ~SharedLib();
    };

}
#ifdef __cplusplus
#endif