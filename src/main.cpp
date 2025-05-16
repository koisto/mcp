
#include <iostream>
#include <string>

#include "util.h"
#include "mcp_server.h"



int main(int argc, char **argv)
{
    mcp_server mcp("my mcp server", "0.0.1");

    log_msg("MCP Server started.\n");

    std::string msg;
    while (std::getline(std::cin, msg))
    {
        //msg = R"({"test":1})";
        std::cout << mcp.parse_request(msg) << std::endl;
    }

    return 0;
}