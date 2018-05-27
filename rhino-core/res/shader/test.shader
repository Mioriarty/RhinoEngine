##set version 330

##shader vertex

layout(location = 0) in vec2 pos; 
layout(location = 1) in vec2 textureCoord; 

out vec2 v_texCoord;

void main(void){ 
	gl_Position = viewMatrix * modelMatrix * vec4(pos, 0.0, 1.0);
	v_texCoord = textureCoord;
}

##shader fragment

in vec2 v_texCoord;

out vec4 c;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float lerpFactor;

void main(void){ 
	vec4 c1 = texture(tex1, v_texCoord);
	vec4 c2 = texture(tex2, v_texCoord);

	c = c1 * lerpFactor + c2 * (1 - lerpFactor);

}
