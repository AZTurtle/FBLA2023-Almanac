
#ifndef LEVEL_CLASS_H
#define LEVEL_CLASS_H

#include"camera.h"
#include"player.h"
#include"core/input.h"
#include"core/time_manager.h"
#include"assets/model.h"
#include"assets/assets.h"
#include"core/audio.h"

static GLuint generatePaperVAO(){
    const glm::vec4 verts[] = {
        glm::vec4(0.5f, 0.5f, 1.0f, 0.0f),
        glm::vec4(-0.5f, 0.5f, 0.0f, 0.0f),
        glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
        glm::vec4(0.5f, -0.5f, 1.0f, 1.0f)
    };
    const unsigned short inds[] = {
        0,1,2,
        2,3,0
    };
    GLuint VAOID, VBOID, EBOID;

    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);

    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &EBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), inds, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return VAOID;
}

struct level{
    const int w, h, z;

    std::vector<unsigned int> letterMovement;
    std::vector<long long> movementTimes;
    std::vector<std::vector<glm::vec3>> movementPos;
    bool removing = false;
    std::vector<letterTile*> removingTiles;
    unsigned int removeNum = 0;
    long long removingTime;
    
    void update(){
        if(getGlobal() - lastPressed >= 200 && !removing){
            switch(lastKeyPressed){
                case VK_UP:
                    movePlayer(glm::ivec3(0.0f, 0.0f, 1.0f));
                    break;
                case VK_DOWN:
                    movePlayer(glm::ivec3(0.0f, 0.0f, -1.0f));
                    break;
                case VK_LEFT:
                    movePlayer(glm::ivec3(1.0f, 0.0f, 0.0f));
                    break;
                case VK_RIGHT:
                    movePlayer(glm::ivec3(-1.0f, 0.0f, 0.0f));
                    break;
                case VK_SPACE:
                    clearWords();
                    player.clearWords();
                    lastPressed = globalTime;
                    break;
                case 'R':
                    restart();
                    break;
            }
        }
        for(auto letter : removingTiles){
            letter->update(6.0f);
        }
        for(auto letter : letters){
            letter->update(12.0f);
        }
        for(int i = 0; i < movementPos.size(); i++){
            if(getGlobal() - movementTimes[i] >= 100 * letterMovement[i]){
                player.body[letterMovement[i]]->targetPos = movementPos[i][letterMovement[i] - 1];
                if(++letterMovement[i] >= player.body.size()){
                    movementTimes.erase(movementTimes.begin() + i);
                    letterMovement.erase(letterMovement.begin() + i);
                    movementPos.erase(movementPos.begin() + i);
                }
            }
        }
        if(removeNum == removingTiles.size()){
            removing = false;
        }else if(getGlobal() - removingTime >= 50){
            removingTiles[removeNum]->targetPos += glm::vec3(0.0f, 10.0f, 0.0f);
            removeNum++;
            removingTime += 50;
            if(removeNum == removingTiles.size()){
                for(auto letter : player.body){
                    letter->targetPos = letter->pos;
                }
            }
        }
    }
	glm::mat4 lTransform;


    std::vector<tile*> tiles;
    std::vector<letterTile*> letters;
    std::vector<std::string> validWords;
    Player player;
    Camera* cam;
    Assets& assets = Assets::getAssets();
    Shader_* tableShader;
    Model table;
    bool* levelComplete;

    Object stapler = Object(new Shader(shaders::textured, uniforms(&cam->matrix,&stapler.transform,assets.getTexture("stapler.png")), staticUniforms()), Model(&models::stapler));
    Object pencil = Object(new Shader(shaders::textured, uniforms(&cam->matrix,&pencil.transform,assets.getTexture("pencil.png")), staticUniforms()), Model(&models::pencil));
    Object ruler = Object(new Shader(shaders::textured, uniforms(&cam->matrix,&ruler.transform,assets.getTexture("ruler.png")), staticUniforms()), Model(&models::ruler));
    Object eraser = Object(new Shader(shaders::textured, uniforms(&cam->matrix,&eraser.transform,assets.getTexture("eraser.png")), staticUniforms()), Model(&models::eraser));
    GLuint camMatrix = glGetUniformLocation(shaders::diffuse.id, "camMatrix");
    GLuint objMatrix = glGetUniformLocation(shaders::diffuse.id, "objMatrix");
    Model letterModel = Model(&models::letterWood);
    
