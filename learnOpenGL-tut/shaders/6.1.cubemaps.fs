#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform sampler2D texture1;
uniform float outputNumber;
uniform samplerCube skybox;

void main()
{    
    if(outputNumber == 1){
	FragColor = texture(texture1, TexCoords);
    }
    if(outputNumber == 2){
	vec3 I = normalize(Position - cameraPos);
    	vec3 R = reflect(I, normalize(Normal));
    	FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }
    if(outputNumber == 3){
	float ratio = 1.00 / 1.52;
    	vec3 I = normalize(Position - cameraPos);
    	vec3 R = refract(I, normalize(Normal), ratio);
    	FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }

   
}
