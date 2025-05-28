#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normal;

//Gouraud着色
//光照
uniform vec4 globalLight_ambient;
uniform vec4 positionalLight_ambient;
uniform vec4 positionalLight_diffuse;
uniform vec4 positionalLight_specular;
uniform vec3 positionalLight_position;
//材质 
uniform vec4  Material_ambient;
uniform vec4 Material_diffuse;
uniform vec4 Material_specular;
uniform float Material_shininess;
//模型
uniform mat4 normal_matrix;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 v_Color;
//out vec2 v_TexCoords;




void main()
{
	vec4 P = mv_matrix * vec4(a_Position, 1.0);
	vec3 N = normalize((normal_matrix * vec4(a_Normal, 1.0)).xyz);
	vec3 L = normalize(positionalLight_position - P.xyz);
	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);

	vec4 ambient = globalLight_ambient * Material_ambient+ positionalLight_ambient * Material_ambient;
	vec4 diffuse = max(dot(N, L), 0.0) * positionalLight_diffuse * Material_diffuse;
	vec4 specular = pow(max(dot(R, V), 0.0), Material_shininess) * positionalLight_specular * Material_specular;

	v_Color = ambient + diffuse + specular;
	gl_Position = proj_matrix * P;
};


#shader fragment
#version 330 core

//uniform vec4 u_Color;
//uniform sampler2D u_Texture;
in vec4 v_Color;

layout (location = 0) out vec4 out_color;

void main()
{
	//out_color  = texture(u_Texture, v_TexCoords);
	out_color = v_Color;
};

