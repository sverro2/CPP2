//
//  Client.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include <string>

class Client {
public:
    Client() {}
    Client(const std::string& name) : name {name} {}

    std::string get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }

private:
    std::string name;
};

#endif Client_hpp
