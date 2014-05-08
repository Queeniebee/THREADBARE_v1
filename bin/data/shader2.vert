/*
#version 120

varying vec2 texCoordVarying;

void main()
{
    texCoordVarying = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
}
*/
#version 120

void main()
{
	gl_Position = ftransform();
}
