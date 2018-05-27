##set version 330

##shader vertex

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 1) in vec3 normal;

out vec2 v_texCoord;

void main(void) {
	v_texCoord = texCoord;
	gl_Position = viewMatrix * modelMatrix * vec4(pos, 1.0);
}

##shader fragment

uniform sampler2D image;

in vec2 v_texCoord;

out vec4 outColor;

void main(void) {
	outColor = texture(image, v_texCoord);
}