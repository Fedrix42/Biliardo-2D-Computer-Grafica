#include "assetmgr.h"
#include <filesystem>

const std::filesystem::path ASSERT_FOLDER = "risorse/";


AssetMGR& AssetMGR::instance()
{
    static AssetMGR instance;
    return instance;
}

AssetMGR::AssetMGR()
{
    loaded_balls_textures.resize(17, false);
    balls.resize(17, nullptr);
    this->table = new sf::Texture(ASSERT_FOLDER / "table.png");
    this->table_pockets = new sf::Texture(ASSERT_FOLDER / "pocket.png");
    this->table_walls = new sf::Texture(ASSERT_FOLDER / "table_wall.png");
}


sf::Texture * AssetMGR::get_ball_texture(unsigned int id)
{
    if(!loaded_balls_textures.at(id)){
        balls.at(id) = new sf::Texture(ASSERT_FOLDER / ("ball_" + std::to_string(id) + ".png"));
        loaded_balls_textures.at(id) = true;
    }
    return balls.at(id);
}

sf::Texture * AssetMGR::table_texture()
{
    return this->table;
}

sf::Texture * AssetMGR::table_pocket_texture()
{
    return this->table_pockets;
}

sf::Texture * AssetMGR::table_wall_texture()
{
    return this->table_walls;
}



