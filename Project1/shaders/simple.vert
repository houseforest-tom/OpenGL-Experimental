#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec3 vert_normal;
layout(location = 2) in vec3 vert_color;
layout(location = 3) in vec2 vert_uv;

uniform mat4 modelViewProj;

out vec3 frag_color;

void main() {
  gl_Position = modelViewProj * vec4(vert_position, 1.0);
  frag_color = vert_color;
}