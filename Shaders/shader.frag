#version 330 core

in vec2 TexCoords;

out vec4 outColour;

uniform sampler2D image;
uniform vec4 fragColour;

void main() {
  outColour = texture(image, TexCoords) * vec4(fragColour);
}
