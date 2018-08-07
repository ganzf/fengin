//
// Created by clara on 1/12/18.
//

#ifdef _WIN32
# include <filesystem>
#endif
#include <experimental/filesystem>
#include <regex>
#include <string>
#include "AssetLoader.hpp"

namespace fengin::systems::SFMLSystems
{
    void AssetLoader::init() {
        __init();
        addReaction<RequestAssets>([this](futils::IMediatorPacket &pkg){
            const auto &packet = futils::Mediator::rebuild<RequestAssets>(pkg);
            if (packet.absolutePaths)
                events->send<std::string>("Assets requested with absolute paths...");
            else
                events->send<std::string>("Assets requested...");
            AssetsLoaded assets;
            assets.fonts = &_fonts;
            assets.textures = &_textures;
            events->send<std::string>("Sending assets...");
            events->send<AssetsLoaded>(assets);
            events->send<std::string>("Done.");
        });

        addReaction<RequestTexture>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RequestTexture>(pkg);
            packet.call(&_textures[packet.path]);
        });

        std::regex patternTexture { ".*.[png|jpg|jpeg]" };
        std::regex patternFont { ".*.ttf" };
        // TODO: Make it easier to set the resources folder
        std::string assetDir = "resources/";

        try {
            std::experimental::filesystem::path path{assetDir.c_str()};
            if (std::experimental::filesystem::exists(path)) {
                std::string pathFile;
                for (auto &p : std::experimental::filesystem::recursive_directory_iterator(path)) {

                    pathFile = p.path().string();

                    std::string file = p.path().string();
                    file.erase(0, assetDir.size());

                    if (std::regex_match(file, patternTexture)) {
                        sf::Texture texture;
                        if (!texture.loadFromFile(pathFile)) {
//                            events->send<std::string>("Texture [" + file + "] not found.");
                            continue;
                        }
                        _textures[file] = texture;
                        events->send<std::string>("Texture [" + file + "] loaded.");
                    } else if (std::regex_match(file, patternFont)) {
                        sf::Font font;
                        if (!font.loadFromFile(pathFile)) {
                            //events->send<std::string>("\e[31m ☒ \e[00m Font \"" + file->d_name + "\" not found.");
                            continue;
                        }
                        events->send<std::string>("Font " + file + " loaded.");
                        _fonts[file] = font;
                    }
                }
            } else {
                events->send<std::string>("[Warning] Could not load assets from unexisting directory " + assetDir);
            }
        }
        catch (...) {
            std::cerr << "Something went wrong in SFMLAssetLoader" << std::endl;
            return ;
        }
        phase = Run;
    }

    void AssetLoader::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
