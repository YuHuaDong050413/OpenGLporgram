#version 430 core

//uniform vec4 u_Color;
#pragma region ����
in vec4 v_Color;

in vec3 v_Normal;
in vec3 v_LightDir;
in vec3 v_VertPos;
in vec3 v_HalfVector;

in vec4 shadow_coord;

in vec2 v_TexCoords;
#pragma endregion

#pragma region Uniform
//����
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

//���� 
struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};
uniform Material material;

//����
uniform sampler2D u_Texture;
//��Ӱ��ͼ
uniform sampler2DShadow shTex;
#pragma endregion

#pragma region ���
layout (location = 0) out vec4 out_color;
#pragma endregion

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);

	float cosTheta = max(dot(normalize(v_LightDir), normalize(v_Normal)), 0);
	float cosPhi = max(dot(normalize(v_VertPos), normalize(v_HalfVector)), 0);
	//�в��ʵ�
	vec3 ambient = ((globalLight.ambient * material.ambient) + (positionalLight.ambient * material.ambient)).xyz;
	vec3 diffuse = positionalLight.diffuse.xyz * material.diffuse.xyz * cosTheta;
	vec3 specular = positionalLight.specular.xyz * material.specular.xyz * pow(cosPhi, material.shininess * 3.0);

	//û�в��ʵ�
	vec3 ambient_1 = (globalLight.ambient + positionalLight.ambient).xyz;
	vec3 diffuse_1 = positionalLight.diffuse.xyz * cosTheta;
	vec3 specular_1 = positionalLight.specular.xyz * pow(cosPhi, material.shininess * 3.0);

	float notInShadow = textureProj(shTex, shadow_coord);
	
	//out_color = 0.5 * (vec4(ambient, 1.0) + texColor);
	
	//out_color = vec4(ambient + (diffuse + specular) * notInShadow, 1.0);
	//out_color = vec4((diffuse + specular) * notInShadow, 1.0);
	//�������µ�
	//out_color = vec4(ambient, 1.0f);
	//out_color = vec4(ambient + (diffuse + specular) * notInShadow, 1.0f);
	if (notInShadow  == 0.0)
	{
		out_color = vec4( ambient + diffuse + specular, 1.0f);
	}
};