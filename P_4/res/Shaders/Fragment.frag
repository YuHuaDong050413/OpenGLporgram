#version 430 core

//uniform vec4 u_Color;
#pragma region 输入
in vec4 v_Color;

in vec3 v_Normal;
in vec3 v_LightDir;
in vec3 v_VertPos;
in vec3 v_HalfVector;

in vec2 v_TexCoords;
#pragma endregion

#pragma region Uniform
//光照
struct GlobalLight
{
	vec4 ambient;
};
uniform GlobalLight globalLight;
struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
uniform PositionalLight positionalLight;

//材质 
struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};
uniform Material material;

//纹理
uniform sampler2D u_Texture;
#pragma endregion

#pragma region 输出
layout (location = 0) out vec4 out_color;
#pragma endregion

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);

	float cosTheta = max(dot(normalize(v_LightDir), normalize(v_Normal)), 0);
	float cosPhi = max(dot(normalize(v_VertPos), normalize(v_HalfVector)), 0);
	//有材质的
	vec3 ambient = ((globalLight.ambient * material.ambient) + (positionalLight.ambient * material.ambient)).xyz;
	vec3 diffuse = positionalLight.diffuse.xyz * material.diffuse.xyz * cosTheta;
	vec3 specular = positionalLight.specular.xyz * material.specular.xyz * pow(cosPhi, material.shininess * 3.0);

	//没有材质的
	vec3 ambient_1 = (globalLight.ambient + positionalLight.ambient).xyz;
	vec3 diffuse_1 = positionalLight.diffuse.xyz * cosTheta;
	vec3 specular_1 = positionalLight.specular.xyz * pow(cosPhi, material.shininess * 3.0);

	out_color = 0.5 * (vec4(ambient + diffuse + specular, 1.0) + texColor); //+ texColor  加起来除2
	//out_color = texColor;
};