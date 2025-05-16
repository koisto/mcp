#include "mcp_server.h"

mcp_server::mcp_server(const std::string server_name, std::string server_version)
{
    server_info["name"] = server_name;
    server_info["version"] = server_version;
}

mcp_server::~mcp_server()
{
}

std::string mcp_server::request_method_handler(const std::string method, json &params, json &id)
{
    // we need an id for anything that expects a response
    if (!id.is_null())
    {
        if (method == "initialize")
        {
            json init_result;
            init_result["protocolVersion"] = "2024-11-05";
            init_result["capabilities"] = {
                {"tools", 
                    {{"listChanged", false}}
                }
            };

            init_result["serverInfo"] = server_info;
            return build_result_response(init_result, id);
        }
        else if (method == "tools/list")
        {
        
        }
        else if (method == "tools/call")
        {
            
        }
    }
    else
    {
        if (method == "notifications/initialized")
        {
            // do nothing, return an empty string, this is a notification
            return {};
        }
    } 

    return build_error_response(JSONRPC_METHOD_NOT_FOUND_ERR, "Method not found", id);
}