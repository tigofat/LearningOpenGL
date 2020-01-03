#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;

out vec2 g_TexCoords;

void main()
{
    gl_Position = vec4(aPosition.xyz, 1.0f);
    g_TexCoords = aTexCoords;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 g_TexCoords;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
    FragColor = mix(texture(u_Texture1, g_TexCoords), texture(u_Texture2, g_TexCoords), 0.5);
}