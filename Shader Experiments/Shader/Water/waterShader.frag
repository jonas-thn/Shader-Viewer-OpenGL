#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform int index;
uniform float time;

out vec4 FragColor;

const float PI = 3.14159265359;
const float WORLD_SCALE = 8.0;

struct Wave {
    vec2 direction;
    float amplitude;
    float wavelength;
    float speed;
};

const float N_WAVES = 3;

Wave waves[3] = Wave[3](
    Wave(vec2(1.0, 0.25), 0.08, 4.0, 0.8),

    Wave(vec2(-0.6, 0.8), 0.05, 2.5, 1.4),

    Wave(vec2(0.2, -1.0), 0.03, 1.5, 2.0)
);

const float SHININESS = 40.0;
const float REFLECTIVITY = 0.04; 

float waveHeight(vec2 pos)
{
    const float WAVE_AMPLITUDE_SCALE = 1.8;

    float h = 0.0;

    for (int i = 0; i < N_WAVES; i++)
    {
        vec2 d = normalize(waves[i].direction);
        h += waves[i].amplitude * sin(2.0 * PI / waves[i].wavelength *  dot(d, pos) - waves[i].speed * time);
    }

    return h * WAVE_AMPLITUDE_SCALE;
}

vec3 getNormal(vec2 pos)
{
    float eps = 0.03;

    return normalize(vec3(
        waveHeight(pos - vec2(eps, 0.0)) - waveHeight(pos + vec2(eps, 0.0)),
                2.0 * eps,
        waveHeight(pos - vec2(0.0, eps)) - waveHeight(pos + vec2(0.0, eps))
    ));
}

void main()
{
    vec3 baseColor = vec3(0.05, 0.07, 0.12);

    vec2 pos = (TexCoords - 0.5) * WORLD_SCALE * vec2(1600.0 / 900.0, 1.0);
    float h = waveHeight(pos);
    vec3 n = getNormal(pos);

    //Light
    vec3 lightDir = normalize(vec3(-0.4, 0.8, 0.3));

    vec3 viewDir = normalize(vec3(0.0, 0.5, 1.0));
    float diff = max(dot(n, lightDir), 0.0);

    vec3 halfVector = normalize(lightDir + viewDir);
    float spec = pow(max(dot(n, halfVector), 0.0), SHININESS);

    //Fesnel
    float viewN = max(dot(n, viewDir), 0.0);
    float fresnel = REFLECTIVITY + (1.0 - REFLECTIVITY) * pow(1.0 - viewN, 5.0);

    vec3 reflectionColor = vec3(0.55, 0.75, 0.9);
    vec3 diffuse = baseColor * diff;
    vec3 color = mix(diffuse, reflectionColor, fresnel);
    color += spec * 0.9;
    color += 0.12 * smoothstep(0.06, 0.18, h);

    FragColor = vec4(color, 1.0);
}
