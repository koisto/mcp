
#include <iostream>
#include <string>

#include "util.h"
#include "json_rpc.h"



int main(int argc, char **argv)
{
    json_rpc rpc;

    log_msg("MCP Server started.\n");

    std::string msg;
    while (std::getline(std::cin, msg))
    {
        //msg = R"({"test":1})";
        std::cout << rpc.parse_request(msg) << std::endl;
    }

    return 0;
}