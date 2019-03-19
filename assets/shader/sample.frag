// varying in fragment shader means 
// receive data from vertex shader
varying vec4 V_Color;

void main() {
    gl_FragColor = V_Color;
}