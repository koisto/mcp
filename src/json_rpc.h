#ifndef __JSON_RPC_H__
#define __JSON_RPC_H__

#include "json.hpp"

#include <string>
#include <set>
#include <functional>

using json = nlohmann::json;

#define JSONRPC_PARSE_ERR               -32700 	    // Parse error 	        Invalid JSON was received by the server.
#define JSONRPC_INVALID_REQUEST_ERR     -32600 	    // Invalid Request 	    The JSON sent is not a valid Request object.
#define JSONRPC_METHOD_NOT_FOUND_ERR    -32601 	    // Method not found 	The method does not exist / is not available.
#define JSONRPC_INVALID_PARAMS_ERR      -32602 	    // Invalid params 	    Invalid method parameter(s).
#define JSONRPC_INTERNAL_ERR            -32603 	    // Internal error
#define JSONRPC_SERVER_ERR_MIN          -32000
#define JSONRPC_SERVER_ERR_MAX          -32099

class json_rpc {
public:
    json_rpc();
    virtual ~json_rpc();
    
    std::string parse_request(const std::string msg);

protected: 
    virtual std::string request_method_handler(const std::string method, json &params, json &id);

    std::string build_error_response(const int error_code, const std::string message, json &id);
    std::string build_result_response(json &result, json &id);
};


#endif 