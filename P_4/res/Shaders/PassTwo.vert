#version 430 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normal;

//Gouraud着色
//光照
struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
uniform PositionalLight positionalLight;

//模型
struct Matrix
{
	mat4 mv;
	mat4 p;
	mat4 normal;
	mat4 shadowMVP;
};
uniform Matrix matrix;

out vec3 v_Normal;
out vec3 v_LightDir;
out vec3 v_VertPos;
out vec3 v_HalfVector;;

//纹理
out vec2 v_TexCoords;
//阴影
out vec4 shadow_coord;

//layout (binding = 0) uniform sampler2DShadow shTex;

void main()
{
	v_VertPos = normalize(-(matrix.mv * vec4(a_Position, 1.0)).xyz);
	v_LightDir = normalize(positionalLight.position - v_VertPos);
	v_Normal = normalize((matrix.normal * vec4(a_Normal, 1.0)).xyz);
	v_HalfVector = normalize(v_LightDir + (- v_VertPos).xyz);

	shadow_coord = matrix.shadowMVP * vec4(a_Position, 1.0);

	v_TexCoords = a_TexCoords;
	gl_Position = matrix.p * matrix.mv * vec4(a_Position, 1.0);
};