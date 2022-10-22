#version 330 core
out vec4 FragColor;
in vec2 o_uv;
uniform sampler2D grass_texture;
vec4 TexColor;
void main(){
	
	TexColor=texture(grass_texture,o_uv);

	FragColor = TexColor;
}