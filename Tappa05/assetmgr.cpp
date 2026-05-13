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
    background = new sf::Texture(ASSERT_FOLDER / "background.jpg");
    background->setRepeated(true);
    table = new sf::Texture(ASSERT_FOLDER / "table.png");
    table_pockets = new sf::Texture(ASSERT_FOLDER / "pocket.png");
    table_walls = new sf::Texture(ASSERT_FOLDER / "table_wall.png");
    cue = new sf::Texture(ASSERT_FOLDER / "cue.png");
}

sf::Texture * AssetMGR::background_texture()
{
    return background;
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
    return table;
}

sf::Texture * AssetMGR::table_pocket_texture()
{
    return table_pockets;
}

sf::Texture * AssetMGR::table_wall_texture()
{
    return table_walls;
}

sf::Texture* AssetMGR::cue_texture(){
    return cue;
}



