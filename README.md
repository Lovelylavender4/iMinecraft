# iMinecraft

![iMinecraft](https://socialify.git.ci/Lovelylavender4/Minecraft/image?description=1&font=Raleway&forks=1&issues=1&language=1&name=1&owner=1&pattern=Circuit%20Board&pulls=1&stargazers=1&theme=Auto)

![English](https://img.shields.io/badge/English-inactive?style=for-the-badge)

`iMinecraft` is a Minecraft BDS plugin for modifying features and world generation related content.

> [!IMPORTANT]
>
> The author is in school and may only have a day or two to write and commit code every half month or so!

## Install

## Usage

### Config

#### OverallConfig

When you run the plugin for the first time, it will generate its corresponding configuration file.
The `config.json` file is the overall configuration for the plugin, adhering to standard JSON format.
The default content of `config.json` is as follows:

```json
{
    "debug": false,
    "enable": true,
    "enable_log": true,
    "format_version": 0,
    "path": {
        "features_config": "config/features.json",
        "overall_config": "config/config.json"
    }
}
```

Its counterpart is explained as:

```jsonc
{
    // If true, debug mode is enabled.
    "debug": /* 'true' or 'false' */,
    // If true, the plugin is enabled.
    "enable": /* 'true' or 'false' */,
    // If true, plugin logging is enabled.
    "enable_log": /* 'true' or 'false' */,
    // Formatted version number for backward compatibility
    "format_version": /* 'integer' */,
    // Relative path to the accompanying file
    "path": {
        // Relative path to itself.
        "features_config": /* 'string' */,
        // Relative path to the feature configuration file.
        "overall_config": /* 'string' */
    }
}
```

#### FeaturesConfig

The `features.json` file will be used for configuring world generation and related aspects such as terrain features. The default content of `features.json` is as follows:

```json
{
    "features": {
        "structures": {
            "village": {
                "enable": true,
                "min_town_separation": -1,
                "spawn": true,
                "specified_chunk_position": [],
                "town_spacing": -1
            }
        }
    }
}
```

Its counterpart is explained as:

```jsonc
{
    // Configuration of feature-related.
    "features": {
        // Configuration of structure-related features.
        "structures": {
            // The configuration of features related to villages.
            "village": {
                // Is this sub-configuration allowed?
                "enable": /* 'true' or 'false' */,
                // The setting of minimum town spacing,
                // with -1 indicating the use of the original default spacing.
                "min_town_separation": /* '-1' or integer */,
                // If set to false, village generation will be disabled.
                "spawn": /* 'true' or 'false' */,
                // Operating configuration at a specific chunk coordinate.
                "specified_chunk_position": [
                    /** Example.
                    {
                        // Whether to generate a village at this coordinate.
                        "spawn": 'true' or 'false',
                        // Is this sub-configuration allowed?
                        "enable": 'true' or 'false',
                        // chunk coordinate.
                        "position": [ 'integer', 'integer' ]
                    }
                    */
                ],
                // The setting of town spacing,
                // with -1 indicating the use of the original default spacing.
                "town_spacing": /* '-1' or integer */
            }
        }
    }
}
```

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=Lovelylavender4/Minecraft&type=Date)](https://star-history.com/#Lovelylavender4/Minecraft&Date)

## ⭐Contributing⭐

> [!IMPORTANT]
>
> You can ``contribute`` to the `iMinecraft` project in the following ways
>
> - ⭐ Add new functionality by pulling request contribution code
> - ⭐ Help me modify or optimize documents
> - ⭐ Feedback on [`GitHub Issues`](https://github.com/Lovelylavender4/Minecraft/issues) for problems, suggestions, etc.
> - ⭐ Help us promote `iMinecraft` and support my development!
>
> Very much looking forward to and welcoming your contribution!

`iMinecraft` follows the [Code of Conduct](https://www.contributor-covenant.org/version/2/1/code_of_conduct/).

## Contributors

This project exists thanks to all the people who contribute.

![Contributors](https://contrib.rocks/image?repo=Lovelylavender4/Minecraft)

## License

Copyright © 2024 Lovelylavender4, All rights reserved.

This project is licensed under the LGPL-3.0 License - see the [COPYING](COPYING) and [COPYING.LESSER](COPYING.LESSER) files for details.
