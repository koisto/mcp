#ifndef __MCP_SERVER_H__
#define __MCP_SERVER_H__

#include "json_rpc.h"

class mcp_server : public json_rpc
{
public:
    mcp_server(const std::string server_name, std::string server_version);
    virtual ~mcp_server();

private:
    std::string request_method_handler(const std::string method, json &params, json &id) override;

    json server_info; 

};


#endif