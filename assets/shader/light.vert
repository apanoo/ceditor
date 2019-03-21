// attribute means get data from CPU
// attribute likes uniform but ...
// buffer size is smaller then attribute
attribute vec3 position;
attribute vec2 texcoord;
attribute vec3 normal;

// dynamic matrix data from CPU
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

// varying means send to fragment shader

// main entry
void main() {
    // calculate position
    gl_Position = P * V * M * vec4(position, 1.0);
}