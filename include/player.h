#ifndef WORM_CLASS_H
#define WORM_CLASS_H

// #define PI 3.1415926
// #define RING_RES 16
// #define RING_NUM 4
// #define END_VERTS 17
// #define SEG_VERTS 64
// #define SEG_OFFSET 1.41414141414f
#include"resources.h"
#include"camera.h"
#include"core/fs.h"
#include"assets/assets.h"

static Assets& assets = Assets::getAssets();
extern const Texture* borders[3];

static Texture* const paperTexs[1] = {
    assets.getTexture("letterPaper.png")
};

inline glm::vec3 minimum(glm::vec3 a, glm::vec3 b){
    if(glm::length(a) < glm::length(b)) return a;
    else return b;
}

struct tile{
    glm::ivec3 pos;
    glm::vec3 renderPos;
    glm::vec3 targetPos;
    glm::mat4 transform;
    glm::mat4 scaledTransform;
    bool moveable;
    Shader_* shader;
    tile(glm::ivec3 pos, bool moveable) : pos(pos), renderPos(pos), targetPos(pos), transform(glm::translate(glm::mat4(1.0f), glm::vec3(-renderPos.x, renderPos.y, -renderPos.z))), moveable(moveable){};
    void update(float speed){
        renderPos += minimum((targetPos - renderPos) * speed * delta_time, targetPos - renderPos);
        transform = glm::translate(glm::mat4(1.0f), glm::vec3(-renderPos.x, renderPos.y, -renderPos.z));
    }
};

struct letterTile : tile{
    char letter;
    glm::vec3 color;
    bool chained = false;
    bool player;
    Texture* tex;
    Texture* border;
    letterTile(glm::ivec3 pos, glm::vec3 color, char letter, bool moveable, bool player, int borderNum) : 
        tile(pos, moveable), 
        player(player), 
        letter(letter), 
        color(color),
        border((Texture*)borders[borderNum])
    {
        char texPath[14] = "letters/ ";
        texPath[8] = letter;
        strcat(texPath, ".png");
        tex = assets.getTexture(texPath);
    };
};

extern bool hasLetters;

class Player{

    unsigned short wordLen;
    const char* word; 

    glm::mat4 transform = glm::mat4(1.0f);

    Shader_* letterShader;
    GLuint pos_u;

    void update();

    public:

        std::vector<letterTile*> body;

        Player(Camera*);

        void move(glm::ivec3);
        void prepModel(const char*, glm::ivec3);
        void clearWords();
};

#endif