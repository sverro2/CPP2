//
//  ClientCommand.h
//  socketexample
//
//  Created by Bob Polis on 27/11/14.
//  Modified by Jeroen de Haas on 23/11/2016.
//  Copyright (c) 2016 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef __socketexample__ClientCommand__
#define __socketexample__ClientCommand__

#include <string>
#include <memory>
#include "Client.h"

class ClientInfo;


class ClientCommand {
public:
    ClientCommand(const std::string& command_text, std::weak_ptr<ClientInfo> client_info, Client client)
		: cmd{ command_text }, info{ client_info }, _client{ client } {}

    std::string get_cmd() const { return cmd; }
    std::weak_ptr<ClientInfo> get_client_info() const { return info; }
	Client& const GetClient();

private:
    std::string cmd;
    std::weak_ptr<ClientInfo> info;
	Client _client;

};

#endif /* defined(__socketexample__ClientCommand__) */
