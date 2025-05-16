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
            json tool_list_result;
            tool_list_result["tools"] = {
                {
                    {"name", "get_time"},
                    {"description", "Gets the current time"},
                    {"inputSchema",{
                        {"type", "object"},
                        {"properties", json::object()},
                        {"required", json::array()}
                    }}
                }
            };

            return build_result_response(tool_list_result, id);
        }
        else if (method == "tools/call")
        {
            // we need a params object for this to work
            if (params.is_object() &&
                params.contains("name"))// && 
                //params.contains("arguments"))
            {
                json tool_name = params.at("name");
                //json tool_args = params.at("arguments");

                json tool_call_response;
                tool_call_response["content"] = {
                    {{"type", "text"},
                    {"text", "12:00:01"}}
                };
                return build_result_response(tool_call_response, id);
            }
            else
            {
                return build_error_response(JSONRPC_INVALID_PARAMS_ERR, "Invalid params", id);
            }
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