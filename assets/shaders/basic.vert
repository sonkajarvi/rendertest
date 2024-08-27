#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec3 a_Normal;

out vec4 v_Color;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    v_Color = a_Color;
    v_Normal = a_Normal;

    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
