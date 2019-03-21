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
uniform mat4 NM;

// varying means send to fragment shader
varying vec3 V_Normal;
varying vec4 V_WorldPos;

// main entry
// <= version120 mat4 to mat3:
// mat3(m[0].xyz, m[1].xyz, m[2].xyz)
// >= version150 mat4 to mat3:
// mat3(m)
void main() {
    V_Normal = mat3( NM[0].xyz, NM[1].xyz, NM[2].xyz)  * normal;
    V_WorldPos = M * vec4(position, 1.0);
    // calculate position
    gl_Position = P * V * M * vec4(position, 1.0);
}