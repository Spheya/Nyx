#version 400

in vec2 v_TexCoord;

out vec4 out_colour;

void main() {
    out_colour = vec4(v_TexCoord, 0.0, 1.0);
}