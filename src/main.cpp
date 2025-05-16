
#include <iostream>
#include <string>

#include "util.h"
#include "mcp_server.h"

class time_tool: public mcp_server_tool_base
{
public:
    time_tool() : mcp_server_tool_base("get_time", "get the current time")
    {

    }

    ~time_tool()
    {


    }

    json get_schema_properties()
    {
        return json::object();
    }

    json get_schema_required()
    {
        return json::array();
    }


    json do_tool_call(json &params)
    {
        return json::object();
    }
};




int main(int argc, char **argv)
{
    mcp_server mcp("my mcp server", "0.0.1");
    time_tool tt;


    mcp.add_tool(tt);

    log_msg("MCP Server started.\n");

    std::string msg;
    while (std::getline(std::cin, msg))
    {
        //msg = R"({"test":1})";
        std::cout << mcp.parse_request(msg) << std::endl;
    }

    return 0;
}