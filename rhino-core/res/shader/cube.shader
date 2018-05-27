##set version 330

##shader vertex

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 1) in vec3 normal;

out vec2 v_texCoord;
out vec3 v_normal;

void main(void) {
	v_texCoord = texCoord;
	v_normal = normal;
	gl_Position = viewMatrix * modelMatrix * vec4(pos, 1.0);
}

##shader fragment

uniform float brightness;
uniform sampler2D tex;
uniform sampler2D stancil;

in vec2 v_texCoord;

out vec4 color;

void main(void) {
	color = texture(tex, v_texCoord) * brightness;
	if (texture(stancil, v_texCoord).x == 1.0f)
		discard;
}