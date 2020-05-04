#pragma once
#include "json.hpp"

using json = nlohmann::json;

namespace DataSerialization
{
    struct GeneralRequest
    {
        int code;
        json data;
    };

    void deserialize(const json& j, GeneralRequest& response);
    void serialize(json& j, const GeneralRequest& response);
}


