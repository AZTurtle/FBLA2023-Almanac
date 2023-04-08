#ifndef LEVEL_DEF_CLASS_H
#define LEVEL_DEF_CLASS_H

#include"level.h"
#include"resources.h"

namespace levels{
	struct l1 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl1.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
			stapler.render();
			pencil.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("at", glm::vec3(1.0f, 0.0f, 2.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('c', glm::vec3(4.0f, 0.0f, 2.0f));
			checkWords();
			stapler.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f, 2.4f, -7.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f, 2.5f, 2.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			pencil.transform = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.02f, -3.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
		}
		l1(Camera* cam, bool* levelComplete): 
		level(-2.0f, 16.0f, 14.0f, cam, 5, 5, 1, {
			"cat","act"
		},levelComplete)
		{
			restart();
		}
	};
	struct l2 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl2.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
			pencil.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.02f, -3.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			pencil.render();
			pencil.transform = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.02f, -1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(190.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			pencil.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("at", glm::vec3(1.0f, 0.0f, 1.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('c', glm::vec3(3.0f, 0.0f, 1.0f));
			addTile(glm::ivec3(2.0f, 0.0f, 1.0f));
			checkWords();
		}
		l2(Camera* cam, bool* levelComplete): 
		level(-1.5f, 16.0f, 15.0f, cam, 4, 4, 1, {
			"cat","act"
		},levelComplete)
		{
			restart();
		}
	};
	struct l3 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl3.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
			ruler.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("af", glm::vec3(4.0f, 0.0f, 1.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('a', glm::vec3(1.0f, 0.0f, 2.0f));
			addLetter('c', glm::vec3(0.0f, 0.0f, 3.0f));
			addLetter('t', glm::vec3(3.0f, 0.0f, 0.0f));
			ruler.transform = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.02f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.8f, 1.8f, 1.8f)) * glm::rotate(glm::mat4(1.0f), glm::radians(190.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			addTile(glm::ivec3(1.0f, 0.0f, 3.0f));
			checkWords();
		}
		l3(Camera* cam, bool* levelComplete): 
		level(-2.0f, 16.0f, 15.0f, cam, 5, 5, 1, {
			"fat","cat","act","fact","aft"
		},levelComplete)
		{
			restart();
		}
	};
	struct l4 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl4.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
			eraser.render();
			pencil.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("until", glm::vec3(4.0f, 0.0f, 3.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('s', glm::vec3(2.0f, 0.0f, 5.0f));
			addLetter('s', glm::vec3(1.0f, 0.0f, 5.0f));
			addLetter('e', glm::vec3(5.0f, 0.0f, 1.0f));
			addLetter('l', glm::vec3(2.0f, 0.0f, 1.0f));
			addLetter('h', glm::vec3(5.0f, 0.0f, 0.0f));
			addTile(glm::ivec3(0.0f, 0.0f, 0.0f));
			addTile(glm::ivec3(1.0f, 0.0f, 0.0f));
			addTile(glm::ivec3(2.0f, 0.0f, 0.0f));
			addTile(glm::ivec3(4.0f, 0.0f, 1.0f));
			eraser.transform = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.02f, -2.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.9f, 0.9f)) * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			pencil.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, 0.02f, -4.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			checkWords();
		}
		l4(Camera* cam, bool* levelComplete): 
		level(-2.5f, 16.0f, 14.0f, cam, 6, 6, 1, {
			"until","sell","hun","sit","lit","it","still"
		},levelComplete)
		{
			restart();
		}
	};
	struct l5 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl5.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
			pencil.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("when", glm::vec3(4.0f, 0.0f, 1.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('o', glm::vec3(1.0f, 0.0f, 0.0f));
			addLetter('w', glm::vec3(0.0f, 0.0f, 2.0f));
			addLetter('t', glm::vec3(5.0f, 0.0f, 5.0f));
			addLetter('e', glm::vec3(4.0f, 0.0f, 3.0f));
			addLetter('n', glm::vec3(5.0f, 0.0f, 2.0f));
			addTile(glm::ivec3(5.0f, 0.0f, 1.0f));
			pencil.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-4.5f, 0.02f, -8.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.5f, 3.5f, 3.5f)) * glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			checkWords();
		}
		l5(Camera* cam, bool* levelComplete): 
		level(-2.5f, 16.0f, 14.0f, cam, 6, 6, 1, {
			"ten","teen","how","when","then","hen","now","the","no","own","new"
		},levelComplete)
		{
			restart();
		}
	};
	struct l6 : level{
		Model levelModel = Model(&models::l1);
		Shader_* levelShader = new Shader(shaders::textured, uniforms(&cam->matrix,&lTransform,assets.getTexture("paperl6.png")), staticUniforms());
		void draw(){
			level::draw();
			levelShader->bind();
			levelModel.render();
		}
		void drawTransparent(){
			level::drawTransparent();
		}
		void update(){
			level::update();
		}
		void restart(){
			level::restart();
			player.prepModel("thanks", glm::vec3(5.0f, 0.0f, 5.0f));
			for(int i = 0; i < player.body.size(); i++){
				letters.push_back(player.body[i]);
			}
			addLetter('f', glm::vec3(2.0f, 0.0f, 3.0f));
			addLetter('o', glm::vec3(1.0f, 0.0f, 3.0f));
			addLetter('r', glm::vec3(0.0f, 0.0f, 3.0f));
			addLetter('p', glm::vec3(6.0f, 0.0f, 0.0f));
			addLetter('l', glm::vec3(5.0f, 0.0f, 0.0f));
			addLetter('a', glm::vec3(4.0f, 0.0f, 0.0f));
			addLetter('y', glm::vec3(3.0f, 0.0f, 0.0f));
			addLetter('i', glm::vec3(2.0f, 0.0f, 0.0f));
			addLetter('n', glm::vec3(1.0f, 0.0f, 0.0f));
			addLetter('g', glm::vec3(0.0f, 0.0f, 0.0f));
			stapler.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 2.4f, -4.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f))/* * */;
			addTile(glm::ivec3(5.0f, 0.0f, 1.0f));
			checkWords();
		}
		l6(Camera* cam, bool* levelComplete): 
		level(-3.f, 16.0f, 14.5f, cam, 7, 7, 1, {
			"thanks","for","playing"
		},levelComplete)
		{
			restart();
		}
	};
};

#endif