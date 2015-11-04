#version 150

in vec4 vPosition;
in vec4 vNormal;

// output values that will be interpolated per-fragment
out vec3 n;
out vec3 e;
out vec3 fL;
out vec3 fL2;

uniform mat4 T;
uniform mat4 V;
uniform mat4 P;
uniform vec4 lightningPos;
uniform vec4 lightningPos2;


void
main()
{
	//first, transform vertex position into camera coordinates.
	vec4 vpos4 = (V*T*(vPosition));
	vec3 vPos = (vpos4).xyz;


	//transform vertex normal into eye coordinates.
	n = normalize( V * T * vNormal).xyz;
	e = -normalize(vPos.xyz);

	fL = ((V*lightningPos).xyz - vPos.xyz);
	fL2 = ((V*lightningPos2).xyz - vPos.xyz);


	//calculating the objectmatrix in ndc coordinates
	gl_Position = P*vpos4;

}