    GLuint color = glGetUniformLocation(shaders::letterPaper.id, "color");
    GLuint camMat_u = glGetUniformLocation(shaders::letterPaper.id, "camMatrix");
    GLuint objMat_u = glGetUniformLocation(shaders::letterPaper.id, "objMatrix");
    GLuint tex_u = glGetUniformLocation(shaders::letterPaper.id, "tex");
    Shader_* shader = new Shader(shaders::letterPaper, uniforms(&cam->matrix), staticUniforms());
    const GLuint VAO = generatePaperVAO();

    virtual void draw(){
        for(auto letter : letters){
            shaders::diffuse.bind();
            glUniformMatrix4fv(camMatrix, 1, GL_FALSE, glm::value_ptr(cam->matrix));
            glUniformMatrix4fv(objMatrix, 1, GL_FALSE, glm::value_ptr(letter->transform));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, assets.getTexture("letterWood.png")->id);
            letterModel.render();
        }
        for(auto letter : removingTiles){
            shaders::diffuse.bind();
            glUniformMatrix4fv(camMatrix, 1, GL_FALSE, glm::value_ptr(cam->matrix));
            glUniformMatrix4fv(objMatrix, 1, GL_FALSE, glm::value_ptr(letter->transform));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, assets.getTexture("letterWood.png")->id);
            letterModel.render();
        }
        tableShader->bind();
        table.render();
    }
    virtual void drawTransparent(){
        for(auto letter : letters){
            shaders::letterPaper.bind();
            glUniformMatrix4fv(objMat_u, 1, GL_FALSE, glm::value_ptr(letter->transform));
            glUniformMatrix4fv(camMat_u, 1, GL_FALSE, glm::value_ptr(cam->matrix));
            glUniform1i(tex_u, 0);
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, letter->tex->id);
            if(letter->chained) glUniform3fv(color, 1, glm::value_ptr(letter->color * glm::vec3(0.4f, 1.0f, 0.4f)));
            else glUniform3fv(color, 1, glm::value_ptr(letter->color));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, letter->border->id);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
        for(auto letter : removingTiles){
            shaders::letterPaper.bind();
            glUniformMatrix4fv(objMat_u, 1, GL_FALSE, glm::value_ptr(letter->transform));
            glUniformMatrix4fv(camMat_u, 1, GL_FALSE, glm::value_ptr(cam->matrix));
            glUniform1i(tex_u, 0);
            glActiveTexture(GL_TEXTURE0 + 0);
            glBindTexture(GL_TEXTURE_2D, letter->tex->id);
            glUniform3fv(color, 1, glm::value_ptr(letter->color * glm::vec3(0.4f, 1.0f, 0.4f)));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, letter->border->id);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }
    }

    long long lastPressed = 0;
    level(float distX, float distY, float distZ, Camera* cam, int w, int h, int z, std::vector<std::string> validWords, bool* levelComplete) : 
    lTransform(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(-w/2.0f + 0.5f,0.0f,-h/2.0f + 0.5f)), glm::radians(90.0f), UP_VECTOR)), 
    tableShader(new Shader(shaders::textured, uniforms(&cam->matrix, &lTransform, assets.getTexture("table.png")),staticUniforms())), 
    table(&models::table), levelComplete(levelComplete), validWords(validWords), cam(cam), player(cam), w(w), h(h), z(z){
        cam->move(glm::vec3(distX, distY, distZ),glm::vec3(0.0f, -0.95f, -1.0f));
        checkWords();
        hasLetters = true;
    }
    void addLetter(char letter, glm::ivec3 pos){
        letters.push_back(new letterTile(pos,glm::vec3(66.0f/255.0f, 159.0/255.0f, 246.0f/255.0f),letter,true,false,0));
    }
    void addTile(glm::ivec3 pos){
        tiles.push_back(new tile(pos, false));
    }
    tile* getTile(glm::ivec3 pos){
        for(auto letter : letters){
            if(letter->pos == pos){
                return letter;
            }
        }
        for(auto tile : tiles){
            if(tile->pos == pos){
                return tile;
            }
        }
        return nullptr;
    }
    virtual void restart(){
        letters.clear();
        removingTiles.clear();
        removeNum = 0;
        removing = false;
        player.body.clear();
        hasLetters = true;
        letterMovement.clear();
        movementTimes.clear();
        movementPos.clear();
    }
    bool move(glm::ivec3 init, glm::ivec3 shift){
        glm::ivec3 newPos = init + shift;
        tile* first = getTile(init);
        tile* next = getTile(newPos);
        if(!(newPos.x >= -1 && newPos.x <= w && newPos.z >= -1 && newPos.z <= h) || (first != nullptr && !first->moveable)) return false;
        else if(first == nullptr) return true;
        else if(move(newPos,shift)){
            first->pos += shift;
            first->targetPos = first->pos;
            return true;
        }
        return false;
    }
    void movePlayer(glm::ivec3 shift){
        if(move(player.body[0]->pos + shift, shift)){
            playSound("resources/audio/bell.wav");
            player.move(shift);
            checkWords();
            lastPressed = getGlobal();
            movementTimes.push_back(getGlobal());
            letterMovement.push_back(1);
            if(player.body.size() > 1){
                movementPos.push_back(std::vector<glm::vec3>());
                for(int i = 1; i < player.body.size(); i++){
                    movementPos[movementPos.size() - 1].push_back(player.body[i]->pos);
                }
            }
        }
    }
    void clearWords(){
        auto i = letters.begin();
        while(i != letters.end()){
            if((*i)->chained){
                removingTiles.push_back(*i);
                letters.erase(i);
                removing = true;
                removingTime = getGlobal();
            }else{
                i++;
            }
        }
        if(letters.size() == 0){
            *levelComplete = true;
        }
        movementPos.clear();
        movementTimes.clear();
        letterMovement.clear();
    }

    void checkWords(){
        std::vector<char*> words;
        std::vector<letterTile**> letterOrder;
        for(int y = 0; y < h; y++){
            words.push_back(new char[w]);
            letterOrder.push_back(new letterTile*[w]);
            for(int x = 0; x < w; x++){
                words[y][x] = ' ';
            }
        }

        for(auto letter : letters){
            words[letter->pos.z][letter->pos.x] = letter->letter;
            letterOrder[letter->pos.z][letter->pos.x] = letter;
        }
        std::vector<std::string> foundWords;
        std::vector<std::vector<letterTile*>> foundLetters;
        for(int y = 0; y < h; y++){
            std::string word;
            bool adj = false;
            std::vector<letterTile*> lettersTemp;
            for(int x = 0; x < w; x++){
                if(words[y][x] != ' '){
                    word.insert(word.begin(), words[y][x]);
                    lettersTemp.push_back(letterOrder[y][x]);
                    adj = true;
                } else {
                    adj = false;
                }
                if((!adj && word.length() > 0) || (x == w - 1 && word.length() > 0)){
                    foundWords.push_back(word);
                    foundLetters.push_back(lettersTemp);
                    word = "";
                    lettersTemp.clear();
                }
            }
        }
        for(int x = 0; x < w; x++){
            std::string word;
            bool adj = false;
            std::vector<letterTile*> lettersTemp;
            for(int y = 0; y < h; y++){
                if(words[y][x] != ' '){
                    word.insert(word.begin(), words[y][x]);
                    lettersTemp.push_back(letterOrder[y][x]);
                    adj = true;
                } else {
                    adj = false;
                }
                if((!adj && word.length() > 0) || (y == h - 1 && word.length() > 0)){
                    foundWords.push_back(word);
                    foundLetters.push_back(lettersTemp);
                    word = "";
                    lettersTemp.clear();
                }
            }
        }   
        std::vector<std::vector<letterTile*>> finalLetters;

        for(int i = 0; i < foundWords.size(); i++){
            for(auto word : validWords){
                if(foundWords[i].compare(word) == 0){
                    finalLetters.push_back(foundLetters[i]);
                    printf(foundWords[i].c_str());
                }
            }
        }

        for(auto letter : letters){
            letter->chained = false;
        }

        for(auto word : finalLetters){
            for(auto letter : word){
                letter->chained = true;
            }
        }
    }
};

class LevelManager{
    public:
        bool loaded = false;
        bool* levelComplete;
        Camera* levelCam;
        GLFWwindow* window;

        level* level_p = nullptr;
        LevelManager(Camera* cam, GLFWwindow* window, bool* levelComplete);
        template<typename T>
        void loadLevel(){
            if(level_p != nullptr){
                delete level_p;
            }
            level_p = new T(levelCam, levelComplete);
            loaded = true;
        }
        void update();
        void drawOpaque();
        void drawTransparent();
        void restart();
        bool checkTile(int, int);
};

#endif