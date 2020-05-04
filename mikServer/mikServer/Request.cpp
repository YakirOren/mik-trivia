#include "Request.h"

void DataSerialization::deserialize(const json& j, GeneralRequest& response)
{
    j.at("op").get_to(response.code);
    response.data = j["d"].get<json>();
}

void DataSerialization::serialize(json& j, const GeneralRequest& response)
{
    j = json{ {"op", response.code}, {"d", response.data} };
}
