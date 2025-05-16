#ifndef __MCP_SERVER_H__
#define __MCP_SERVER_H__

#include <map>

#include "json_rpc.h"

class mcp_server_tool_base {
public:
    mcp_server_tool_base(std::string name_, std::string description_);
    virtual ~mcp_server_tool_base();
    
    const std::string name;
    const std::string description;
    
    virtual json get_schema_properties(void) = 0; 
    virtual json get_schema_required(void) = 0; 

    virtual json do_tool_call(json &params) = 0;
};

class mcp_server : public json_rpc
{
public:
    mcp_server(const std::string server_name, std::string server_version);
    virtual ~mcp_server();

    void add_tool(mcp_server_tool_base& tool);

private:
    std::string request_method_handler(const std::string method, json &params, json &id) override;

    json server_info; 

    std::map<std::string, mcp_server_tool_base&> tools;

};


#endif