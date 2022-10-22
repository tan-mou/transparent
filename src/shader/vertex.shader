#version 330 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 anormal;
layout(location = 2) in vec2 auv;

out vec3 normal;
out vec3 o_position;

out vec2 o_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    gl_Position = projection * view * model * vec4(apos, 1.0);
    normal = normalize(transpose(inverse(mat3(model)))* anormal);
    o_uv = auv;
    o_position = vec3(model * vec4(apos, 1));
}