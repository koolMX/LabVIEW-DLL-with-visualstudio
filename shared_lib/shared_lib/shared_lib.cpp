#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "comm/datalayer/datalayer.h"
#include "comm/datalayer/datalayer_system.h"
#include "shared_lib.h"

extern "C" {
    __declspec(dllexport) SharedLib::SharedLib(const const char* ip, const const char* user, const char* password, int sslPort)
    {
        _ip = ip;
        _user = user;
        _password = password;
        _sslPort = sslPort;

    }

    __declspec(dllexport) SharedLib::~SharedLib()
    {
        Deleteclient();
    }

    const char* SharedLib::getConnectionString(const char* ip, const char* user, const char* password, int sslPort)
    {
        std::string connectionString = DL_TCP + std::string(user) + ":" + std::string(password) + "@" + std::string(ip);
        if (sslPort == 443)
        {
            return _strdup(connectionString.c_str());
        }

        std::string connection = connectionString + "?sslport=" + std::to_string(sslPort);
        return _strdup(connection.c_str());
    }


    comm::datalayer::IClient* SharedLib::Connectclient(const char* constr)
    {
        if (_client == nullptr) {
            _datalayerSystem.start(false);
           std::string connectionString = "tcp://" + std::string(_user) + ":" + std::string(_password) + "@" + std::string(_ip);
            //std::string connectionString = "tcp://boschrexroth:boschrexroth@192.168.1.1";
            _client = _datalayerSystem.factory()->createClient(std::string(constr));
        }
        if (_client->isConnected())
        {
            std::cout << "client has been generated" << std::endl;
            return _client;
        }

        delete _client;

        return nullptr;
    }

    const char* SharedLib::Readclient(const char* str)
    {
        _output.str("");
        if (_client == nullptr) {
            return nullptr;
        }
        //std::stringstream output;
        //comm::datalayer::Variant data;
        //comm::datalayer::DlResult result;
        _result = _client->readSync(std::string(str), &_data);
        if (_result == comm::datalayer::DlResult::DL_OK) {
            _output << "value at given node address is: " << double(_data) << std::endl;
        }
        else {
            _output << "Reading Datalayernode failed with: " << _result.toString() << std::endl;
        }
        return _strdup(_output.str().c_str());
    }

    void SharedLib::Deleteclient()
    {
        if (_client != nullptr) {
            delete _client;
            _client = nullptr;
        }
    }
}