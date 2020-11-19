#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform Material material;
uniform bool gridMaterial;

Material _material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    if(gridMaterial) {
        bool rev = mod(floor(FragPos.x)+floor(FragPos.z), 2) == 1;
        if(rev) {
            _material.ambient = vec3(1.0, 1.0, 1.0);
            _material.diffuse = vec3(1.0, 1.0, 1.0);
            _material.specular = vec3(1.0, 1.0, 1.0);
        }
        else {
            _material.ambient = vec3(0.0, 0.0, 0.0);
            _material.diffuse = vec3(0.0, 0.0, 0.0);
            _material.specular = vec3(0.0, 0.0, 0.0);
        }
        _material.shininess = material.shininess;
    }
    else {
        _material.ambient = material.ambient;
        _material.diffuse = material.diffuse;
        _material.specular = material.specular;
        _material.shininess = material.shininess;
    }

    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    result += CalcPointLight(pointLight, norm, FragPos, viewDir);
    // phase 3: spot light
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    // combine results
    vec3 ambient = light.ambient * _material.ambient;
    vec3 diffuse = light.diffuse * diff * _material.diffuse;
    vec3 specular = light.specular * spec * _material.specular;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * _material.ambient;
    vec3 diffuse = light.diffuse * diff * _material.diffuse;
    vec3 specular = light.specular * spec * _material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}