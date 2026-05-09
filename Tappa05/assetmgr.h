#ifndef ASSETMGR_H
#define ASSETMGR_H
#include <SFML/Graphics.hpp>
#include <vector>


class AssetMGR {
public:
	static AssetMGR& instance();
	sf::Texture* table_texture();
	sf::Texture* table_wall_texture();
	sf::Texture* table_pocket_texture();
	sf::Texture* cue_texture();
	sf::Texture* get_ball_texture(unsigned id);
private:
	AssetMGR(); // Nascondo il costruttore per usare il singleton
	sf::Texture* table;
	sf::Texture* table_walls;
	sf::Texture* table_pockets;
	sf::Texture* cue;
	std::vector<sf::Texture*> balls;
	std::vector<bool> loaded_balls_textures;
};

#endif
