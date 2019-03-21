// varying in fragment shader means
// receive data from vertex shader

// uniform vec4 ambient_light_color;
// uniform vec4 ambient_material;

// diffuse base : N*L=|N|*|L|cosΘ 
// diffuse = Kd * lightColor * max(N·L,0)

varying vec3 V_Normal;

void main() {
    vec3 lightPosition = vec3(0.0, 10.0, 0.0);
    vec3 L = lightPosition;
    L = normalize(L);
    vec3 n = normalize(V_Normal);

    // ambient 
    vec4 ambient_light_color=vec4(0.2, 0.2, 0.2, 1.0);
    vec4 ambient_material=vec4(0.2, 0.2, 0.2, 1.0);
    vec4 ambientColor = ambient_light_color * ambient_material;

    // diffuse
    vec4 DiffuseLightColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 DiffuseMaterial = vec4(0.4, 0.4, 0.4, 1.0);
    vec4 diffuseColor = DiffuseLightColor * DiffuseMaterial * max(0.0, dot(L, n));

    gl_FragColor = ambientColor + diffuseColor;
}