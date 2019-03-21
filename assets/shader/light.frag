// varying in fragment shader means
// receive data from vertex shader

// uniform vec4 ambient_light_color;
// uniform vec4 ambient_material;

#ifdef GL_ES
precision mediump float;
#endif

void main() {
    // environment light color
    vec4 ambient_light_color=vec4(0.2, 0.2, 0.2, 1.0);

    // ambient params
    vec4 ambient_material=vec4(0.2, 0.2, 0.2, 1.0);

    // calculate ambient color
    vec4 ambientColor = ambient_light_color * ambient_material;
    gl_FragColor = ambientColor;
}