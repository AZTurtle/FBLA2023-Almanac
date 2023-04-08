#ifndef RESOURCE_CLASS_H
#define RESOURCE_CLASS_H

#include "assets/shaders.h"
#include "assets/model.h"
#include "assets/textures.h"
#include "core/audio.h"

namespace shaders{
	extern ShaderBase<uniforms<glm::mat4*, float*, Texture*>,staticUniforms<>> diffuse2D;
	extern ShaderBase<uniforms<glm::mat4*, float*, Texture*, glm::mat4*>,staticUniforms<>> diffusesprite3D;
	extern ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> diffuse;
	extern ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterShader;
	extern ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterPaper;
	extern ShaderBase<uniforms<glm::mat4*, glm::mat4*, Texture*>,staticUniforms<>> textured;
	extern ShaderBase<uniforms<float*>,staticUniforms<>> fadeShader;
};

namespace models{
	extern Model_def_N letterPaper;
	extern Model_def_T letterWood;

	extern Model_def_NT l1;
	extern Model_def_NT table;

	extern Model_def_NT stapler;
	extern Model_def_NT pencil;
	extern Model_def_NT ruler;
	extern Model_def_NT eraser;
};

#endif