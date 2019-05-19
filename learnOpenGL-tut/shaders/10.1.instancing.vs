#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;

uniform mat4 view;
uniform mat4 projection;

uniform float outputNumVs;

void main()
{
    	fColor = aColor;
    	vec2 pos = aPos * (gl_InstanceID / 100.0);
	if(outputNumVs == 1)
    		gl_Position = projection * view * vec4(aPos + aOffset, 0.0, 1.0);
	if(outputNumVs == 2)
  		gl_Position = projection * view * vec4(pos + aOffset, 0.0, 1.0);
}
