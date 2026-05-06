#include "../../include/core/ScenarioLoader.h"
#include "../../include/core/FlyingObjectFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

static IFFStatus parseIFF(const std::string& s) {
    if (s == "FRIEND") return IFFStatus::FRIEND;
    if (s == "FOE")    return IFFStatus::FOE;
    return IFFStatus::UNKNOWN;
}

void ScenarioLoader::load(const std::string& path, ObjectManager& manager, IFFSystem& iff) {
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("Cannot open scenario file: " + path);

    json j = json::parse(f);

    for (const auto& obj : j["objects"]) {
        int id = obj["id"];
        std::string type = obj["type"];
        Vector2D pos(obj["position"][0].get<double>(), obj["position"][1].get<double>());
        Vector2D vel(obj["velocity"][0].get<double>(), obj["velocity"][1].get<double>());
        double alt = obj["altitude"].get<double>();

        auto flyingObj = FlyingObjectFactory::create(type, id, pos, vel, alt);
        if (flyingObj)
            manager.addObject(std::move(flyingObj));

        if (obj.contains("iff"))
            iff.setStatus(id, parseIFF(obj["iff"].get<std::string>()));
    }
}
