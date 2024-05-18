#pragma once
#define SLASH "/"

#define LL_PLUGINS_ROOT_DIR "plugins/"

#define PLUGIN_NAME                "iMinecraft"
#define PLUGIN_VERSION             "0.0.0"
#define PLUGIN_AUTHOR              "Lovelylavender4"
#define PLUGIN_DESCRIPTION         "A Minecraft BDS Plugin for Modifying Features and World-Related Generation."
#define PLUGIN_WEBSITE             "https://github.com/Lovelylavender4/iMinecraft"
#define PLUGIN_PATH_PREFIX         LL_PLUGINS_ROOT_DIR PLUGIN_NAME SLASH
#define PLUGIN_WORK_DIR            PLUGIN_PATH_PREFIX
#define PLUGIN_OVERALL_CONFIG_FILE "config/config.json"

#define SelfLogger iMinecraft::iMinecraftPlugin::getLogger()
