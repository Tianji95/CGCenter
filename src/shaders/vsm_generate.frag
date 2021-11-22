#version 420 core
layout (location = 0) out vec2 Depth_;	
void main()
{
	Depth_ = vec2(gl_FragCoord.z, gl_FragCoord.z * gl_FragCoord.z);
} 