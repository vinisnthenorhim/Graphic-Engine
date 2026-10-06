#version 460 core

#define MODEL_MATRIX_BINDING 4

uniform mat4 projection;
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(std430, binding = MODEL_MATRIX_BINDING) readonly buffer ModelMatrixBuffer { mat4 modelMatrices[]; };

out vec2 texCoord;

void main()
{
  mat4 model = modelMatrices[gl_InstanceID];
  gl_Position = projection * model * vec4(position, 1.0);
  texCoord = uv;
}