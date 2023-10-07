add_library(weathers Weather.cpp)

target_link_libraries(weathers PRIVATE cpr nlohmann_json)
