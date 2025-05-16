#include "json_rpc.h"
#include "util.h"

json_rpc::json_rpc()
{
}

json_rpc::~json_rpc()
{
}

std::string json_rpc::parse_request(const std::string req)
{
    json rpc_version;
    json method;
    json params;
    json id;

    log_msg("Received: %s\n", req.c_str());
    json parsed_msg = json::parse(req.c_str(), nullptr, false);

    // handle parse errors
    if (parsed_msg.is_discarded())
    {
        log_msg("Error. Couldn't parse message\n");
        return build_error_response(JSONRPC_PARSE_ERR, "Parse Error", id);
    }

    // must have these
    if (!parsed_msg.contains("jsonrpc") ||
        !parsed_msg.contains("method"))
    {
        log_msg("Error. Message didn't include \"jsonrpc\" or \"method\".\n");
        return build_error_response(JSONRPC_INVALID_REQUEST_ERR, "Invalid Request", id);
    }

    // deserialise the fields we know about
    rpc_version = parsed_msg.at("jsonrpc");
    method = parsed_msg.at("method");

    if (parsed_msg.contains("params"))
    {
        params = parsed_msg.at("params");
        if (!(params.is_array() || params.is_object()))
        {
             log_msg("Error. \"params\" is not array or object.\n");
            return build_error_response(JSONRPC_INVALID_REQUEST_ERR , "Invalid Request", id);       
        }
    }

    if (parsed_msg.contains("id"))
    {
        id = parsed_msg.at("id");
        if (!(id.is_number_integer() || id.is_string()))
        {
            log_msg("Error. \"id\" is not number or string.\n");
            return build_error_response(JSONRPC_INVALID_REQUEST_ERR , "Invalid Request", id);       
        }
    }

    // sanity check
    if ((rpc_version != "2.0") || 
        (!method.is_string()))
    {
        log_msg("Error. \"jsonrpc\" is not \"2.0\" or \"method\" is not string.\n");
        return build_error_response(JSONRPC_INVALID_REQUEST_ERR , "Invalid Request", id);
    }

    // call the handler then return
    return request_method_handler(method, params, id);
}

std::string json_rpc::request_method_handler(const std::string method, json &params, json &id)
{
    return build_error_response(JSONRPC_METHOD_NOT_FOUND_ERR, "Method not found", id);
}

std::string json_rpc::build_error_response(const int error_code, const std::string message, json &id)
{
    json err_msg;
    err_msg["jsonrpc"] = "2.0";
    err_msg["error"] = {
        {"code" , error_code},
        {"message", message.c_str()},
    };
    err_msg["id"] = id;

    return err_msg.dump();
}

std::string json_rpc::build_result_response(json &result, json &id)
{
    json result_msg;
    result_msg["jsonrpc"] = "2.0";
    result_msg["result"] = result;
    result_msg["id"] = id;

    return result_msg.dump();
}
