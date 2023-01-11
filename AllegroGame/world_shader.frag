#version 400 core

const int MAX_LIGHTS_NUM = 100;

uniform sampler2D al_tex;
in vec2 varying_texcoord;
uniform int LIGHTS_NUM;
uniform vec3 LIGHTS_POS[MAX_LIGHTS_NUM];
uniform float LIGHTS_BRIGHT[MAX_LIGHTS_NUM];
uniform vec4 ambientLightColor;

vec4 mulEach(vec4 a, vec4 b) {
	return vec4(a.x*b.x,a.y*b.y,a.z*b.z,a.w*b.w);
}

vec3 limit(vec3 v, float l) {
	float m = max(v.x,max(v.y,v.z));
	if(m>l)
		return v*(l/m);
	else
		return v;
}

void main() {
	vec4 c1 = texture2D(al_tex, varying_texcoord);
	float fac = 1;
	for(int i=0;i<LIGHTS_NUM;i++)
	{
		float dist = length(vec3(gl_FragCoord)-LIGHTS_POS[i]);
		fac*=max(1,LIGHTS_BRIGHT[i]/(dist)); 
	}
	vec3 ac = limit(vec3(ambientLightColor)*min(2.25,max(1,fac)),1);
	c1 = mulEach(c1,vec4(ac,1));
	gl_FragColor = c1;
}