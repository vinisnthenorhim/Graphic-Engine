#version 460 core

in vec2 UV;
uniform sampler2D myTexture;

out vec4 color;

void main()
{
    // color = texture(myTexture, UV);
    color = vec4(0.3, 0.4, 0.6, 1.0);
}