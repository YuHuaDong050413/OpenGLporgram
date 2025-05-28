#version 420 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normal;

//Gouraud��ɫ
//����
struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
uniform PositionalLight positionalLight;

//ģ��
struct Matrix
{
	mat4 mv;
	mat4 p;
	mat4 normal;
};
uniform Matrix matrix;
//uniform mat4 normal_matrix;
//uniform mat4 mv_matrix;
//uniform mat4 proj_matrix;

out vec3 v_Normal;
out vec3 v_LightDir;
out vec3 v_VertPos;
out vec3 v_HalfVector;;

//����
out vec2 v_TexCoords;



void main()
{
	v_VertPos = normalize(-(matrix.mv * vec4(a_Position, 1.0)).xyz);
	v_LightDir = normalize(positionalLight.position - v_VertPos);
	v_Normal = normalize((matrix.normal * vec4(a_Normal, 1.0)).xyz);
	v_HalfVector = normalize(v_LightDir + (- v_VertPos).xyz);

	v_TexCoords = a_TexCoords;
	gl_Position = matrix.p * matrix.mv * vec4(a_Position, 1.0);
};