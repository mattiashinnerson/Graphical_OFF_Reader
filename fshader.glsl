#version 150

//per-fragment interpolated values from the vertex shader
in vec3 n;
in vec3 fL;
in vec3 fL2;
in vec3 e;

out vec4  fColor;

uniform vec4 ambientProduct, diffuseProduct, diffuseProduct2 , specularProduct;
uniform mat4 T;
uniform mat4 V;
uniform vec4 lightningPos;
uniform vec4 lightningPos2;
uniform float shininess;



void main() {

	vec4 ambient, diffuse, specular, diffuse2, specular2;

	vec3 l = normalize(fL);
	vec3 l2 = normalize(fL2);

	vec3 h = normalize(l+e);
	vec3 h2 = normalize(l2+e);

	//cumpute the illumination equation.
	ambient = ambientProduct;

	float kd = max(dot(l,n),0.0);
	float kd2 = max(dot(l2,n),0.0);
	diffuse = kd * diffuseProduct;
	diffuse2 = kd2 * diffuseProduct2;

	float ks = pow(max(dot(n,h), 0.0), shininess);
	float ks2 = pow(max(dot(n,h2), 0.0), 33);
	specular = ks * specularProduct;
	specular2 = ks2 * specularProduct;

	if(dot(l,n) < 0)
	specular = vec4(0.0,0.0,0.0,1.0);

	//adding each component to our color.
	fColor = ambient  +  diffuse  + specular + diffuse2  + specular2;
	fColor.a = 1.0;
}