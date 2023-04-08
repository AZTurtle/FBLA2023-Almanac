#include "resources.h"

namespace shaders{
	ShaderBase<uniforms<glm::mat4*, float*, Texture*, glm::mat4*>,staticUniforms<>> diffusesprite3D("3D_diffuse.vs","3D_diffuse.fs", {"matrix","color","tex","cam"},{});
	ShaderBase<uniforms<glm::mat4*, float*,Texture*>,staticUniforms<>> diffuse2D("2D_diffuse.vs","2D_diffuse.fs", {"matrix","color","tex"},{});
	ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> diffuse("diffuse.vs","diffuse.fs",{"camMatrix"},{});
	ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterShader("letter.vs","letter.fs",{"camMatrix"},{});
	ShaderBase<uniforms<glm::mat4*>,staticUniforms<>> letterPaper("letterPaper.vs","letterPaper.fs",{"camMatrix"},{});
	ShaderBase<uniforms<glm::mat4*, glm::mat4*, Texture*>,staticUniforms<>> textured("textured.vs","textured.fs",{"camMatrix","objMatrix","tex"},{});
	ShaderBase<uniforms<float*>,staticUniforms<>> fadeShader("fade.vs","fade.fs",{"fade"},{});
}

namespace models{
	Model_def_N letterPaper("letters.obj");
	Model_def_T letterWood("letterWood.obj");
	Model_def_NT l1("l1.obj");
	Model_def_NT table("table.obj");
	Model_def_NT stapler("stapler.obj");
	Model_def_NT pencil("pencil.obj");
    Model_def_NT ruler("ruler.obj");
    Model_def_NT eraser("eraser.obj");
}