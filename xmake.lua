add_rules("mode.debug", "mode.release")
set_allowedarchs("windows|x64")
set_defaultarchs("windows|x64")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("MiF-repo https://github.com/MiracleForest/xmake-repo.git")

-- Dependencies from xmake-repo.
add_requires("fmt")
add_requires("magic_enum")
add_requires("nlohmann_json")

-- Dependencies from liteldev-repo.
add_requires("levilamina 0.13.4")

-- Dependencies from MiF-repo.
add_requires("iFamily")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("iMinecraft")
    add_cxflags(
        "/EHa",
        "/utf-8",
        "/W4",
        "/w44265",
        "/w44289",
        "/w44296",
        "/w45263",
        "/w44738",
        "/w45204"
    )
    add_defines("NOMINMAX", "UNICODE")
    add_headerfiles("src/**.h")
    add_files("src/**.cpp")
    add_includedirs("src")
    add_packages(
		"levilamina",
 		"fmt",
        "magic_enum",
        "nlohmann_json",
        "iFamily"
    )
    add_shflags("/DELAYLOAD:bedrock_server.dll") -- To use symbols provided by SymbolProvider.
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")

    if is_mode("debug") then
        add_defines("iMINECRAFT_DEBUG")
    end
    
    after_build(function (target)
        local plugin_packer = import("scripts.after_build")

        local tag = os.iorun("git describe --tags --abbrev=0 --always")
        local major, minor, patch, suffix = tag:match("v(%d+)%.(%d+)%.(%d+)(.*)")
        if not major then
            print("Failed to parse version tag, using 0.0.0")
            major, minor, patch = 0, 0, 0
        end
        local plugin_define = {
            pluginName = target:name(),
            pluginFile = path.filename(target:targetfile()),
            pluginVersion = major .. "." .. minor .. "." .. patch,
        }
        
        plugin_packer.pack_plugin(target,plugin_define)
    end)
