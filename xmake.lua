add_rules("mode.debug", "mode.release")

set_languages("c99", "c++11")

add_requires("raylib", "nlohmann_json")

target("ultrashooter")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_plat("windows") then
        add_ldflags("/subsystem:windows", {force = true})
        add_files("ultrashooter.rc")
    end
    add_packages("raylib", "nlohmann_json")