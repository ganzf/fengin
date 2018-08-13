#version 330 core

// Comes from the vertex shader
in vec3 fragmentColor;

out vec3 color;
void main(){
  color = fragmentColor;
}