//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Revised by Jeroen de Haas on 22/11/2016
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Server.h"

void RunServer() {
	Server server;
	server.startListening(1080);
}

int main(int argc, const char * argv[])
{	
	RunServer();

	_CrtDumpMemoryLeaks();
}
